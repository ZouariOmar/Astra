/**
 * @file      EmployeesUICharts.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesUICharts header file
 * @version   0.1
 * @date      2025-04-05
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/EmployeesUICharts.hpp EmployeesUICharts.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_UI_CHARTS__
#define __EMPLOYEES_UI_CHARTS__

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QtCharts>
#include <QtWidgets/QMainWindow>

//* Include std C++ header(s)
#include <vector>

/**
 * @namespace Employees
 * @brief     Employees namespace
 */
namespace Employees {
class EmployeesUICharts;
} // Namespace Employees

//? Classes prototype declaration part

/**
 * @class EmployeesUICharts
 * @brief EmployeesUICharts class
 */
class Employees::EmployeesUICharts {
private:
  QMainWindow *ui;
  void clearPrevChart(QHBoxLayout *);

public:
  explicit EmployeesUICharts(QMainWindow *);
  void setPieChart(QHBoxLayout *, const std::vector<std::pair<std::string, double>> &);
  void setBarChart(QHBoxLayout *, const std::vector<std::pair<std::string, double>> &);
  void setBarLineChart(QHBoxLayout *, const std::vector<std::pair<std::string, double>> &);
}; // EmployeesUICharts class

#endif // __EMPLOYEES_UI_CHARTS__