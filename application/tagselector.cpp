#include <QVBoxLayout>
#include <QSpacerItem>
#include <QComboBox>
#include <QHBoxLayout>
#include <QList>
#include <QCheckBox>
#include <QPair>

#include <map>
#include <string>
#include <iostream>

#include "tagselector.h"
#include "ui_tagselector.h"
#include "tags.h"
#include "tagedit.h"

QList<TagSelector::CheckBool> TagSelector::_boxes = QList<TagSelector::CheckBool>();

TagSelector::TagSelector(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TagSelector)
{
  ui->setupUi(this);
  ui->_edit_combo->setEditable(false);
  connect(ui->_edit_combo, SIGNAL(activated(QString)), this, SLOT(selectedEdit(QString)));

  connect(ui->_select_ok_button, SIGNAL(released()), this, SLOT(ok()));
  connect(ui->_new_tag_button, SIGNAL(released()), this, SLOT(newTag()));
  refreshTags();

  for(auto it = Tags::instance()->get()->begin(); it != Tags::instance()->get()->end(); ++it) {
    std::cout << it->second.name() << std::endl;
  }
}

TagSelector::~TagSelector()
{
  delete ui;
}

void TagSelector::refreshTags() {
  ui->_edit_combo->clear();

  std::map<std::string, Tag> *tags = Tags::instance()->get();
  for(auto it = tags->begin(); it != tags->end(); it++) {
    ui->_edit_combo->addItem(QString::fromStdString(it->first));
    _boxes.append(CheckBool(new QCheckBox(QString::fromStdString(it->first))));
    std::cout << it->first << std::endl;
  }
  setCheckBoxes();
  qDebug("refreshed.");
}

void TagSelector::setCheckBoxes() {
  clearGrid();
  for(int i = 0; i < _boxes.size(); i ++) {
    ui->_select_grid->addWidget(_boxes.at(i).box, i / 3, i % 3);
    connect(_boxes.at(i).box, SIGNAL(clicked()), this, SLOT(boxTicked()));
  }
}

void TagSelector::clearGrid() {
  QLayoutItem *item;
  while((item = ui->_select_grid->takeAt(0))) {
    delete item->widget();
    delete item;
  }
}

void TagSelector::clearSpace() {
  QLayoutItem *item;
  while((item = ui->_tag_edit_space->takeAt(0))) {
      ui->_tag_edit_space->removeItem(item);
      delete item;
  }
}


void TagSelector::boxTicked() {
  _tags_string = tr("Preview :  ");
  for(int i = 0; i < _boxes.size(); i ++) {
    if(_boxes.at(i).box->isChecked())
      _tags_string.append(_boxes.at(i).box->text() + "; ");
  }

  // remove the last 2 chars : "; ".
  _tags_string.remove(_tags_string.size() - 2, 2);
  ui->_select_label->setText(_tags_string);
}

void TagSelector::ok() {
  selectedTags(_tags_string);
  close();
}

void TagSelector::newTag() {
  if(_editor) {
    delete _editor;
  }
  _editor = new TagEdit();
  connect(_editor, SIGNAL(tagSaved()), this, SLOT(refreshTags()));
  ui->_tag_edit_space->addWidget(_editor);
  _editor->show();
}

void TagSelector::selectedEdit(QString name) {
  if(_editor) {
    delete _editor;
  }
  _editor = new TagEdit(&Tags::instance()->get()->at(name.toStdString()));
  connect(_editor, SIGNAL(tagSaved()), this, SLOT(refreshTags()));
  ui->_tag_edit_space->addWidget(_editor);
  _editor->show();
}
