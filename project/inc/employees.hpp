/**
 * @file employees.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Employees management header file
 * @version 0.1
 * @date 2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/employees.hpp employees.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_HPP__
#define __EMPLOYEES_HPP__

//? Include prototype declaration part
#include "../inc/connect.hpp"

// ? Structure declaration part
enum EmployeeQueue {
  EMPLOYEE_ID,
  USERNAME,
  FIRSTNAME,
  LASTNAME,
  EMAIL,
  JOBTITLE,
  SALARY,
  HIRE_DATE,
  STATUS,
  PASSWORD,
  PROFILE_IMAGE,
  PHONE_NUMBER,
  ADDRESS,
  BIRTHDATE,
  DEPARTMENT,
  LAST_LOGIN,
  LAST_PASSWORD_RESET
}; // EmployeeQueue enum

// ? Include prototype declaration part
// * Include std C++ headers

class Employees {
private:
  Database *db;
  std::vector<std::vector<std::string>> *result;

public:
  // Employees Constructor and destructor
  Employees();
  ~Employees();

  // * Employees `SELECT` functions
  std::vector<std::string> select_employee(const std::string &);
  std::vector<std::string> select_employee(const std::string &, const std::string &);

  // * Employees `UPDATE` functions

public:
}; // Employees class

#endif // __EMPLOYEES_HPP__