#ifndef IMAGEPICKER_CPP
#define IMAGEPICKER_CPP

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <QtDebug>

#include "texteditor.h"
#include "imagepicker.h"
#include "mainwindow.h"
#include "parser.h"
#include "tags.h"
#include "app_settings.h"
#include "authors.h"
#include "tagselector.h"
#include "tagedit.h"

MainWindow::MainWindow()
{
  this->setWindowTitle("Site Helper");

  init();
}

void MainWindow::init() {
  // Set Layout.
  QVBoxLayout *layout = new QVBoxLayout();

  // Post button.
  m_button_post = new QPushButton(tr("New Post"));
  layout->addWidget(m_button_post);
  layout->setAlignment(m_button_post, Qt::AlignHCenter);
  connect(m_button_post, SIGNAL(released()), this, SLOT(newPost()));

  // Settings button.
  m_button_settings = new QPushButton(tr("Settings"));
  layout->addWidget(m_button_settings);
  layout->setAlignment(m_button_settings, Qt::AlignHCenter);
  connect(m_button_settings, SIGNAL(released()), this, SLOT(siteSettings()));

  // Ttorial button
  m_button_tutorial = new QPushButton(tr("Tutorial"));
  layout->addWidget(m_button_tutorial);
  layout->setAlignment(m_button_tutorial, Qt::AlignHCenter);
  connect(m_button_tutorial, SIGNAL(released()), this, SLOT(tutorial()));

  // About button.
  m_button_about = new QPushButton(tr("About"));
  layout->addWidget(m_button_about);
  layout->setAlignment(m_button_about, Qt::AlignHCenter);
  connect(m_button_about, SIGNAL(released()), this, SLOT(about()));

  // Close button.
  m_close = new QPushButton(tr("Exit"));
  layout->addWidget(m_close);
  layout->setAlignment(m_close, Qt::AlignHCenter);
  connect(m_close, SIGNAL(released()), this, SLOT(close()));


  // Set layout.
  this->setLayout(layout);
}


//### Slots ###

void MainWindow::newPost() {
  TextEditor *editor = new TextEditor();
  editor->show();
}

void MainWindow::siteSettings() {
//  QMessageBox *box = new QMessageBox(this);
//  box->setWindowTitle(tr("Site Settings"));
//  box->setText(tr("Site settings dev box."));
//  box->show();
  TagEdit *edit = new TagEdit();
  edit->show();
}

void MainWindow::about() {
//  QMessageBox *box = new QMessageBox(this);
//  box->setWindowTitle(tr("About"));
//  box->setText(tr("About dev box."));
//  box->show();

  ImagePicker *pic = new ImagePicker();
  pic->show();
}

void MainWindow::tutorial() {
//  QMessageBox *box = new QMessageBox(this);
//  box->setWindowTitle(tr("Tutorial"));
//  box->setText(tr("This is how to use the app ..."));
//  box->show();
  TagSelector *selector = new TagSelector();
  selector->show();

  qDebug("ok");
}

#endif

