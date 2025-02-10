// ! Lance the Doxygen file comment Her (in VSC - `/** */`)

//? Include prototype declaration part
#include "../inc/login.hpp"

//? Function/Class prototype dev part

Backend::Backend(QObject *parent)
    : QObject(parent) {
}

QString Backend::username() const {
  return m_username;
}

void Backend::setUsername(const QString &newUsername) {
  if (m_username != newUsername) {
    m_username = newUsername;
    emit usernameChanged();
  }
}

QString Backend::password() const {
  return m_password;
}

void Backend::setPassword(const QString &newPassword) {
  if (m_password != newPassword) {
    m_password = newPassword;
    emit passwordChanged();
  }
}

void Backend::login() {
  qDebug() << "Attempting login with:";
  qDebug() << "Username:" << m_username;
  qDebug() << "Password:" << m_password;

  // Simple login logic (replace with real authentication)
  if (m_username == "admin" && m_password == "1234") {
    qDebug() << "Login successful!";
    emit loginSuccess();
  } else {
    qDebug() << "Login failed!";
    emit loginFailed();
  }
}
