/**
 * @file      Employees.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Employees header file
 * @version   0.1
 * @date      2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/Employees.hpp
 * Employees.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_HPP__
#define __EMPLOYEES_HPP__
#define EMAIL_MATCHER_PATTERN "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"

//? Include prototype declaration part
//* Include custom header(s)
#include "../inc/Database.hpp"

//? Namespaces declaration part

/**
 * @namespace Employees
 * @brief     Employees namespace
 */
namespace Employees {

/**
 * @enum  EmployeeQueueFlags_integers
 * @brief EmployeeQueueFlags_integers enum
 */
enum EmployeeQueueFlags_integers {
  EMPLOYEE_ID, //!< 0
  SALARY,      //!< 1
  PHONE_NUMBER //!< 2
}; // EmployeeQueueFlags_integers enum

/**
 * @enum  EmployeeQueueFlags_strings
 * @brief EmployeeQueueFlags_strings enum
 */
enum EmployeeQueueFlags_strings {
  USERNAME,          //!< 0
  FIRSTNAME,         //!< 1
  LASTNAME,          //!< 2
  EMAIL,             //!< 3
  JOBTITLE,          //!< 4
  STATUS,            //!< 5
  PASSWORD,          //!< 6
  ADDRESS,           //!< 7
  DEPARTMENT,        //!< 8
  PROFILE_IMAGE_PATH //!< 9
}; // EmployeeQueueFlags_strings enum

/**
 * @enum  EmployeeQueueFlags_dates
 * @brief EmployeeQueueFlags_dates enum
 */
enum EmployeeQueueFlags_dates {
  HIRE_DATE, //!< 0
  BIRTHDATE  //!< 1
}; // EmployeeQueueFlags_dates enum

/**
 * @enum  EmployeeQueueFlags_timestamps
 * @brief EmployeeQueueFlags_timestamps enum
 */
enum EmployeeQueueFlags_timestamps {
  LAST_LOGIN,         //!< 0
  LAST_PASSWORD_RESET //!< 1
}; // EmployeeQueueFlags_timestamps enum

/**
 * @enum  EmployeeQueueFlags_blobs
 * @brief EmployeeQueueFlags_blobs enum
 */
enum EmployeeQueueFlags_blobs {}; // EmployeeQueueFlags_blobs enum

/**
 * @enum  EmployeeCheckerFlags
 * @brief EmployeeCheckerFlags enum
 */
enum EmployeeCheckerFlags {
  EMPTY = -1,                 //!< -1
  OK,                         //!< 0
  REFUSED,                    //!< 1
  UNIQUE_EMAIL,               //!< 2
  UNIQUE_EMAIL_WITH_EXCEPTION //!< 3
}; // EmployeeCheckerFlags enum

/**
 * @enum  EmployeesStatusFlags
 * @brief EmployeesStatusFlags enum
 */
enum EmployeeStatusFlags {
  ALL,      //!< 0
  ACTIVE,   //!< 1
  INACTIVE, //!< 2
  SUSPENDED //!< 3
}; // EmployeesStatusFlags

/**
 * @enum  EmployeeDepartmentFlags
 * @brief EmployeeDepartmentFlags enum
 */
enum EmployeeDepartmentFlags {
  COMMERCIAL, //!< 0
  SHOPS,      //!< 1
  PARTNERS,   //!< 2
  EVENTS,     //!< 3
  PERSONALS,  //!< 4
  EMPLOYEES   //!< 5
}; // EmployeeDepartmentFlags

std::string EmployeeStatusString(const EmployeeStatusFlags &);
template <typename T>
struct EmployeeInfo;
class Setup;
class Select;
class Insert;
class Update;
class Delete;
class EmployeeChecker;
} // namespace Employees

//? Structure declaration part

/**
 * @struct Employees::EmployeeInfo
 * @brief  EmployeeInfo struct
 */
template <typename T>
struct Employees::EmployeeInfo {
  T data;
  std::string arg;
  explicit EmployeeInfo(const T &,
                        const Employees::EmployeeQueueFlags_integers &);
  explicit EmployeeInfo(const T &,
                        const Employees::EmployeeQueueFlags_strings &);
  explicit EmployeeInfo(const T &, const Employees::EmployeeQueueFlags_dates &);
  explicit EmployeeInfo(const T &,
                        const Employees::EmployeeQueueFlags_timestamps &);
}; // EmployeeInfo struct

//? Class(es) prototype declaration part

/**
 * @class Employees::Setup
 * @brief Generale database setup
 */
class Employees::Setup {
protected:
  Database *db;

public:
  Setup();
  virtual ~Setup();
}; // Employees::Setup class

/**
 * @class Employees::Select
 * @brief C`R`UD
 */
class Employees::Select : private Employees::Setup {
public:
  //* Employees::Select functions
  std::vector<SqlParam> selectAll();
  std::vector<SqlParam> selectAll(const Employees::EmployeeInfo<std::string> &);
  std::vector<SqlParam> selectAll(const Employees::EmployeeInfo<std::string> &,
                                  const Employees::EmployeeInfo<std::string> &);
  std::vector<SqlParam>
  selectAllExcept(const Employees::EmployeeInfo<std::string> &);
  std::vector<SqlParam>
  selectAllExcept(const Employees::EmployeeInfo<std::string> &,
                  const Employees::EmployeeInfo<std::string> &);
  std::vector<SqlParam> selectLastInsertedRow();
}; // Employees::Select class

/**
 * @class Employees::Insert
 * @brief Insert new employee
 */
class Employees::Insert : private Employees::Setup {
public:
  //* Employees::Insert function(s)
  int insert(const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &);

  int insert(const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<int> &,
             const Employees::EmployeeInfo<int> &,
             const Employees::EmployeeInfo<oracle::occi::Date> &);
}; // Employees::Insert class

/**
 * @class Employees::Update
 * @brief CR`U`D
 */
class Employees::Update : private Employees::Setup {
public:
  //* Employees::Update functions
  int update(const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &);

  int update(const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &);

  int update(const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<std::string> &,
             const Employees::EmployeeInfo<int> &,
             const Employees::EmployeeInfo<int> &,
             const Employees::EmployeeInfo<oracle::occi::Date> &);
  ;
}; // Employees::Update class

/**
 * @class Employees::Delete
 * @brief CRU`D`
 */
class Employees::Delete : private Employees::Setup {
public:
  //* Employees::Delete functions
  int del(const Employees::EmployeeInfo<std::string> &);
}; // Employees::Delete class

/**
 * @class Employees::EmployeeChecker
 * @brief Check the passed employees data
 */
class Employees::EmployeeChecker {
private:
  static bool is_validEmail(const std::string &);
  static bool is_empty(const std::string &, const std::string &,
                       const std::string &, const std::string &,
                       const std::string &);
  static bool is_alphaDigit(const std::string &);

public:
  static std::pair<Employees::EmployeeCheckerFlags, const char *> is_valid(
      const std::string &, const std::string &, const std::string &,
      const std::string &, const std::string &, std::string status,
      const std::pair<Employees::EmployeeCheckerFlags, const char *> &flag = {
          Employees::EmployeeCheckerFlags::EMPTY, ""});
}; // EmployeeChecker class

#if __has_include("../templates/Employees.tpp")
#include "../templates/Employees.tpp"
#else
#error "Employees.tpp not found!"
#endif

#endif // __EMPLOYEES_HPP__
