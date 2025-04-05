/**
 * @file      EmployeesStatistics.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesStatistics source file
 * @version   0.1
 * @date      2025-04-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/EmployeesStatistics.cpp EmployeesStatistics.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/EmployeesStatistics.hpp"

//? Function/Class prototype dev part

EmployeesStatistics::EmployeesStatistics(const SqlParam &_employee)
    : employee(_employee), employees_length(0) {
  Employees::Select *sl = new Employees::Select;
  std::vector<SqlParam> employees = sl->selectAllExcept(Employees::EmployeeInfo<std::string>(
      std::to_string(employee.integers[Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID].second),
      Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID));
  delete sl;
  sl = nullptr;

  employees_length = employees.size();

  for (const SqlParam &emp : employees) {
    statuses[emp.strings[Employees::EmployeeQueueFlags_strings::STATUS].second]++;
    departments[emp.strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT].second]++;
    salaries[emp.strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT].second] += emp.integers[Employees::EmployeeQueueFlags_integers::SALARY].second;
  }
}

const std::vector<unsigned int> EmployeesStatistics::getStatusStats() {
  return {statuses["ACTIVE"], statuses["INACTIVE"], statuses["SUSPENDED"]};
}

const std::vector<double> EmployeesStatistics::getDepartmentStats() {
  if (!employees_length) // To avoid deviding on zero
    return {};

  for (std::pair<const std::string, double> &department : departments)
    department.second = (department.second * 100.0) / employees_length;

  return {departments["Commercial"], departments["Shops"], departments["Partners"], departments["Events"], departments["Personals"], departments["Employees"]};
}

const std::vector<double> EmployeesStatistics::getSalaryStats() {
  return {salaries["Commercial"], salaries["Shops"], salaries["Partners"], salaries["Events"], salaries["Personals"], salaries["Employees"]};
}