// ! Lance the Doxygen file comment Her (in VSC - `/** */`)

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

// ? Structure prototype declaration part
/*
 * struct...
 */

class Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
  Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
  explicit Backend(QObject *parent = nullptr);

  QString username() const;
  void setUsername(const QString &newUsername);

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
};

#endif // LOGIN_HPP
