#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <tuple>

#include "imagepicker.h"
#include "texteditor.h"

ImagePicker::ImagePicker(bool has_alt, bool has_caption, QWidget *parent)
  : QWidget (parent), m_has_alt(has_alt), m_has_caption(has_caption) {

  QVBoxLayout *layout = new QVBoxLayout(parent);

  // Image preview
  this->m_img_tumbnail = new QLabel(tr("No image selected"));
  m_img_tumbnail->setGeometry(0, 0, 200, 200);
  layout->addWidget(m_img_tumbnail);
  layout->setAlignment(m_img_tumbnail, Qt::AlignHCenter);

  // Path label
  this->m_path_label = new QLabel(tr("No path selected"));
  layout->addWidget(m_path_label);
  layout->setAlignment(m_path_label, Qt::AlignHCenter);

  // Selector button
  this->m_button_img_select = new QPushButton(tr("Select Image"));
  layout->addWidget(m_button_img_select);
  layout->setAlignment(m_button_img_select, Qt::AlignHCenter);
  this->connect(m_button_img_select, SIGNAL(released()), this, SLOT(selectImage()));

  // Alt text
  if(m_has_alt) {
      QLabel *lab_alt = new QLabel(tr("Alt text :"));
      lab_alt->setMaximumWidth(70);
      this->m_alt = new QLineEdit(tr("alt text"));
      QHBoxLayout *alt_layout = new QHBoxLayout();
      alt_layout->addWidget(lab_alt);
      alt_layout->addWidget(m_alt);
      layout->addLayout(alt_layout);
  }

  // Caption
  if(m_has_caption) {
      QLabel *lab_caption = new QLabel(tr("Caption :"));
      this->m_caption = new QTextEdit(tr("My caption"));
//      QHBoxLayout *caption_layout = new QHBoxLayout();
//      caption_layout->addWidget(lab_caption);
//      caption_layout->addWidget(m_caption);
      layout->addWidget(lab_caption);
      layout->addWidget(m_caption);
      m_caption->setMinimumWidth(200);
      m_caption->setMinimumHeight(100);
  }

  // Ok and Abort Buttons.
  QHBoxLayout *bottomLayout = new QHBoxLayout();

  this->m_button_ok = new QPushButton(tr("Add"));
  bottomLayout->addWidget(m_button_ok);
  bottomLayout->setAlignment(m_button_ok, Qt::AlignVCenter);
  this->connect(m_button_ok, SIGNAL(released()), this, SLOT(closeOk()));

  this->m_button_abort = new QPushButton(tr("Cancel"));
  bottomLayout->addWidget(m_button_abort);
  bottomLayout->setAlignment(m_button_abort, Qt::AlignVCenter);
  this->connect(m_button_abort, SIGNAL(released()), this, SLOT(closeAbort()));

  // Add the layouts.
  layout->addLayout(bottomLayout);
  this->setLayout(layout);

  this->setGeometry(0, 0, 220, 500);
  this->setFixedSize(this->size());
}

void ImagePicker::selectImage() {
  const QString DEFAULT_DIR_KEY("default_dir");

  QSettings my_settings; // Will be using application informations
                            // for correct location of your settings

  QString selectedFile = QFileDialog::getOpenFileName(
        this,
        "Select an image",
        my_settings.value(DEFAULT_DIR_KEY).toString(),
        tr("All files (*.*);;JPEG (*.jpg *.jpeg);; PNG (*.png);; TIFF (*.tif)" )
        );

  if (selectedFile.isEmpty()) {
    QDir CurrentDir;
    my_settings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));
    QMessageBox::critical(nullptr, tr("Error"), tr("Invalid file."));
    return;
  }

  QImage image(selectedFile);
  this->m_path_label->setText(selectedFile);
  this->m_path = &selectedFile;
  this->setImage(image);
}

void ImagePicker::setImage(QImage &image) {
  image = image.scaled(400, 300, Qt::KeepAspectRatio).scaled(200, 150, Qt::KeepAspectRatio);
  QPixmap pix(QPixmap::fromImage(image));
  this->m_img_tumbnail->setPixmap(pix);
}

void ImagePicker::closeAbort() {
  this->close();
}

void ImagePicker::closeOk() {  
  if(m_path == nullptr || *m_path == "") {
    QMessageBox::warning(this, tr("Invalid"), tr("No path chosen"));
    return;
  }

  QString path = m_path_label->text();
  closedOk(path);
  closedOk(path, m_has_alt ? m_alt->text() : "", m_has_caption ? m_caption->toPlainText() : "");

  this->close();
}
