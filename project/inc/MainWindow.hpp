/**
 * @file      MainWindow.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     MainWindow header file
 * @version   0.1
 * @date      2025-02-20
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/MainWindow.hpp MainWindow.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __INC_HPP__
#define __INC_HPP__
#define __SCREEN_WIDTH__ 1920
#define __SCREEN_HIGHT__ 1080

//? Include prototype declaration part
//* Include std libs (Qt)
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>

//* Include custom header(s) (.hpp)
#include "../inc/EmployeesUI.hpp"
#include "../inc/LoginUI.hpp"

//? Class prototype declaration part
class MainWindow : public QMainWindow {
public:
  MainWindow();
  ~MainWindow();

private:
  QStackedWidget *stackedWidget;
  LoginUI *loginUI;
  EmployeesUI *employee_ui;
}; // MainWindow class

#endif // __INC_HPP__
