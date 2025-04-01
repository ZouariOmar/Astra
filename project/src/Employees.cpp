/**
 * @file      Employees.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Employees source file
 * @version   0.1
 * @date      2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/Employees.cpp Employees.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/Employees.hpp"

//? Function/Class prototype dev part

/**
 * @fn           Employees::EmployeeStatusString(const EmployeeStatusFlags &)
 * @brief        Return the corresponding `EmployeeStatusFlags` string
 * @param status {const EmployeeStatusFlags &}
 * @return       std::string
 */
std::string Employees::EmployeeStatusString(const EmployeeStatusFlags &status) {
  switch (status) {
  case EmployeeStatusFlags::ALL:
    return "ALL";
  case EmployeeStatusFlags::ACTIVE:
    return "ACTIVE";
  case EmployeeStatusFlags::INACTIVE:
    return "INACTIVE";
  case EmployeeStatusFlags::SUSPENDED:
    return "SUSPENDED";
  default:
    return "NONE";
  }
  return ""; // Dummy
}

// * ====================================
// ? ========= Employees::Setup =========
// * ====================================

/**
 * @fn    Employees::Setup::Setup()
 * @brief Construct a new Employees::Setup::Setup object
 */
Employees::Setup::Setup()
    : db(new Database()) {};

/**
 * @fn    Employees::Setup::~Setup()
 * @brief Destroy the Employees::Setup::Setup object
 */
Employees::Setup::~Setup() {
  delete db;
  db = nullptr;
};

// * ======================================
// ? ========= / Employees::Setup  ========
// ? ========= Employees::Select  =========
// * ======================================

/**
 * @fn     Employees::Select::selectAll()
 * @brief  Return all users without any exceptions
 * @return std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAll() {
  return db->execute("SELECT * FROM Employees", SqlParam());
}

/**
 * @fn         Employees::Select::selectAll(const Employees::EmployeeInfo &)
 * @brief      Return all user data where `info`
 * @param info {const Employees::EmployeeInfo &}
 * @return     std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAll(const Employees::EmployeeInfo<std::string> &info) {
  return db->execute("SELECT * FROM Employees WHERE " + info.arg + " = :1",
                     SqlParam({{1, info.data}}));
}

/**
 * @fn            Employees::Select::selectAll(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &)
 * @brief         Return all user data where `info_00` and `info_01`
 * @note          Use this function for login check
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAll(const Employees::EmployeeInfo<std::string> &info_00, const Employees::EmployeeInfo<std::string> &info_01) {
  return db->execute(
      "SELECT * FROM Employees WHERE " + info_00.arg + " = :1 AND " + info_01.arg + " = :2",
      SqlParam({{1, info_00.data}, {2, info_01.data}}));
}

/**
 * @fn         Employees::Select::selectAllExcept(const Employees::EmployeeInfo &)
 * @brief      Return all user data except where `info`
 * @param info {const Employees::EmployeeInfo &}
 * @return     std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAllExcept(const Employees::EmployeeInfo<std::string> &info) {
  return db->execute(
      "SELECT * FROM Employees WHERE " + info.arg + " <> :1",
      SqlParam({}, {{1, std::stoi(info.data)}}));
}

/**
 * @fn            Employees::Select::selectAllExcept(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &)
 * @brief         Return all user data except where `info`
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectAllExcept(const Employees::EmployeeInfo<std::string> &info_00, const Employees::EmployeeInfo<std::string> &info_01) {
  return db->execute(
      "SELECT * FROM Employees WHERE " + info_00.arg + " = :1 AND " + info_01.arg + " <> :2",
      SqlParam({{1, info_00.data}, {2, info_01.data}}));
}

/**
 * @fn     Employees::Select::selectLastInsertedRow()
 * @brief  Select the last inserted employee from the Employees table
 * @return std::vector<SqlParam>
 */
std::vector<SqlParam> Employees::Select::selectLastInsertedRow() {
  return db->execute("SELECT * FROM Employees ORDER BY id DESC LIMIT 1", SqlParam{});
}

// * =====================================
// ? ========= / Employees::Select =======
// ? =========== Employees::Insert =======
// * =====================================

/**
 * @fn               Employees::Insert::insertReq(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &)
 * @brief            Insert the required employee data
 * @param email      {const Employees::EmployeeInfo<std::string> &}
 * @param firstname  {const Employees::EmployeeInfo<std::string> &}
 * @param lastname   {const Employees::EmployeeInfo<std::string> &}
 * @param password   {const Employees::EmployeeInfo<std::string> &}
 * @param department {const Employees::EmployeeInfo<std::string> &}
 * @return           int
 */
