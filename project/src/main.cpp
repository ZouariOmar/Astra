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
#include "../inc/login.hpp"
#include <qt6/QtGui/QGuiApplication>
#include <qt6/QtQml/QQmlApplicationEngine>
#include <qt6/QtQml/QQmlContext>

// ? Main int function prototype dev part

/**
 * @brief # The Main Program Function
 * @param argc int
 * @param argv char **
 * @return int
 */
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  // Create Backend instance
  Backend backend;
  QQmlContext *context = engine.rootContext();
  context->setContextProperty("backend", &backend); // Correct way to expose backend

  engine.load(QUrl::fromLocalFile(QStringLiteral("project/qml/main.qml"))); // Adjust the file path
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
