#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <tuple>
#include <yaml-cpp/yaml.h>
#include <QFile>
#include <QString>

#include "tags.h"
#include "app_settings.h"

Tags Tags::_instance = Tags();

Tags::Tags(std::map<std::string, Tag> tags) : _tags(tags) {
  _path = AppSettings::instance()->tagsPath();
}

Tags::Tags() {
  _path = AppSettings::instance()->tagsPath();
  parse();
}

Tags* Tags::instance() {
  if(_instance._path.size() == 0) _instance._path = AppSettings::instance()->tagsPath();
  if(_instance._tags.size() == 0) _instance.parse();
  return &_instance;
}

std::map<std::string, Tag> * Tags::get() {
  return &_tags;
}

void Tags::set(std::map<std::string, Tag> tags) {
  _tags = tags;
  _changed = true;
}

bool Tags::parse() {
  std::cout << "parsing tags" << std::endl;
  std::cout << "Path:" << _path << std::endl;


  QFile file(QString::fromStdString(_path));
  if(!file.exists()) return false;


  YAML::Node node = YAML::LoadFile(_path);
  std::map<std::string, Tag> out;

  for(YAML::iterator it = node.begin(); it != node.end(); ++it) {
      out.insert(std::pair<std::string,Tag>(it->first.as<std::string>(), it->second.as<Tag>()));
  }

  std::cout << "parsed tags" << std::endl;

  _tags = out;
  return true;
}

//bool Tags::changeTag(std::string name, Tag tag) {
//  auto it = _tags.find(name);

//  if(it == _tags.end())
//    return addTag(tag);

//  _changed = true;

//  if(_tags.at(name).name() == tag.name()) {
//    _tags.at(name).setDescription(tag.description());
//    _tags.at(name).setCover(tag.cover());
//    return true;
//  }

//  Tag tmp = _tags.at(name);
//  _tags.erase(it);
//  _tags.insert(std::pair<std::string, Tag>(tag.name(), tag));
//  return true;
//}

//bool Tags::changedTag(std::string name) {
//  if(_tags.find(name) == _tags.end()) return false;

//  _changed = true;

//  if(_tags.at(name).name() == name) return true;

//  auto nodeHandler = _tags.extract(name);
//  nodeHandler.key() = nodeHandler.mapped().name();
//  _tags.insert(std::move(nodeHandler));
//  return true;
//}

bool Tags::addTag(Tag tag) {
  if(_tags.find(tag.name()) == _tags.end())
    return false;

  _changed = true;

  _tags.insert(std::pair<std::string, Tag>(tag.name(), tag));
  return true;
}

bool Tags::save() {
  if(!(_changed || changed())) {
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

  resetChangedTags();
  return true;
}

Tag Tags::getCopy(std::string name) {
  if(_tags.find(name) == _tags.end()) {
    return Tag();
  }
  return Tag(_tags[name]);
}

bool Tags::changed() {
  for(auto it = _tags.begin(); it != _tags.end(); it++) {
    if(it->second.changed()) return true;
  }
  return false;
}

void Tags::resetChangedTags() {
  _changed = false;
  for(auto it = _tags.begin(); it != _tags.end(); it ++) {
    it->second.resetChanged();
  }
}

bool Tags::removeTag(std::string name) {
  auto it = _tags.find(name);
  if(it == _tags.end()) return false;
  _tags.erase(it);
}

void Tags::sort() {

}