int Employees::Insert::insert(const Employees::EmployeeInfo<std::string> &email,
                              const Employees::EmployeeInfo<std::string> &firstName,
                              const Employees::EmployeeInfo<std::string> &lastName,
                              const Employees::EmployeeInfo<std::string> &password,
                              const Employees::EmployeeInfo<std::string> &department) {
  int aff;
  return db->execute("INSERT INTO Employees (" + email.arg + ", " + firstName.arg + ", " + lastName.arg + ", " + password.arg + ", " + department.arg + ") VALUES (:1, :2, :3, :4, :5)",
                     SqlParam(
                         {{1, email.data}, {2, firstName.data}, {3, lastName.data}, {4, password.data}, {5, department.data}}),
                     aff),
         aff;
}

/**
 * @fn               Employees::Insert::insert(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &)
 * @brief            Insert all employee data
 * @param email      {const Employees::EmployeeInfo<std::string> &}
 * @param firstname  {const Employees::EmployeeInfo<std::string> &}
 * @param lastname   {const Employees::EmployeeInfo<std::string> &}
 * @param password   {const Employees::EmployeeInfo<std::string> &}
 * @param department {const Employees::EmployeeInfo<std::string> &}
 * @param jobTitle   {const Employees::EmployeeInfo<std::string> &}
 * @param address    {const Employees::EmployeeInfo<std::string> &}
 * @param imagePath  {const Employees::EmployeeInfo<std::string> &}
 * @param salary     {const Employees::EmployeeInfo<int> &}
 * @param tel        {const Employees::EmployeeInfo<int> &}
 * @param birthdate  {const Employees::EmployeeInfo<oracle::occi::Date> &}
 * @return           int
 */
int Employees::Insert::insert(const Employees::EmployeeInfo<std::string> &email,
                              const Employees::EmployeeInfo<std::string> &firstName,
                              const Employees::EmployeeInfo<std::string> &lastName,
                              const Employees::EmployeeInfo<std::string> &password,
                              const Employees::EmployeeInfo<std::string> &department,
                              const Employees::EmployeeInfo<std::string> &jobTitle,
                              const Employees::EmployeeInfo<std::string> &address,
                              const Employees::EmployeeInfo<std::string> &imagePath,
                              const Employees::EmployeeInfo<int> &salary,
                              const Employees::EmployeeInfo<int> &tel,
                              const Employees::EmployeeInfo<oracle::occi::Date> &birthdate) {
  int aff;
  return db->execute("INSERT INTO Employees (" + email.arg + ", " + firstName.arg + ", " + lastName.arg + ", " + password.arg + ", " + department.arg + ", " + jobTitle.arg + ", " + address.arg + ", " + imagePath.arg + ", " + salary.arg + ", " + tel.arg + ", " + birthdate.arg + ") VALUES (:1, :2, :3, :4, :5, :6, :7, :8, :9, :10, :11)",
                     SqlParam(
                         {
                             {1, email.data},
                             {2, firstName.data},
                             {3, lastName.data},
                             {4, password.data},
                             {5, department.data},
                             {6, jobTitle.data},
                             {7, address.data},
                             {8, imagePath.data},
                         },
                         {{9, salary.data}, {10, tel.data}},
                         {{11, birthdate.data}}),
                     aff),
         aff;
}

// * ==============================================
// ? ============ / Employees::Insert =============
// ? ============= Employees::Update ==============
// * ==============================================

/**
 * @fn            Employees::Update::update(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &);)
 * @brief         Update user data where `info_00` and `info_01`
 * @namespace     Employees
 * @class         Update
 * @param info_00 {const Employees::EmployeeInfo &}
 * @param info_01 {const Employees::EmployeeInfo &}
 * @return        int
 */
int Employees::Update::update(const Employees::EmployeeInfo<std::string> &info_00, const Employees::EmployeeInfo<std::string> &info_01) {
  int aff;
  return db->execute("UPDATE Employees SET " + info_00.arg + " = :1 WHERE " + info_01.arg + " = :2", SqlParam({{1, info_00.data}, {2, info_01.data}}), aff), aff;
}

/**
 * @fn               Employees::Update::update(const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &, const Employees::EmployeeInfo &)
 * @brief            Update the required employee data where `username`
 * @param email      {const Employees::EmployeeInfo &}
 * @param firstname  {const Employees::EmployeeInfo &}
 * @param lastname   {const Employees::EmployeeInfo &}
 * @param password   {const Employees::EmployeeInfo &}
 * @param department {const Employees::EmployeeInfo &}
 * @param username   {const Employees::EmployeeInfo &}
 * @return           int
 */
