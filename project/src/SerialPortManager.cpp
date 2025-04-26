/**
 * @file      SerialPortManager.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     SerialPortManager source file
 * @version   0.1
 * @date      2025-04-25
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/SerialPortManager.cpp SerialPortManager.cpp @endlink
 */

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtCore/QtDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QtWidgets/QMessageBox>

//* Include std C++ header(s)
#include <iostream>

//* Include custom header(s)
#include "../inc/Employees.hpp"
#include "../inc/SerialPortManager.hpp"

//? Function prototype dev part

/**
 * @fn           SerialPortManager::SerialPortManager()
 * @brief        Construct a new SerialPortManager::SerialPortManager object
 * @param parent {QMainWindow *}
 */
SerialPortManager::SerialPortManager(QObject *parent)
    : ui(parent),
      ino(new QSerialPort(parent)),
      inoVendorId(9025),
      inoProductId(67) {};

/**
 * @fn    SerialPortManager::~SerialPortManager()
 * @brief Destruct SerialPortManager::SerialPortManager object
 */
SerialPortManager::~SerialPortManager() {
  if (ino->isOpen())
    ino->close(), ino = nullptr;
}

/**
 * @fn      SerialPortManager::details()
 * @brief   Prints the description, vendor id, and product id of all ports
 * @details [TESTING MODE] - Used it to determine the values for the arduino uno.
 * @return  void
 */
void SerialPortManager::details() const {
  std::cout << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
  foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    std::cout << "Description: " << serialPortInfo.description().toStdString() << "\n"
              << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n"
              << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n"
              << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n"
              << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
}

/**
 * @brief   Return `true` if the arduino uno connect Successfully (physically), otherwise retrun `false`
 * @details In true result, we take the arduino connected port name
 * @return  {const bool}
 */
const bool SerialPortManager::is_inoAvailable() {
  foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    if (serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier())
      if ((serialPortInfo.productIdentifier() == inoProductId) && (serialPortInfo.vendorIdentifier() == inoVendorId))
        return inoPortName = serialPortInfo.portName(), true;
  return false;
}

/**
 * @fn     SerialPortManager::setupSerialPort()
 * @brief  Setup the serial monitor reading port
 * @return void
 */
void SerialPortManager::setupSerialPort() {
  ino->setPortName(inoPortName);
  ino->setBaudRate(QSerialPort::Baud9600);
  ino->setDataBits(QSerialPort::Data8);
  ino->setParity(QSerialPort::NoParity);
  ino->setStopBits(QSerialPort::OneStop);
  ino->setFlowControl(QSerialPort::NoFlowControl);
  std::cout << "[INFO] Serial Port Setuped Successfully!\n";
}

/**
 * @fn     SerialPortManager::connect()
 * @brief  Connect `ino` serial port to `EmployeesUI` on `SerialPort::readyRead` signal
 * @return void
 */
void SerialPortManager::connect() {
  if (!ino) {
    std::cerr << "[ERROR] Serial port is not initialized!";
    return;
  }
  QObject::connect(ino, &QSerialPort::readyRead, this, &SerialPortManager::on_readSerial);
  std::cout << "[INFO] Serial Port Connected Successfully!\n";
}

/**
 * @fn    SerialPortManager::listen()
 * @brief The lancer `SerialPortManager` function
 *
 * @details this function listen to serial monitor buffer and take
 * action depanding on the recived data.
 *
 * @retrun void
 */
void SerialPortManager::listen() {
  if (is_inoAvailable())
    setupSerialPort(), openSerialPort(), connect();
  else {
    std::cerr << "[ERROR] Couldn't find the correct port for the arduino!\n";
    QMessageBox::warning(qobject_cast<QWidget *>(ui), "Serial Port Error", "Couldn't open serial port to arduino!");
  }
}

/**
 * @fn     SerialPortManager::openSerialPort()
 * @brief  Open the serial monitor reading port
 * @return void
 */
inline void SerialPortManager::openSerialPort() {
  if (ino->open(QIODevice::ReadWrite)) {
    std::cerr << "[ERROR] Can't open the serial port!\n";
    return;
  }
  ino->clear(QSerialPort::AllDirections);
  std::cout << "[INFO] Serial Port Opened Successfully!\n";
}

/**
 * @fn    SerialPortManager::on_readSerial()
 * @brief Read all available data from the port every `\n\r`
 *
 * @details Append incoming data to `serialData` buffer, and split the buffer
 * at the first `completeMessage`. Then we split the message using the " - " separator
 * into `uid|part[0]` and `username|part[1]` (extracting proccess). After that we verify the `status`
 * of the employee/user and depanding on it we repend the serial monitor.
 *
 * @return void
 */
void SerialPortManager::on_readSerial() {
  serialData += ino->readAll();
  while (serialData.contains("\r\n")) {
    qsizetype index(serialData.indexOf("\r\n"));
    QByteArray completeMessage = serialData.left(index);
    serialData = serialData.mid(index + 2); // Remove the processed part from the buffer
    QString message = QString::fromUtf8(completeMessage);
    QStringList parts = message.split(" - ");

    if (parts.length() == 2) {
      std::string username = parts[1].toStdString();
      QMessageBox::information(
          qobject_cast<QWidget *>(ui),
          "Access Request",
          message + " Want to Access!");

      Employees::Select *sl(new Employees::Select);
      std::vector<SqlParam> employees = sl->selectAll(
          Employees::EmployeeInfo<std::string>(
              username,
              Employees::EmployeeQueueFlags_strings::USERNAME));
      delete sl;
      sl = nullptr;
      if (employees.empty()) { // The given `username` not found in the database
        std::cerr << "[ERROR] The given `username` not found in the database..." << username << '\n';
        return;
      }

      ((employees[0].strings[Employees::EmployeeQueueFlags_strings::STATUS].second != "SUSPENDED"))
          ? message = QString("CARD AUTHORISED")
          : message = QString("CARD NOT AUTHORISED");
      ino->write(message.toUtf8() + "\r\n"); // Answer the RFID request (repend action)
    }
  }
}
