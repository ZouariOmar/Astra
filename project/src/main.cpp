/**
 * @file main.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # The main source file (app lancer)
 * @version 0.1
 * @date 2025-02-10
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/main.cpp @endlink
 */

// ? Include prototype declaration part
#include "../inc/inc.hpp"
#include "../inc/partenaire.h"

// ? Main int function prototype dev part

/**
 * @brief # The Main Program Function
 * @param argc int
 * @param argv char **
 * @return int
 */
int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QMainWindow mainWin;
  QStackedWidget *stackedWidget(new QStackedWidget);

  Login *l(new Login);
  partenaire *partner(new partenaire); // ! Put islam interface her

  // Add interfaces to `stackWidget`
  stackedWidget->addWidget(l);
  stackedWidget->addWidget(partner);
  stackedWidget->setCurrentWidget(l); // Set login interface as default enter interface

  // Switch to islam interface onLoginSuccessful signal
  QMainWindow::connect(l, &Login::loginSuccessful, [&]() {
    stackedWidget->setCurrentWidget(partner);
  });

  mainWin.setCentralWidget(stackedWidget);
  mainWin.resize(1920, 1080);
  mainWin.show();

  return app.exec();
}