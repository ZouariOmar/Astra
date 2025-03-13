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
enum EmployeeQueueFlags {
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
}; // EmployeeQueueFlags enum

struct EmployeeInfo;
class Setup;
class Select;
class Insert;
class Update;
} // namespace Employees

// ? Structure declaration part
struct Employees::EmployeeInfo {
  std::string data;
  std::string arg;
  explicit EmployeeInfo(const std::string &, const Employees::EmployeeQueueFlags &);
}; // EmployeeInfo struct

// ? Classes prototype declaration part

class Employees::Setup {
protected:
  Database *db;
  std::vector<std::vector<std::string>> *result;

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
  std::vector<std::string> selectAll(const Employees::EmployeeInfo &);
  std::vector<std::string> selectAll(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &);
  std::vector<std::vector<std::string>> selectAllExcept(const Employees::EmployeeInfo &);
  std::vector<std::string> selectLastInsertedRow();
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

#endif // __EMPLOYEES_HPP__