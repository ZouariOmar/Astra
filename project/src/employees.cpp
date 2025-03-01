/**
 * @file employees.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Employees management source file
 * @version 0.1
 * @date 2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/employees.cpp employees.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/employees.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new Employees::Employees object
 *
 * @class Employees
 */
Employees::Employees()
    : db(new Database()),
      result(new std::vector<std::vector<std::string>>) {};

/**
 * @brief ### Destroy the Employees::Employees object
 *
 * @details Close oracle 1521 port
 * @class   Employees
 */
Employees::~Employees() {
  delete db;
  db = nullptr;
  delete result;
  result = nullptr;
}

/**
 * @brief ### Return the user data using `username`
 *
 * @class           Employees
 * @param  username {const std::string &}
 * @return          std::vector<std::string>
 */
std::vector<std::string> Employees::select_employee(const std::string &username) {
  *result = db->execute("SELECT * FROM Employees WHERE Username = '" + username + "'");
  return (result->empty()) ? std::vector<std::string>{} : (*result)[0]; // Return the first and the only row
}

/**
 * @brief ### Return the user data using `username` and `password`
 *
 * @details         Use this function for login check
 * @class           Employees
 * @param  username {const std::string &}
 * @param  password {const std::string &}
 * @return          std::vector<std::string>
 */
std::vector<std::string> Employees::select_employee(const std::string &username, const std::string &password) {
  *result = db->execute("SELECT * FROM Employees WHERE Username = '" + username + "' AND Password = '" + password + "'");
  return (result->empty()) ? std::vector<std::string>{} : (*result)[0]; // Return the first and the only row
}