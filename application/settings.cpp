#include <QFileInfo>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QFile>
#include <QFileInfo>

#include "settings.h"

Settings::Settings()
{
  _site_folder_is_valid = setSiteFolder();
//  if(_site_folder_is_valid)
//    parseYAML("_config.yml".);
}

//Settings* Settings::instance() {

//}

bool Settings::setSiteFolder() {
  QSettings settings;

  if(settings.contains("site_folder")) {
    _site_folder = QDir(settings.value("site_folder").toString());

    if(!relativeFileExists("_config.yml")) {
      settings.setValue("site_folder", "");
      return false;
    }

    return true;
  }
  _site_folder = QDir("");
  return false;

}

bool Settings::relativeFileExists(QString relative_path) {
  QFile *file = new QFile(_site_folder.absoluteFilePath(relative_path));
  if(file->exists())
    return true;
  return false;
}

bool Settings::siteFolderIsValid() {
  return _site_folder_is_valid;
}

QString Settings::sitePath() {
  return _site_folder.path();
}

QString Settings::title() {
  return _title;
}

QString Settings::cover() {
  return _cover;
}

QString Settings::logo() {
  return _logo;
}

QString Settings::favicon() {
  return _favicon;
}

QString Settings::baseURL() {
  return _baseURL;
}

QString Settings::twitter() {
  return _twitter;
}

QString Settings::facebook() {
  return _facebook;
}

QString Settings::disqusShortname() {
  return _disqus_shortname;
}

bool Settings::disqusIsActive() {
  return _disqus_is_active;
}

QString Settings::googleAnalytics() {
  return _google_analytics;
}

QString Settings::relativeSource() {
  return _relative_source;
}

QString Settings::destination() {
  return _relative_destination;
}

bool Settings::setSiteFolder(QDir folder) {
  QFileInfo check_file(folder.path() + "/_config.yml");

  if(check_file.exists() && check_file.isFile()) {
    _site_folder = folder;
    return true;
  }
  return false;
}

void Settings::setTitle(QString title) {
  _title = title;
}

void Settings::setCover(QString relative_path) {

}

