/**
 * @file employees.tpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # `EmployeeInfo` template defintion part
 * @version 0.1
 * @date 2025-03-27
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/templates/employees.tpp employees.tpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_TPP__
#define __EMPLOYEES_TPP__

// ? Include prototype declaration part

// * Include custom header(s)
#include "../inc/employees.hpp"

// * ==============================================
// ? === Employees::SetEmployeeInfo Constructors ==
// * ==============================================

/**
 * @fn          EmployeeInfo(const T &, const Employees::EmployeeQueueFlags_integers &)
 * @brief       Construct a new Employees::EmployeeInfo<T>::EmployeeInfo object
 * @tparam T    <string|int|..>
 * @param _data {const T &}
 * @param flag  {const Employees::EmployeeQueueFlags_integers &}
 */
template <typename T>
Employees::EmployeeInfo<T>::EmployeeInfo(const T &_data, const Employees::EmployeeQueueFlags_integers &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID:
    arg = "EmployeeID";
    break;
  case Employees::EmployeeQueueFlags_integers::SALARY:
    arg = "Salary";
    break;
  case Employees::EmployeeQueueFlags_integers::PHONE_NUMBER:
    arg = "PhoneNumber";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_integers' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_integers flag passed to EmployeeInfo constructor.");
    break;
  }
}

/**
 * @fn          EmployeeInfo(const T &, const Employees::EmployeeQueueFlags_strings &)
 * @brief       Construct a new Employees::EmployeeInfo<T>::EmployeeInfo object
 * @tparam T    <string|int|..>
 * @param _data {const T &}
 * @param flag  {const Employees::EmployeeQueueFlags_strings &}
 */
template <typename T>
Employees::EmployeeInfo<T>::EmployeeInfo(const T &_data, const Employees::EmployeeQueueFlags_strings &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_strings::USERNAME:
    arg = "Username";
    break;
  case Employees::EmployeeQueueFlags_strings::FIRSTNAME:
    arg = "FirstName";
    break;
  case Employees::EmployeeQueueFlags_strings::LASTNAME:
    arg = "LastName";
    break;
  case Employees::EmployeeQueueFlags_strings::EMAIL:
    arg = "Email";
    break;
  case Employees::EmployeeQueueFlags_strings::JOBTITLE:
    arg = "JobTitle";
    break;
  case Employees::EmployeeQueueFlags_strings::STATUS:
    arg = "Status";
    break;
  case Employees::EmployeeQueueFlags_strings::PASSWORD:
    arg = "Password";
    break;
  case Employees::EmployeeQueueFlags_strings::ADDRESS:
    arg = "Address";
    break;
  case Employees::EmployeeQueueFlags_strings::DEPARTMENT:
    arg = "Department";
    break;
  case Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH:
    arg = "ProfileImagePath";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_strings' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_strings flag passed to EmployeeInfo constructor.");
    break;
  }
}

/**
 * @fn          EmployeeInfo(const T &, const Employees::EmployeeQueueFlags_dates &)
 * @brief       Construct a new Employees::EmployeeInfo<T>::EmployeeInfo object
 * @tparam T    <string|int|..>
 * @param _data {const T &}
 * @param flag  {const Employees::EmployeeQueueFlags_dates &}
 */
template <typename T>
Employees::EmployeeInfo<T>::EmployeeInfo(const T &_data, const Employees::EmployeeQueueFlags_dates &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_dates::HIRE_DATE:
    arg = "HireDate";
    break;
  case Employees::EmployeeQueueFlags_dates::BIRTHDATE:
    arg = "BirthDate";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_dates' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_dates flag passed to EmployeeInfo constructor.");
    break;
  }
}

/**
 * @fn          EmployeeInfo(const T &, const Employees::EmployeeQueueFlags_timestamps &)
 * @brief       Construct a new Employees::EmployeeInfo<T>::EmployeeInfo object
 * @tparam T    <string|int|..>
 * @param _data {const T &}
 * @param flag  {const Employees::EmployeeQueueFlags_timestamps &}
 */
template <typename T>
Employees::EmployeeInfo<T>::EmployeeInfo(const T &_data, const Employees::EmployeeQueueFlags_timestamps &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_timestamps::LAST_LOGIN:
    arg = "LastLogin";
    break;
  case Employees::EmployeeQueueFlags_timestamps::LAST_PASSWORD_RESET:
    arg = "LastPasswordReset";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_timestamps' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_timestamps flag passed to EmployeeInfo constructor.");
    break;
  }
}

// * ===================================================
// ? ==== / Employees::SetEmployeeInfo Constructors ====
// * ===================================================

#endif // __EMPLOYEES_TPP__