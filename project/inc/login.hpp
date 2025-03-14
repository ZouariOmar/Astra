/**
 * @file login.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login header file
 * @version 0.1
 * @date 2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/login.hpp login.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__
#define __LOGIN_GIF_ANIMATION__ 5000 // 5sec
#define __START_LG_Q_LABEL_X__ 210   // Start l QLabel x position = 210px
#define __END_LG_Q_LABEL_X__ 330     // End l QLabel x position = 210px
#define __FULL_VISIBLE__ 1.0         // Fully visible (opacity)
#define __FULL_TRANSPARENT__ 0.0     // Fully transparent (opacity)

// ? Include prototype declaration part
// * Include std headers (Qt)
#include <QtConcurrent/QtConcurrent>
#include <QtCore/QDebug>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QMovie>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>

#include "../inc/employees.hpp"

// Include generated .ui files
#include "../ui/ui_login.h"

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
  std::vector<SqlParam> get_employee();

private: // ? Private vars
  Ui::Login *ui;
  const QStringList gifPaths;
  int currentGifIndex;
  QTimer *gifTimer;
  QMovie *currentMovie;
  std::string generated_password;
  std::vector<SqlParam> employee;

private: // ? Private fns
  // * Events
  bool
  eventFilter(QObject *, QEvent *) override;
  bool forget_password_events(QObject *, QEvent *);
  bool login_btn_events(QObject *, QLabel *, QEvent *);

  // * Effects
  void updateGif();
  void QGroupBoxFadeOutEffect(QGroupBox *, QGroupBox *);
  QPropertyAnimation *FadeEffect(QGroupBox *, const QVariant, const QVariant);
  void change_hideShowBtnIcon(QLineEdit *, QPushButton *, const QLineEdit::EchoMode mode = QLineEdit::Password, const QString path = "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/closedEye.png");

  // * Helpers
  void enableResetPassword(const bool &);
  void clearResetPassword();

private slots: // ? Private slots fns
  // * Login sub-inteface group box slots
  void on_pushButton_clicked();
  void on_hide_show_btn_clicked();
  void on_reset_clicked();

  // * Forget password sub-inteface group box slots
  void on_hide_show_btn_2_clicked();
  void on_returnBtn_clicked();
  void on_sendEmailBtn_clicked();

signals: // ? Signals fns
  // * Login sub-inteface group box signals
  void loginSuccessful(); // Signal to notify successful login
}; // Login class

#endif // __LOGIN_HPP__
