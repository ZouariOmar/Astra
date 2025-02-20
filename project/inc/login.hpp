/**
 * @file login.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login header file
 * @version 0.1
 * @date 2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/login.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__
#define __LOGIN_GIF_ANIMATION__ 5000 // 5sec
#define __START_LG_Q_LABEL_X__ 210   // Start l QLabel x position = 210px
#define __END_LG_Q_LABEL_X__ 330     // End l QLabel x position = 210px

// ? Include prototype declaration part
// * Include std libs (Qt)
#include <QtCore/QDebug>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QMovie>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

// Include generated .h files
#include "../ui/ui_login.h"

// * Use stander workspace
using namespace std;

// ? Classes prototype declaration part

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow {
  Q_OBJECT

public:
  explicit Login(QWidget *parent = nullptr);
  ~Login();

private: // ? Private vars
  Ui::MainWindow *ui;
  const QStringList gifPaths;
  int currentGifIndex;
  QTimer *gifTimer;
  QMovie *currentMovie;

private: // ? Private fns
  void updateGif();
  bool eventFilter(QObject *, QEvent *) override;

private slots:
  void on_pushButton_clicked();
  // void onLoginSuccessful();

signals:
  void loginSuccessful(); // Signal to notify successful login
}; // Login class

#endif // __LOGIN_HPP__
