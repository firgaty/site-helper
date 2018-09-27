#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <map>
#include <string>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTextEdit>

#include "tagedit.h"
#include "tags.h"
#include "imagepicker.h"

TagEdit::TagEdit(QWidget *parent) : QWidget (parent) {
  _tag = new Tag();
  _edit = false;
  init();
}

TagEdit::TagEdit(Tag *tag, QWidget *parent) : _tag(tag), QWidget(parent)
{
  // Set if Edit mode or creation mode.
//  _edit = tag->name().size() == 0;
  _edit = true;
  init();
}

void TagEdit::init() {
  // init all layouts.
  QVBoxLayout *main_layout = new QVBoxLayout();
  QFormLayout *layout = new QFormLayout();
  QHBoxLayout *button_layout = new QHBoxLayout();

  // if edit mode, no name modification is allowed.
  if(_edit) {
    layout->addRow(new QLabel(tr("Name :")), new QLabel(QString::fromStdString(_tag->name())));
  } else {
    _name = new QLineEdit("");
    layout->addRow(new QLabel(tr("Name :")), _name);
  }

  // set the rest.
  _description = new QTextEdit(_edit ? QString::fromStdString(_tag->description()) : "");
  layout->addRow(new QLabel(tr("Description :")), _description);

  _cover_path = new QLabel(_edit ? QString::fromStdString(_tag->cover()) : tr("No path.") );
  QPushButton *image_picker = new QPushButton(tr("Select"));
  layout->addWidget(image_picker);

  // if edit mode we can remove the tag.
  if(_edit) {
    QPushButton *remove = new QPushButton(tr("Remove"));
    button_layout->addWidget(remove);
    connect(remove, SIGNAL(released()), this, SLOT(remove()));
  }

  // other buttons.
  QPushButton *cancel = new QPushButton(tr("Cancel"));
  QPushButton *save = new QPushButton(tr("Save"));

  // add everything to the layouts.
  button_layout->addWidget(cancel);
  button_layout->addWidget(save);

  main_layout->addLayout(layout);
  main_layout->addLayout(button_layout);

  // Connection time.
  connect(image_picker, SIGNAL(released()), this, SLOT(imagePicker()));
  connect(cancel, SIGNAL(released()), this, SLOT(cancel()));
  connect(save, SIGNAL(released()), this, SLOT(save()));

  this->setLayout(main_layout);
  this->setWindowTitle(tr("Tag Editor"));
  this->show();
}

void TagEdit::remove() {
  Tags::instance()->removeTag(_name->text().toStdString());
}

void TagEdit::cancel() {
  this->close();
}

void TagEdit::save() {
  _tag->setDescription(_description->toPlainText().toStdString());
  _tag->setCover(_cover_path->text().toStdString());
  if(_edit) {
    _tag->setName(_name->text().toStdString());
    Tags::instance()->addTag(*_tag);
  }
  tagSaved();
}

void TagEdit::imagePicker() {
  ImagePicker *picker = new ImagePicker();
  connect(picker, SIGNAL(closedOk(QString)), this, SLOT(setImagePath(QString)));
  picker->show();
}

void TagEdit::setImagePath(QString path) {
  _cover_path->setText(path);
}
