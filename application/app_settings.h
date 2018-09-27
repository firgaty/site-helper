#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <string>
#include <yaml-cpp/yaml.h>

#include "parser.h"

using namespace std;

class AppSettings : public Parser{
public:
  string tagsPath       () const {return _tags_path;}
  string authorsPath    () const {return _authors_path;}
  string imagePickerDir () const {return _image_picker_dir;}
  string projectPath    () const {return _project_path;}
  string settingsPath   () const {return _settings_path;}
  string appSettingsPath() const {return _path;}

  void setTagsPath      (string path, bool init = false) {_changed = !init; _tags_path = path;}
  void setAuthorsPath   (string path, bool init = false) {_changed = !init; _authors_path = path;}
  void setImagePickerDir(string path, bool init = false) {_changed = !init; _image_picker_dir = path;}
  void setProjectPath   (string path, bool init = false) {_changed = !init; _project_path = path;}
  void setSettingsPath  (string path, bool init = false) {_changed = !init; _settings_path = path;}

  static AppSettings *instance();

  bool save();

private:
  AppSettings() {
    _settings_path    = "";
    _tags_path        = "";
    _authors_path     = "";
    _image_picker_dir = "";
    _project_path     = "";
    parse();
  }

  bool parse();

  string _settings_path;
  string _tags_path;
  string _authors_path;
  string _image_picker_dir;
  string _project_path;

  static AppSettings _instance;

  const string _path = "app_settings.yml";
};




#endif // APPSETTINGS_H
