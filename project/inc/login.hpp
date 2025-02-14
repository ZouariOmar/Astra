/**
 * @file login.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login header file
 * @version 0.1
 * @date 2025-02-10
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/login.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef LOGIN_HPP
#define LOGIN_HPP

// ? Include prototype declaration part
// * Include std libs (Qt)
#include <qt6/QtCore/QDebug>
#include <qt6/QtCore/QObject>

// * Include std libs (C++)
#include <iostream>

// * Use stander workspace
using namespace std;

// ? Classes prototype declaration part
class Login : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
  Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
  explicit Login(QObject *parent = nullptr);
  
  // Username read and write fn
  QString username() const;
  void setUsername(const QString &newUsername);

  // Password read and write fn
  QString password() const;
  void setPassword(const QString &newPassword);

  Q_INVOKABLE void login(); // Function to process login

signals:
  void usernameChanged();
  void passwordChanged();
  void loginSuccess();
  void loginFailed();

private:
  QString m_username;
  QString m_password;
}; // Login class

#endif // LOGIN_HPP
