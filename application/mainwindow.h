#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QDialog>

class MainWindow : public QDialog
{
  Q_OBJECT
public:
  MainWindow();

private slots:
  void newPost();
  void siteSettings();
  void about();
  void tutorial();

signals:

public slots:

private:
   void init();

   QPushButton *m_button_post;
   QPushButton *m_button_settings;
   QPushButton *m_button_tutorial;
   QPushButton *m_button_about;
   QPushButton *m_close;
};

#endif // MAINWINDOW_H
