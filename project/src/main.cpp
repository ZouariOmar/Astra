/**
 * @file      main.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     The main source file (app lancer)
 * @version   0.1
 * @date      2025-02-10
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/main.cpp main.cpp @endlink
 */

//? Include prototype declaration part

//* Include custom headers
#include "../inc/MainWindow.hpp"

//* Include std headers (Qt)
#include <QtWidgets/QApplication>

//? Main function prototype dev part

/**
 * @fn         main(int, char **)
 * @brief      The Main Program Function
 * @param argc int
 * @param argv {char **}
 * @return     int
 */
int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow mainWin;
  return app.exec();
}