int Employees::Update::update(const Employees::EmployeeInfo<std::string> &email, const Employees::EmployeeInfo<std::string> &firstname, const Employees::EmployeeInfo<std::string> &lastname, const Employees::EmployeeInfo<std::string> &password, const Employees::EmployeeInfo<std::string> &department, const Employees::EmployeeInfo<std::string> &username) {
  int aff;
  return db->execute("UPDATE Employees SET " + email.arg + " = :1, " + firstname.arg + " = :2, " + lastname.arg + " = :3, " + password.arg + " = :4, " + department.arg + " = :5 WHERE " + username.arg + " = :6",
                     SqlParam(
                         {{1, email.data}, {2, firstname.data}, {3, lastname.data}, {4, password.data}, {5, department.data}, {6, username.data}}),
                     aff),
         aff;
}

/**
 * @fn               Employees::Update::update(const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<std::string> &, const Employees::EmployeeInfo<int> &, const Employees::EmployeeInfo<int> &, const Employees::EmployeeInfo<oracle::occi::Date> &)
 * @brief            Update all employee data where `username`
 * @param username   {const Employees::EmployeeInfo<std::string> &}
 * @param email      {const Employees::EmployeeInfo<std::string> &}
 * @param firstname  {const Employees::EmployeeInfo<std::string> &}
 * @param lastname   {const Employees::EmployeeInfo<std::string> &}
 * @param password   {const Employees::EmployeeInfo<std::string> &}
 * @param department {const Employees::EmployeeInfo<std::string> &}
 * @param jobTitle   {const Employees::EmployeeInfo<std::string> &}
 * @param address    {const Employees::EmployeeInfo<std::string> &}
 * @param imagePath  {const Employees::EmployeeInfo<std::string> &}
 * @param status     {const Employees::EmployeeInfo<std::string> &}
 * @param salary     {const Employees::EmployeeInfo<int> &}
 * @param tel        {const Employees::EmployeeInfo<int> &}
 * @param birthdate  {const Employees::EmployeeInfo<oracle::occi::Date> &}
 * @return           int
 */
int Employees::Update::update(const Employees::EmployeeInfo<std::string> &username,
                              const Employees::EmployeeInfo<std::string> &email,
                              const Employees::EmployeeInfo<std::string> &firstName,
                              const Employees::EmployeeInfo<std::string> &lastName,
                              const Employees::EmployeeInfo<std::string> &password,
                              const Employees::EmployeeInfo<std::string> &department,
                              const Employees::EmployeeInfo<std::string> &jobTitle,
                              const Employees::EmployeeInfo<std::string> &address,
                              const Employees::EmployeeInfo<std::string> &imagePath,
                              const Employees::EmployeeInfo<std::string> &status,
                              const Employees::EmployeeInfo<int> &salary,
                              const Employees::EmployeeInfo<int> &tel,
                              const Employees::EmployeeInfo<oracle::occi::Date> &birthdate) {
  int aff;
  return db->execute("UPDATE Employees SET " + email.arg + " = :1, " + firstName.arg + " = :2, " + lastName.arg + " = :3, " + password.arg + " = :4, " + department.arg + " = :5, " + jobTitle.arg + " = :6, " + address.arg + " = :7, " + imagePath.arg + " = :8, " + status.arg + " = :9, " + salary.arg + " = :10, " + tel.arg + " = :11, " + birthdate.arg + " = :12 WHERE " + username.arg + " = :13 ",
                     SqlParam(
                         {{1, email.data},
                          {2, firstName.data},
                          {3, lastName.data},
                          {4, password.data},
                          {5, department.data},
                          {6, jobTitle.data},
                          {7, address.data},
                          {8, imagePath.data},
                          {9, status.data},
                          {13, username.data}},
                         {{10, salary.data}, {11, tel.data}},
                         {{12, birthdate.data}}),
                     aff),
         aff;
}

// * ===========================================
// ? =========== / Employees::Update ===========
// ? ============ Employees::Delete  ===========
// * ===========================================

/**
 * @fn         Employees::Delete::del(const Employees::EmployeeInfo &)
 * @brief      Delete user where `info`
 * @param info {const Employees::EmployeeInfo &}
 * @return     int
 */
int Employees::Delete::del(const Employees::EmployeeInfo<std::string> &info) {
  int aff;
  return db->execute("DELETE FROM Employees WHERE " + info.arg + " = :1",
                     SqlParam({{1, info.data}}),
                     aff),
         aff;
}

