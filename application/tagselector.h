#ifndef TAGSELECTOR_H
#define TAGSELECTOR_H

#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QList>
#include <QCheckBox>

#include "tagedit.h"

namespace Ui {
  class TagSelector;
}

class TagSelector : public QDialog
{
  Q_OBJECT

public:
  explicit TagSelector(QWidget *parent = nullptr);
  ~TagSelector();

  struct CheckBool {
    CheckBool(QCheckBox *box) {this->box = box;}
    QCheckBox *box;
    bool placed = false;
  };

signals:
  void selectedTags(QString);

private slots:
  void ok();
  void newTag();
  void refreshTags();
  void boxTicked();
  void clearGrid();
  void clearSpace();
  void selectedEdit(QString);

private:
  void setCheckBoxes();

  Ui::TagSelector *ui;
  QString _tags_string;
  static QList<CheckBool> _boxes;
  TagEdit *_editor = nullptr;
};



#endif // TAGSELECTOR_H
