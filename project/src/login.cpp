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

/**
 * @brief ### Construct a new Login::Login object
 * 
 * @param parent {QObject *}
 */
Login::Login(QObject *parent)
    : QObject(parent), m_username("Username"), m_password("Password") {
}

/**
 * @brief ### Get the `username`
 * 
 * @return QString 
 */
QString Login::username() const {
  return m_username;
}

/**
 * @brief ### Set the changed `username`
 *
 * @param newUsername {const QString &}
 */
void Login::setUsername(const QString &newUsername) {
  if (m_username != newUsername) {
    m_username = newUsername;
    emit usernameChanged();
  }
}

/**
 * @brief ### Get the `password`
 *
 * @return QString
 */
QString Login::password() const {
  return m_password;
}

/**
 * @brief ### Set the changed `password`
 *
 * @param newPassword {const QString &}
 */
void Login::setPassword(const QString &newPassword) {
  if (m_password != newPassword) {
    m_password = newPassword;
    emit passwordChanged();
  }
}

/**
 * @brief ### Main Login fn
 * @details Verify if the user given info are exist
 */
void Login::login() {
  qDebug() << "Username:" << m_username;
  qDebug() << "Password:" << m_password;
  Database *db = new Database();
  int aff{};
  vector<vector<string>> res = db->execute("SELECT * FROM Employees WHERE Username = '" +
                                               m_username.toStdString() + "' AND Password = '" +
                                               m_password.toStdString() + "'",
                                           aff);
  delete db; // Close oracle 1521 port

  // Verify if given user info (username, password) exists or not
  (!res.empty()) ? emit loginSuccess() : emit loginFailed();
}
