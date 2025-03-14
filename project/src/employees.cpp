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

// * ==============================================
// ? === Employees::SetEmployeeInfo Constructor ===
// * ==============================================

/**
 * @brief ### Construct a new Employees::EmployeeInfo::EmployeeInfo object
 *
 * @namespace   Employees
 * @struct      EmployeeInfo
 * @param _data {const std::string &}
 * @param flag  {const Employees::EmployeeQueueFlags_integers &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags_integers &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID:
    arg = "EmployeeID";
    break;
  case Employees::EmployeeQueueFlags_integers::SALARY:
    arg = "Salary";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_integers' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_integers flag passed to EmployeeInfo constructor.");
    break;
  }
}

/**
 * @brief ### Construct a new Employees::EmployeeInfo::EmployeeInfo object
 *
 * @namespace   Employees
 * @struct      EmployeeInfo
 * @param _data {const std::string &}
 * @param flag  {const Employees::EmployeeQueueFlags_strings &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags_strings &flag)
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
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_strings' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_strings flag passed to EmployeeInfo constructor.");
    break;
  }
}

/**
 * @brief ### Construct a new Employees::EmployeeInfo::EmployeeInfo object
 *
 * @namespace   Employees
 * @struct      EmployeeInfo
 * @param _data {const std::string &}
 * @param flag  {const Employees::EmployeeQueueFlags_dates &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags_dates &flag)
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
 * @brief ### Construct a new Employees::EmployeeInfo::EmployeeInfo object
 *
 * @namespace   Employees
 * @struct      EmployeeInfo
 * @param _data {const std::string &}
 * @param flag  {const Employees::EmployeeQueueFlags_timestamps &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags_timestamps &flag)
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

/**
 * @brief ### Construct a new Employees::EmployeeInfo::EmployeeInfo object
 *
 * @namespace   Employees
 * @struct      EmployeeInfo
 * @param _data {const std::string &}
 * @param flag  {const Employees::EmployeeQueueFlags_blobs &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags_blobs &flag)
    : data(_data), arg("") {
  switch (flag) {
  case Employees::EmployeeQueueFlags_blobs::PROFILE_IMAGE:
    arg = "ProfileImage";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags_blobs' flag!" << std::endl;
    throw std::invalid_argument("Invalid EmployeeQueueFlags_blobs flag passed to EmployeeInfo constructor.");
    break;
  }
}

// * ===================================================
// ? ==== / Employees::SetEmployeeInfo Constructor =====
// ? === Employees::Setup Constructor and destructor ===
// * ===================================================

/**
 * @brief ### Construct a new Employees::Setup::Setup object
 *
 * @namespace Employees
 * @class     Setup
 */
Employees::Setup::Setup()
    : db(nullptr),
      result(nullptr) {};

/**
 * @brief ### Destroy the Employees::Setup::Setup object
 *
 * @namespace Employees
 * @class     Setup
 */
Employees::Setup::~Setup() {};

// * =====================================================
// ? === / Employees::Setup Constructor and destructor ===
// ? === Employees::Select Constructor and destructor ====
// * =====================================================

/**
 * @brief ### Construct a new Employees::Employees::Select object
 *
 * @namespace Employees
 * @class     Select
 */
Employees::Select::Select() {
  db = new Database();
  result = new std::vector<SqlParam>;
}

/**
 * @brief ### Destroy the Employees::Employees::Select object
 *
 * @details   Close oracle 1521 port
 * @namespace Employees
 * @class     Select
 */
Employees::Select::~Select() {
  delete db;
  db = nullptr;
  delete result;
  result = nullptr;
}

// * ======================================================
// ? === / Employees::Select Constructor and destructor ===
// ? ============ Employees::Select functions =============
// * ======================================================

