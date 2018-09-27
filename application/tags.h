#ifndef TAGS_H
#define TAGS_H

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

#include "parser.h"

class Tag {
public:
  Tag(std::string name = "", std::string description = "", std::string cover = "") {
    _name = name;
    _description = description;
    _cover = cover;
  }

  Tag(const Tag &t) {
    _name = t.name();
    _description = t.description();
    _cover = t.cover();
  }

  std::string name        () const {return _name;}
  std::string description () const {return _description;}
  std::string cover       () const {return _cover;}
  bool        changed     () const {return _changed;}

  void setName        (std::string name,        bool init = false) {_changed = !init; _name = name;}
  void setDescription (std::string description, bool init = false) {_changed = !init; _description = description;}
  void setCover       (std::string cover,       bool init = false) {_changed = !init; _cover = cover;}
  void resetChanged   () {_changed = false;}

  std::string print() {return "Tag : " + _name;}

private:
  std::string _name;
  std::string _description;
  std::string _cover;
  bool        _changed;
};

class Tags : public Parser{
public:
  std::map<std::string, Tag> *get();
  void set(std::map<std::string, Tag> tags);
  bool addTag(Tag tag);
  bool removeTag(std::string name);
  bool save();
  Tag getCopy(std::string name);
  static Tags *instance();

private:
  Tags(std::map<std::string, Tag> tags);
  Tags();
  bool parse();
  bool changed();
  void resetChangedTags();
  void sort();

  static Tags _instance;

  std::map<std::string, Tag> _tags;
  std::string _path;
};

namespace YAML {
  template<>
  struct convert<Tag> {
    static Node encode(const Tag& tag) {
      Node node;
      node["name"]        = tag.name();
      node["description"] = tag.description();
      node["cover"]       = tag.cover();
      return node;
    }

    static bool decode(const Node& node, Tag& tag) {
      if(!node.IsMap() || node.size() != 3) {
        return false;
      }

      tag.setName(node["name"].as<std::string>(), true);
      if(node["description"].IsDefined())
        tag.setDescription(node["description"].as<std::string>(), true);
      if(node["cover"].IsDefined())
        tag.setCover(node["cover"].as<std::string>(), true);

      return true;
    }
  };
}


#endif // TAGS_H
