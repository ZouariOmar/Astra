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
#include "../inc/MainWindow.hpp"

// * Include std libs (Qt)
#include "../inc/smtp-mail.hpp"
#include <QtWidgets/QApplication>

// ? Main int function prototype dev part

/**
 * @brief # The Main Program Function
 * @param argc int
 * @param argv char **
 * @return int
 */
int main(int argc, char **argv) {
  QApplication app(argc, argv);

  // ! Email Test
  Email_ls *email_ls = new Email_ls("Omar.Zouari@esprit.tn", "Hello World!", "Just a simple mail");
  Email email(*email_ls);
  email.sendEmail();
  delete email_ls;

  MainWindow mainWin;
  return app.exec();
}