// * ============================================
// ? ============ / Employees::Delete ===========
// ? ======== Employees::EmployeeChecker ========
// * ============================================

/**
 * @fn               Employees::EmployeeChecker::is_empty
 * @brief            Return `true` if the passed Employee data empty, otherwise return `false`
 * @param username   {const std::string &}
 * @param email      {const std::string &}
 * @param firstname  {const std::string &}
 * @param lastname   {const std::string &}
 * @param password   {const std::string &}
 * @param department {const std::string &}
 * @return           bool
 */
bool Employees::EmployeeChecker::is_empty(const std::string &email, const std::string &firstname, const std::string &lastname, const std::string &password, const std::string &department) {
  return firstname.empty() || lastname.empty() || email.empty() || password.empty() || department.empty();
}

/**
 * @fn          Employees::EmployeeChecker::is_validEmail(const std::string &)
 * @brief       Return `true` if the given string email matches with the given regular expression, otherwise return `false`
 * @param email {const std::string &}
 * @return      bool
 */
bool Employees::EmployeeChecker::is_validEmail(const std::string &email) {
  const std::regex emailMatchPattern(EMAIL_MATCHER_PATTERN); // Regular expression definition
  return std::regex_match(email, emailMatchPattern);         // Match the string pattern with regular expression
}

/**
 * @fn      Employees::EmployeeChecker::is_alphaDigit(const std::string &)
 * @brief   Return `true` if the passed string `s` is have digit characters, otherwise return `false`
 * @param s {const std::string &}
 * @return  bool
 */
bool Employees::EmployeeChecker::is_alphaDigit(const std::string &s) {
  return *std::find_if(s.begin(), s.end(), [](const char &c) -> bool {
    return std::isdigit(c);
  });
}

/**
 * @fn               Employees::EmployeeChecker::is_valid(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::pair<Employees::EmployeeCheckerFlags, const char *>)
 * @brief            Return `{Employees::EmployeeCheckerFlags::OK, ""}` if the passed Employee data are valid, otherwise return `{Employees::EmployeeCheckerFlags::REFUSED, "ERROR_MESSAGE"}`
 * @param username   {const std::string &}
 * @param email      {const std::string &}
 * @param firstname  {const std::string &}
 * @param lastname   {const std::string &}
 * @param password   {const std::string &}
 * @param department {const std::string &}
 * @return           std::pair<Employees::EmployeeCheckerFlags, const char *>
 */
std::pair<Employees::EmployeeCheckerFlags, const char *> Employees::EmployeeChecker::is_valid(const std::string &email, const std::string &firstname, const std::string &lastname, const std::string &password, const std::string &department, std::string status, const std::pair<Employees::EmployeeCheckerFlags, const char *> &flag) {
  if (is_empty(email, firstname, lastname, password, department))
    return {Employees::EmployeeCheckerFlags::REFUSED, "Error: Missing required employee data!\nPlease fill in the missing fields."};

  if (is_alphaDigit(firstname + lastname))
    return {Employees::EmployeeCheckerFlags::REFUSED, "Error: Lastname/Firstname can only contain alphaiptic characters!"};

  if (!is_validEmail(email))
    return {Employees::EmployeeCheckerFlags::REFUSED, "Error: The email format is not valid!"};

  if (flag.first == Employees::EmployeeCheckerFlags::UNIQUE_EMAIL) { // Verify if the given email exist
    Employees::Select *sl(new Employees::Select);
    std::vector<SqlParam> employee = sl->selectAll(Employees::EmployeeInfo<std::string>(flag.second, Employees::EmployeeQueueFlags_strings::EMAIL)); // flag.second = email
    if (!employee.empty())
      return {Employees::EmployeeCheckerFlags::REFUSED, "Error: This Email Exist, you can't added it again!"};
  }

  if (flag.first == Employees::EmployeeCheckerFlags::UNIQUE_EMAIL_WITH_EXCEPTION) { // Verify if the given email exist except the employee him self
    Employees::Select sl;
    std::vector<SqlParam> employee = sl.selectAllExcept(Employees::EmployeeInfo<std::string>(email, Employees::EmployeeQueueFlags_strings::EMAIL), Employees::EmployeeInfo<std::string>(flag.second, Employees::EmployeeQueueFlags_strings::USERNAME)); // flag.second = username
    if (!employee.empty())
      return {Employees::EmployeeCheckerFlags::REFUSED, "Error: This Email already used, you can't used again!"};
  }

  return {Employees::EmployeeCheckerFlags::OK, ""}; // Valid employee informations
}

// * ============================================
// ? ======= / Employees::EmployeeChecker =======
// * ============================================