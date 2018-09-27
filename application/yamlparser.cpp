#include "yamlparser.h"
#include "tags.h"
#include "authors.h"

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <assert.h>
#include <map>
#include <QDebug>
#include <QString>
#include <QFile>

YAMLParser* YAMLParser::_instance = nullptr;

YAMLParser::YAMLParser(std::map<std::string, Tag> tags, std::map<std::string, Author> authors)
{
  _tags = tags;
  _authors = authors;
  _tags_changed = false;
  _authors_changed = false;
  _tags_path = "tags.yml";
  _authors_path = "authors.yml";
}

//YAMLParser* YAMLParser::get() {

//}

std::map<std::string, Tag> YAMLParser::getTags() {
  std::cout << "tags" << std::endl;
  if(_tags.size() == 0) {
    std::cout << "Affect Tags." << std::endl;
    _tags = parseTags();
  }
  return _tags;
}

std::map<std::string, Author> YAMLParser::getAuthors() {
  std::cout << "authors" << std::endl;
  if(_authors.size() == 0) {
    std::cout << "Affect Authors." << std::endl;
    _authors = parseAuthors();
  }
  return _authors;
}

void YAMLParser::setTags(std::map<std::string, Tag> tags) {
  _tags = tags;
  _tags_changed = true;
}

void YAMLParser::setAuthors(std::map<std::string, Author> authors) {
  _authors = authors;
  _authors_changed = true;
}

void YAMLParser::setAuthorsPath(std::string path) {
  _authors_path = path;
}

void YAMLParser::setTagsPath(std::string path) {
  _tags_path = path;
}

std::map<std::string, Tag> YAMLParser::parseTags() {
  QFile file(QString::fromStdString(_tags_path));
  if(!file.exists()) qDebug("file not found.");
  else qDebug("file found.");

  YAML::Node node = YAML::LoadFile(_tags_path);
  std::map<std::string, Tag> out;

//  std::cout << std::to_string(node.size()) << std::endl;

  for(YAML::iterator it = node.begin(); it != node.end(); ++it) {
      out.insert(std::pair<std::string,Tag>(it->first.as<std::string>(), it->second.as<Tag>()));
  }

  std::cout << "parsed tags" << endl;

  return out;
}

std::map<std::string, Author> YAMLParser::parseAuthors() {
  QFile file(QString::fromStdString(_authors_path));
  if(!file.exists()) qDebug("file not found.");
  else qDebug("file found.");

  YAML::Node node = YAML::LoadFile(_authors_path);
  std::map<std::string, Author> out;

  for(YAML::iterator it = node.begin(); it != node.end(); ++it) {
    out.insert(std::pair<std::string, Author>(it->first.as<std::string>(), it->second.as<Author>()));
  }

  std::cout << "parsed authors" << endl;

  return out;
}

bool YAMLParser::save() {
  return saveTags() & saveAuthors();
}

bool YAMLParser::saveTags() {
  if(!_tags_changed) {
    std::cout << "tags didn't change" << std::endl;
    return true;
  }

  YAML::Node root;
  for(auto it = _tags.begin(); it != _tags.end(); it++) {
    root[it->first] = it->second;
  }

  std::ofstream file_out("_tags_path.yml", std::ios::out);

  file_out << root;
  file_out.close();

  std::cout << root;

  return true;
}

bool YAMLParser::saveAuthors() {
  if(!_authors_changed) return true;

  YAML::Node root;
  for(auto it = _authors.begin(); it != _authors.end(); it++) {
    root[it->first] = it->second;
  }

  std::ofstream file_out("_authors_path.yml", std::ios::out);

  file_out << root;
  file_out.close();

  std::cout << root;


  return true;
}

