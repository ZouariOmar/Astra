/**
 * @file      MainWindow.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     The Main interfaces lancer (default: login interface)
 * @version   0.1
 * @date      2025-02-21
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/MainWindow.cpp MainWindow.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/MainWindow.hpp"

//? Function prototype dev part

/**
 * @fn    MainWindow::MainWindow()
 * @brief Construct a new MainWindow::MainWindow object
 */
MainWindow::MainWindow()
    : stackedWidget(new QStackedWidget(this)),
      loginUI(new Login(this)), employee_ui(nullptr) {

  // Add interfaces to `stackWidget`
  stackedWidget->addWidget(loginUI);
  stackedWidget->setCurrentWidget(loginUI); // Set login interface as default interface

  // Switch to the next interface on `loginSuccessful` signal
  connect(loginUI, &Login::loginSuccessful, this, [this]() {
    employee_ui = new EmployeesUI(loginUI->get_employee(), this);
    stackedWidget->addWidget(employee_ui);
    stackedWidget->setCurrentWidget(employee_ui);
  }); // TODO:Need specify the next widget by verifying the department of the employee

  setCentralWidget(stackedWidget);
  resize(__SCREEN_WIDTH__, __SCREEN_HIGHT__);
  show();
}

/**
 * @fn    MainWindow::~MainWindow()
 * @brief Destroy the MainWindow::MainWindow object
 */
MainWindow::~MainWindow() {
  delete loginUI; // Delete `loginUI` before `stackedWidget`
  loginUI = nullptr;
  delete employee_ui;
  employee_ui = nullptr;
  delete stackedWidget;
  stackedWidget = nullptr;
}