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

// ? Include prototype declaration part
#include "../inc/connect.hpp"

// ? Namespaces declaration part
namespace Employees {
enum EmployeeQueueFlags_integers {
  EMPLOYEE_ID,
  SALARY
}; // EmployeeQueueFlags_integers enum
enum EmployeeQueueFlags_strings {
  USERNAME,
  FIRSTNAME,
  LASTNAME,
  EMAIL,
  JOBTITLE,
  STATUS,
  PASSWORD,
  PHONE_NUMBER,
  ADDRESS,
  DEPARTMENT
}; // EmployeeQueueFlags_strings enum
enum EmployeeQueueFlags_dates {
  HIRE_DATE,
  BIRTHDATE
}; // EmployeeQueueFlags_dates enum
enum EmployeeQueueFlags_timestamps {
  LAST_LOGIN,
  LAST_PASSWORD_RESET
}; // EmployeeQueueFlags_timestamps enum
enum EmployeeQueueFlags_blobs {
  PROFILE_IMAGE
}; // EmployeeQueueFlags_blobs enum

struct EmployeeInfo;
class Setup;
class Select;
class Insert;
class Update;
class Delete;
} // namespace Employees

// ? Structure declaration part
struct Employees::EmployeeInfo {
  std::string data;
  std::string arg;
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags_integers &);
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags_strings &);
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags_dates &);
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags_timestamps &);
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags_blobs &);
}; // EmployeeInfo struct

// ? Classes prototype declaration part

class Employees::Setup {
protected:
  Database *db;
  std::vector<SqlParam> *result;

public:
  Setup();
  ~Setup();
}; // Employees::Setup class

class Employees::Select : private Employees::Setup {
public:
  // Employees::Select Constructor and destructor
  Select();
  ~Select();

  // * Employees::Select functions
  std::vector<SqlParam> selectAll(const Employees::EmployeeInfo &);
  std::vector<SqlParam> selectAll(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &);
  std::vector<SqlParam> selectAllExcept(const Employees::EmployeeInfo &);
  std::vector<SqlParam> selectLastInsertedRow();
}; // Employees::Select class

class Employees::Insert : private Employees::Setup {
public:
  // Employees::Select Constructor and destructor
  Insert();
  ~Insert();

  // * Employees::Insert functions
  int insertReq(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &);
}; // Employees::Insert class

class Employees::Update : private Employees::Setup {
public:
  // Employees::Update Constructor and destructor
  Update();
  ~Update();

  // * Employees::Update functions
  int update(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &);
}; // Employees::Update class

class Employees::Delete : private Employees::Setup {
public:
  // Employees::Update Constructor and destructor
  Delete();
  ~Delete();

  // * Employees::Update functions
  int del(const Employees::EmployeeInfo &);
}; // Employees::Update class

#endif // __EMPLOYEES_HPP__