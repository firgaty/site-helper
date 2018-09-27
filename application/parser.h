#ifndef PARSER_H
#define PARSER_H

class Parser {
public:
  Parser() {_changed = false;}
  virtual bool save() {return true;}
  virtual ~Parser() {}
  bool changed() const {return _changed;}
protected:
  virtual bool parse() {return true;}
  bool _changed;
};

#endif // PARSER_H
