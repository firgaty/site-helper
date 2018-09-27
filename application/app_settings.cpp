#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <QFile>
#include <QString>
#include "tags.h"
#include "app_settings.h"

AppSettings AppSettings::_instance = AppSettings();

AppSettings* AppSettings::instance() {
  return &_instance;
}

bool AppSettings::parse() {
  std::cout << "parsing app settings" << std::endl;

  QFile file(QString::fromStdString(_path));
  if(!file.exists()) return false;


  YAML::Node node = YAML::LoadFile(_path);
  if(node["tags_path"].IsDefined()){
      setTagsPath(node["tags_path"].as<std::string>(), true);
      std::cout << "tags_path" << _tags_path << std::endl;
    }
  if(node["authors_path"].IsDefined())
    setAuthorsPath(node["authors_path"].as<std::string>(), true);
  if(node["image_picker_dir"].IsDefined())
    setImagePickerDir(node["image_picker_dir"].as<std::string>(), true);
  if(node["project_path"].IsDefined())
    setProjectPath(node["project_path"].as<std::string>(), true);
  if(node["settings_path"].IsDefined())
    setSettingsPath(node["settings_path"].as<std::string>(), true);

  std::cout << "parsed app settings" << std::endl;

  return true;
}

bool AppSettings::save() {
  if(!_changed) {
    std::cout << "tags didn't change" << std::endl;
    return true;
  }

  YAML::Node node;

  node["tags_path"]         = tagsPath();
  node["authors_path"]      = authorsPath();
  node["image_picker_dir"]  = settingsPath();
  node["project_path"]      = projectPath();
  node["settings_path"]     = settingsPath();

  std::ofstream file_out("_app_settings.yml", std::ios::out);

  file_out << node;
  file_out.close();

  std::cout << node;

  _changed = false;
  return true;
}
