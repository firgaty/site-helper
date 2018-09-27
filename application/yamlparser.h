#ifndef YAMLPARSER_H
#define YAMLPARSER_H

#include "tags.h"
#include "authors.h"
#include "app_settings.h"
#include "yaml-cpp/yaml.h"
#include <deque>
#include <map>

class YAMLParser
{
public:
  std::map<std::string, Tag> getTags();
  std::map<std::string, Author> getAuthors();
  AppSettings getAppSettings();

  void setTags(std::map<std::string, Tag> tags);
  void setAuthors(std::map<std::string, Author> authors);

  static YAMLParser *instance() {
    if(!_instance) {
        _instance = new YAMLParser();
    }
    return _instance;
  }

  void setTagsPath(std::string path);
  void setAuthorsPath(std::string path);

  bool save();
  
private:
  YAMLParser(std::map<std::string, Tag> tags = std::map<std::string, Tag>(), std::map<std::string, Author> authors = std::map<std::string, Author>());

  static YAMLParser *_instance;

  bool saveTags();
  bool saveAuthors();

  std::map<std::string, Tag> parseTags();
  std::map<std::string, Author> parseAuthors();
  AppSettings parseAppSettings();

  std::string _tags_path;
  std::string _authors_path;
  
  std::map<std::string, Tag> _tags;
  std::map<std::string, Author> _authors;

  bool _tags_changed;
  bool _authors_changed;
};


#endif // YAMLPARSER_H
