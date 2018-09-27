#ifndef IMAGEPICKER_H
#define IMAGEPICKER_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <tuple>
#include <QLineEdit>
#include <QTextEdit>

#include "texteditor.h"

class ImagePicker : public QWidget
{
  Q_OBJECT
public:
//  explicit ImagePicker(QWidget *parent = nullptr);
  explicit ImagePicker(bool has_alt = false, bool has_caption = false, QWidget *parent = nullptr);

private slots:
  void selectImage();
  void setImage(QImage &image);
  void closeAbort();
  void closeOk();
  
public slots:

signals:
  void closedOk(QString, QString, QString);
  void closedOk(QString);

private:
  QLabel      *m_img_tumbnail       = nullptr;
  QLabel      *m_path_label         = nullptr;
  QPushButton *m_button_abort       = nullptr;
  QPushButton *m_button_ok          = nullptr;
  QPushButton *m_button_img_select  = nullptr;
  QString     *m_path               = nullptr;
  QLineEdit   *m_alt                = nullptr;
  QTextEdit   *m_caption            = nullptr;

  bool m_has_alt, m_has_caption;

};

#endif // IMAGEPICKER_H
