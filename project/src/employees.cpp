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
 * @param flag  {const Employees::EmployeeQueueFlags &}
 */
Employees::EmployeeInfo::EmployeeInfo(const std::string &_data, const Employees::EmployeeQueueFlags &flag)
    : data(_data) {
  switch (flag) {
  case Employees::EmployeeQueueFlags::EMPLOYEE_ID:
    arg = "EmployeeID";
    break;
  case Employees::EmployeeQueueFlags::USERNAME:
    arg = "Username";
    break;
  case Employees::EmployeeQueueFlags::FIRSTNAME:
    arg = "FirstName";
    break;
  case Employees::EmployeeQueueFlags::LASTNAME:
    arg = "LastName";
    break;
  case Employees::EmployeeQueueFlags::EMAIL:
    arg = "Email";
    break;
  case Employees::EmployeeQueueFlags::JOBTITLE:
    arg = "JobTitle";
    break;
  case Employees::EmployeeQueueFlags::HIRE_DATE:
    arg = "HireDate";
    break;
  case Employees::EmployeeQueueFlags::STATUS:
    arg = "Status";
    break;
  case Employees::EmployeeQueueFlags::PASSWORD:
    arg = "Password";
    break;
  case Employees::EmployeeQueueFlags::PROFILE_IMAGE:
    arg = "ProfileImage";
    break;
  case Employees::EmployeeQueueFlags::PHONE_NUMBER:
    arg = "PhoneNumber";
    break;
  case Employees::EmployeeQueueFlags::ADDRESS:
    arg = "Address";
    break;
  case Employees::EmployeeQueueFlags::BIRTHDATE:
    arg = "BirthDate";
    break;
  case Employees::EmployeeQueueFlags::DEPARTMENT:
    arg = "Department";
    break;
  case Employees::EmployeeQueueFlags::LAST_LOGIN:
    arg = "LastLogin";
    break;
  case Employees::EmployeeQueueFlags::LAST_PASSWORD_RESET:
    arg = "LastPasswordReset";
    break;
  default:
    std::cerr << "Error: Not invalid 'EmployeeQueueFlags' flag!" << std::endl;
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
  result = new std::vector<std::vector<std::string>>;
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
 * @return     std::vector<std::string>
 */
std::vector<std::string> Employees::Select::selectAll(const Employees::EmployeeInfo &info) {
  *result = db->execute("SELECT * FROM Employees WHERE " + info.arg + " = :1", SqlParam({{1, info.data}}));
  return (result->empty()) ? std::vector<std::string>{} : (*result)[0]; // Return the first and the only row
}

/**
 * @brief ### Return all user data where `info_00` and `info_01`
 *
 * @note          ! Use this function for login check
 * @namespace     Employees
 * @class         Select
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        std::vector<std::string>
 */
std::vector<std::string> Employees::Select::selectAll(const Employees::EmployeeInfo &info_00, const Employees::EmployeeInfo &info_01) {
  *result = db->execute("SELECT * FROM Employees WHERE " + info_00.arg + " = :1 AND " + info_01.arg + " = :2", SqlParam({{1, info_00.data}, {2, info_01.data}}));
  return (result->empty()) ? std::vector<std::string>{} : (*result)[0]; // Return the first and the only row
}

/**
 * @brief ### Return all user data where different to `info`
 *
 * @namespace  Employees
 * @class      Select
 * @param info {const Employees::EmployeeInfo &}
 * @return     std::vector<std::vector<std::string>>
 */
std::vector<std::vector<std::string>> Employees::Select::selectAllExcept(const Employees::EmployeeInfo &info) {
  *result = db->execute("SELECT * FROM Employees WHERE " + info.arg + " <> :1", SqlParam({{1, info.data}}));
  return (result->empty()) ? std::vector<std::vector<std::string>>{} : *result; // Return the first and the only row
}

/**
 * @brief ### Select the last inserted employees into Employees table
 *
 * @namespace  Employees
 * @class      Select
 * @return     std::vector<std::string>
 */
std::vector<std::string> Employees::Select::selectLastInsertedRow() {
  *result = db->execute("SELECT * FROM Employees ORDER BY id DESC LIMIT 1", SqlParam{{}});
  return (result->empty()) ? std::vector<std::string>{} : (*result)[0]; // Return the first and the only row
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
  result = new std::vector<std::vector<std::string>>;
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
  result = new std::vector<std::vector<std::string>>;
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
 * @param info_00
 * @param info_01
 * @return int
 */
int Employees::Update::update(const Employees::EmployeeInfo &info_00, const Employees::EmployeeInfo &info_01) {
  int aff;
  return db->execute("UPDATE Employees SET " + info_00.arg + " = :1 WHERE " + info_01.arg + " = :2", SqlParam({{1, info_00.data}, {2, info_01.data}}), aff), aff;
}

// * =======================================
// ? ==== / Employees::Update functions ====
// * =======================================