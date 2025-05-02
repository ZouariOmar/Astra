/**
 * @file      ServoManager.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     ServoManager header file
 * @version   0.1
 * @date      2025-04-26
 * @copyright Copyright (c) 2025
 * @details   VCC(Red wire)      - 5V
 *            SIG(yellow/orange) - SERVO_PIN
 *            GND(Black/Brown)   - GND
 * @link https://www.electronics-lab.com/project/using-sg90-servo-motor-arduino SG90 @endlink
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/include/ServoManager.hpp ServoManager.hpp @endlink
 */

//? Pre-proccessor prototype declaration part
#ifndef __SERVO_MANAGER_HPP__
#define __SERVO_MANAGER_HPP__
#define SERVO_PIN 4

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <Servo.h>

//* Class prototype declaration part

class ServoManager {
private:
  Servo servo;
  int angle;

public:
  ServoManager();
  ServoManager(int);
  void setup();
  void goToAngle(const int &);
}; // ServoManager class

#endif // __SERVO_MANAGER_HPP__
