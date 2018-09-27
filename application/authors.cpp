#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <QFile>
#include <QString>
#include "authors.h"
#include "app_settings.h"

Authors Authors::_instance = Authors();

Authors::Authors(std::map<std::string, Author> authors) : _authors(authors) {
  _path = AppSettings::instance()->authorsPath();
}

Authors* Authors::instance() {
  if(_instance._path.size() == 0) _instance._path = AppSettings::instance()->authorsPath();
  if(_instance._authors.size() == 0) _instance.parse();
  return &_instance;
}

std::map<std::string, Author> Authors::get() {
  return _authors;
}

void Authors::set(std::map<std::string, Author> authors) {
  _authors = authors;
  _changed = true;
}

bool Authors::parse() {
  QFile file(QString::fromStdString(_path));
  if(!file.exists()) return false;

  YAML::Node node = YAML::LoadFile(_path);
  std::map<std::string, Author> out;

  for(YAML::iterator it = node.begin(); it != node.end(); ++it) {
    out.insert(std::pair<std::string, Author>(it->first.as<std::string>(), it->second.as<Author>()));
  }

  std::cout << "parsed authors" << endl;

  _authors = out;

  return true;
}

bool Authors::save() {
  if(!_changed) return true;

  YAML::Node root;
  for(auto it = _authors.begin(); it != _authors.end(); it++) {
    root[it->first] = it->second;
  }

  std::ofstream file_out("_authors_path.yml", std::ios::out);

  file_out << root;
  file_out.close();

  std::cout << root;

  _changed = false;
  return true;
}
