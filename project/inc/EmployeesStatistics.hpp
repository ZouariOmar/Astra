/**
 * @file      EmployeesStatistics.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesStatistics header file
 * @version   0.1
 * @date      2025-04-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/EmployeesStatistics.hpp EmployeesStatistics.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_STATISTICS__
#define __EMPLOYEES_STATISTICS__

// ? Include(s) prototype declaration part
// * Include std c++ header(s)
#include <unordered_map>

//* Include generated ui_.h file(s)
#include "../inc/Employees.hpp"

// ? Class prototype declaration part

/**
 * @class EmployeesStatistics
 * @brief EmployeesStatistics class
 */
class EmployeesStatistics {
private:
  SqlParam employee;
  size_t employees_length;
  std::unordered_map<std::string, unsigned int> statuses;
  std::unordered_map<std::string, double> departments;
  std::unordered_map<std::string, double> salaries;

public:
  explicit EmployeesStatistics(const SqlParam &);
  const std::vector<unsigned int> getStatusStats();
  const std::vector<double> getDepartmentStats();
  const std::vector<double> getSalaryStats();
}; // EmployeesStatistics class

#endif // __EMPLOYEES_STATISTICS__