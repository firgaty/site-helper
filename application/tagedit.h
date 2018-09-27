#ifndef TAGEDIT_H
#define TAGEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

#include "tags.h"
#include "imagepicker.h"

class TagEdit : public QWidget
{
  Q_OBJECT
public:
  explicit TagEdit(Tag *tag, QWidget *parent = nullptr);
  TagEdit(QWidget *parent = nullptr);

signals:
//  void tagSaved(Tag);
//  void remove(std::string);
void tagSaved();

public slots:

private slots:
  void setImagePath(QString);
  void remove();
  void cancel();
  void save();
  void imagePicker();

private:
  void init();

  Tag *_tag;
  QLineEdit *_name = nullptr;
  QTextEdit *_description = nullptr;
  QLabel    *_cover_path = nullptr;
  bool _edit;
};

#endif // TAGEDIT_H
