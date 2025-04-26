/**
 * @file    SerialPortManager.hpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   SerialPortManager header file
 * @version 0.1
 * @date    2025-04-25
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/SerialPortManager.hpp SerialPortManager.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __SERIAL_PORT_MANAGER_HPP__
#define __SERIAL_PORT_MANAGER_HPP__

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtCore/QObject>
#include <QtSerialPort/QSerialPort>

//? Class prototype declaration part

/**
 * @class SerialPortManager
 * @brief SerialPortManager class
 */
class SerialPortManager : public QObject {
  Q_OBJECT
public:
  SerialPortManager(QObject *);
  ~SerialPortManager();
  void details() const;
  void listen();

private:
  QObject *ui;
  QSerialPort *ino;
  const quint16 inoVendorId, inoProductId;
  QString serialBuffer, parsed_data;
  QByteArray serialData;
  QString inoPortName;
  void connect();

  const bool is_inoAvailable();
  void setupSerialPort();
  inline void openSerialPort();

private slots:
  void on_readSerial();
}; // SerialPortManager class

#endif // __SERIAL_PORT_MANAGER_HPP__
