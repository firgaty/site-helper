#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "texteditor.h"
#include <QMessageBox>

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

  // About button.
  m_button_about = new QPushButton(tr("About"));
  layout->addWidget(m_button_about);
  layout->setAlignment(m_button_about, Qt::AlignHCenter);
  connect(m_button_about, SIGNAL(released()), this, SLOT(about()));

  // Set layout.
  this->setLayout(layout);
}


//### Slots ###

void MainWindow::newPost() {
  TextEditor *editor = new TextEditor();
  editor->show();
}

void MainWindow::siteSettings() {
  QMessageBox *box = new QMessageBox(this);
  box->setWindowTitle(tr("Site Settings"));
  box->setText(tr("Site settings dev box."));
  box->show();
}

void MainWindow::about() {
  QMessageBox *box = new QMessageBox(this);
  box->setWindowTitle(tr("About"));
  box->setText(tr("About dev box."));
  box->show();
}


