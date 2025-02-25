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
#include "../inc/login.hpp"
#include "../inc/partenaire.h"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new MainWindow::MainWindow object
 *
 * @param parent {QWidget *}
 */
MainWindow::MainWindow()
    : stackedWidget(new QStackedWidget(this)) {

  // Declare interfaces objects 
  Login *l(new Login(this));
  partenaire *partner(new partenaire(this));

  // Add interfaces to `stackWidget`
  stackedWidget->addWidget(l);
  stackedWidget->addWidget(partner);
  stackedWidget->setCurrentWidget(l); // Set login interface as default enter interface

  // Switch to islam interface on loginSuccessful signal
  connect(l, &Login::loginSuccessful, this,  [this, partner]() {
    stackedWidget->setCurrentWidget(partner);
  });

  setCentralWidget(stackedWidget);
  resize(__SCREEN_WIDTH__, __SCREEN_HIGHT__);
  show();
}

/**
 * @brief ### Destroy the MainWindow::MainWindow object
 */
MainWindow::~MainWindow() {
  delete stackedWidget;
}