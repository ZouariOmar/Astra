/**
 * @file login.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login source file
 * @version 0.1
 * @date 2025-02-10
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/login.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/login.hpp"
#include "../inc/connect.hpp"

//? Function/Class prototype dev part

Login::Login(QObject *parent)
    : QObject(parent), m_username("Username"), m_password("Password") {
}

QString Login::username() const {
  return m_username;
}

void Login::setUsername(const QString &newUsername) {
  if (m_username != newUsername) {
    m_username = newUsername;
    emit usernameChanged();
  }
}

QString Login::password() const {
  return m_password;
}

void Login::setPassword(const QString &newPassword) {
  if (m_password != newPassword) {
    m_password = newPassword;
    emit passwordChanged();
  }
}

void Login::login() {
  qDebug() << "Attempting login with:";
  qDebug() << "Username:" << m_username;
  qDebug() << "Password:" << m_password;
  Database *db = new Database("c##omar", "root", "localhost:1521/orclpdb1");
  int aff{};
  vector<vector<string>> res = db->execute("SELECT * FROM Employees WHERE Username = '" +
                                               m_username.toStdString() + "' AND Password = '" +
                                               m_password.toStdString() + "'",
                                           aff);
  delete db; // Close oracle 1521 port

    if (!res.empty()) { // Verify if given user info (username, password) exists or not
    // Reset m_password and m_username
    m_password = "", m_username = "";
    qDebug() << "Login successful!";
    emit loginSuccess();
  } else {
    // Reset m_password and m_username
    m_password = "", m_username = "";
    qDebug() << "Login failed!";
    emit loginFailed();
  }
}
