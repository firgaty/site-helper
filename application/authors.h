#ifndef AUTHORS_H
#define AUTHORS_H

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

#include "parser.h"

using namespace std;

class Author
{
public:
  Author(
      string username = "",
      string name = "",
      string location = "",
      string url_full = "",
      string url = "",
      string bio = "",
      string picture = "",
      string facebook = "",
      string twitter = "",
      string cover = ""
      ) {
    _username = username;
    _name = name;
    _location = location;
    _url_full = url_full;
    _url = url;
    _bio = bio;
    _picture = picture;
    _facebook = facebook;
    _twitter = twitter;
    _cover = cover;
  }

  string username()   const {return _username;}
  string name()       const {return _name;}
  string location()   const {return _location;}
  string urlFull()    const {return _url_full;}
  string url()        const {return _url;}
  string bio()        const {return _bio;}
  string picture()    const {return _picture;}
  string facebook()   const {return _facebook;}
  string twitter()    const {return _twitter;}
  string cover()      const {return _cover;}

  void setUsername(string username) {_username = username;}
  void setName    (string name)     {_name = name;}
  void setLocation(string location) {_location = location;}
  void setURLFull (string url)      {_url_full = url;}
  void setURL     (string url)      {_url = url;}
  void setBio     (string bio)      {_bio = bio;}
  void setPicture (string path)     {_picture = path;}
  void setFacebook(string facebook) {_facebook = facebook;}
  void setTwitter (string twitter)  {_twitter = twitter;}
  void setCover   (string path)     {_cover = path;}

  string print() {return "Author : " + _name; }

private:
  string _username;
  string _name;
  string _location;
  string _url_full;
  string _url;
  string _bio;
  string _picture;
  string _facebook;
  string _twitter;
  string _cover;
};

class Authors : public Parser{
public:
  std::map<std::string, Author> get();
  void set(std::map<std::string, Author> authors);
  bool save();
  static Authors *instance();

private:
  Authors(std::map<std::string, Author> authors = std::map<std::string, Author>());
  bool parse();

  static Authors _instance;

  std::map<std::string, Author> _authors;
  std::string _path;
};

namespace YAML {
  template<>
  struct convert<Author> {
    static Node encode(const Author& author) {
      Node node;
      node["username"]  = author.username();
      node["name"]      = author.name();
      node["location"]  = author.location();
      node["url_full"]  = author.urlFull();
      node["url"]       = author.url();
      node["bio"]       = author.bio();
      node["picture"]   = author.picture();
      node["facebook"]  = author.facebook();
      node["twitter"]   = author.twitter();
      node["cover"]     = author.cover();

      return node;
    }

    static bool decode(const Node& node, Author& author) {
      if(!node.IsMap()) {
        return false;
      }

      author.setUsername(node["username"].as<std::string>());
      author.setName(node["name"].as<std::string>());
      if(node["location"].IsDefined())
        author.setLocation(node["location"].as<std::string>());
      if(node["url_full"].IsDefined())
        author.setURLFull(node["url_full"].as<std::string>());
      if(node["url"].IsDefined())
        author.setURL(node["url"].as<std::string>());
      if(node["bio"].IsDefined())
        author.setBio(node["bio"].as<std::string>());
      if(node["picture"].IsDefined())
        author.setPicture(node["picture"].as<std::string>());
      if(node["facebook"].IsDefined())
        author.setFacebook(node["facebook"].as<std::string>());
      if(node["twitter"].IsDefined())
        author.setTwitter(node["twitter"].as<std::string>());
      if(node["cover"].IsDefined())
        author.setCover(node["cover"].as<std::string>());

      return true;
    }
  };
}

#endif // AUTHORS_H