/**
 * @brief ### Return all user data where `info`
 *
 * @namespace  Employees
 * @class      Select
 * @param info {const Employees::EmployeeInfo &}
 * @return     std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAll(const Employees::EmployeeInfo &info) {
  if (!db)
    throw std::runtime_error("Database connection is not initialized.");

  return db->execute("SELECT * FROM Employees WHERE " + info.arg + " = :1",
                     SqlParam({{1, info.data}}));
}

/**
 * @brief ### Return all user data where `info_00` and `info_01`
 *
 * @note          ! Use this function for login check
 * @namespace     Employees
 * @class         Select
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAll(const Employees::EmployeeInfo &info_00, const Employees::EmployeeInfo &info_01) {
  return db->execute(
      "SELECT * FROM Employees WHERE " + info_00.arg + " = :1 AND " + info_01.arg + " = :2",
      SqlParam({{1, info_00.data}, {2, info_01.data}}));
}

/**
 * @brief ### Return all user data except where `info`
 *
 * @namespace  Employees
 * @class      Select
 * @param info {const Employees::EmployeeInfo &}
 * @return     std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAllExcept(const Employees::EmployeeInfo &info) {
  return db->execute(
      "SELECT * FROM Employees WHERE " + info.arg + " <> :1",
      SqlParam({}, {{1, std::stoi(info.data)}}));
}

/**
 * @brief ### Select the last inserted employee from the Employees table
 *
 * @namespace  Employees
 * @class      Select
 * @return     std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectLastInsertedRow() {
  return db->execute("SELECT * FROM Employees ORDER BY id DESC LIMIT 1", SqlParam{});
}

// * ======================================================
// ? =========== / Employees::Select functions ============
// ? ==== Employees::Insert constructor and destructor ====
// * ======================================================

/**
 * @brief ### Construct a new Employees::Insert::Insert object
 *
 * @namespace Employees
 * @class     Inset
 */
Employees::Insert::Insert() {
  db = new Database();
  result = new std::vector<SqlParam>;
}

/**
 * @brief ### Destroy the Employees::Insert::Insert object
 *
 * @namespace Employees
 * @class     Inset
 */
Employees::Insert::~Insert() {
  delete db;
  db = nullptr;
  delete result;
  result = nullptr;
}

// * ========================================================
// ? ==== / Employees::Insert constructor and destructor ====
// ? ============== Employees::Insert functions =============
// * ========================================================

int Employees::Insert::insertReq(const Employees::EmployeeInfo &info_00, const Employees::EmployeeInfo &info_01, const Employees::EmployeeInfo &info_02, const Employees::EmployeeInfo &info_03, const Employees::EmployeeInfo &info_04) {
  int aff;
  return db->execute("INSERT INTO Employees (" + info_00.arg + ", " + info_01.arg + ", " + info_02.arg + ", " + info_03.arg + ", " + info_04.arg + ") VALUES (:1, :2, :3, :4, :5)",
                     SqlParam({{1, info_00.data}, {2, info_01.data}, {3, info_02.data}, {4, info_03.data}, {5, info_04.data}}), aff),
         aff;
}

// * ========================================================
// ? ============ / Employees::Insert functions =============
// ? ============= Employees::Update functions ==============
// * ========================================================

/**
 * @brief ### Construct a new Employees::Employees::Update object
 *
 * @namespace Employees
 * @class     Update
 */
Employees::Update::Update() {
  db = new Database();
  result = new std::vector<SqlParam>;
}

/**
 * @brief ### Destroy the Employees::Employees::Update object
 *
 * @details   Close oracle 1521 port
 * @namespace Employees
 * @class     Update
 */
Employees::Update::~Update() {
  delete db;
  db = nullptr;
  delete result;
  result = nullptr;
}

/**
 * @brief ### Update user data where `info_00` and `info_01`
 *
 * @namespace     Employees
 * @class         Update
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        int
 */
int Employees::Update::update(const Employees::EmployeeInfo &info_00, const Employees::EmployeeInfo &info_01) {
  int aff;
  return db->execute("UPDATE Employees SET " + info_00.arg + " = :1 WHERE " + info_01.arg + " = :2", SqlParam({{1, info_00.data}, {2, info_01.data}}), aff), aff;
}

// * ====================================================
// ? =========== / Employees::Update functions ==========
// ? ==== Employees::Delete constructor and destructor ==
// * ====================================================

/**
 * @brief ### Construct a new Employees::Employees::Delete object
 *
 * @namespace Employees
 * @class     Delete
 */
Employees::Delete::Delete() {
  db = new Database();
  result = new std::vector<SqlParam>;
}

/**
 * @brief ### Destroy the Employees::Employees::Delete object
 *
 * @details   Close oracle 1521 port
 * @namespace Employees
 * @class     Delete
 */
Employees::Delete::~Delete() {
  delete db;
  db = nullptr;
  delete result;
  result = nullptr;
}

// * ======================================================
// ? === / Employees::Delete constructor and destructor ===
// ? ============ Employees::Delete functions ===========
// * ======================================================

/**
 * @brief ### Delete user where `info`
 *
 * @param info {const Employees::EmployeeInfo &}
 * @namespace  Employees
 * @class      Delete
 * @return     int
 */
int Employees::Delete::del(const Employees::EmployeeInfo &info) {
  int aff;
  return db->execute("DELETE FROM Employees WHERE " + info.arg + " = :1",
                     SqlParam({{1, info.data}}),
                     aff),
         aff;
}

// * ======================================================
// ? ============ / Employees::Delete functions ===========
// * ======================================================