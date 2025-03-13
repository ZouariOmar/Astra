/**
 * @file MainWindow.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief ### The Main interfaces lancer (default: login interface)
 * @version 0.1
 * @date 2025-02-21
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/MainWindow.cpp MainWindow.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/MainWindow.hpp"
#include "../inc/employeesUI.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new MainWindow::MainWindow object
 *
 * @class        MainWindow
 * @param parent {QWidget *}
 */
MainWindow::MainWindow()
    : stackedWidget(new QStackedWidget(this)),
      loginUI(new Login(this)) {

  // Add Login interface to `stackWidget` and set it as default interface
  stackedWidget->addWidget(loginUI);
  stackedWidget->setCurrentWidget(loginUI);

  // Switch to the next interface on `loginSuccessful` signal
  connect(loginUI, &Login::loginSuccessful, this, [this]() {
    EmployeesUI *employee(new EmployeesUI(loginUI->get_employee(), this));
    stackedWidget->addWidget(employee);
    stackedWidget->setCurrentWidget(employee);
  }); // TODO:Need specify the next widget by verifying the department of the employee

  setCentralWidget(stackedWidget);
  resize(__SCREEN_WIDTH__, __SCREEN_HIGHT__);
  show();
}

/**
 * @brief ### Destroy the MainWindow::MainWindow object
 *
 * @class MainWindow
 */
MainWindow::~MainWindow() {
  delete loginUI; // Delete `loginUI` before `stackedWidget`
  delete stackedWidget;
}