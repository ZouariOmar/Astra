/**
 * @file      ServoManager.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     ServoManager source file
 * @version   0.1
 * @date      2025-04-26
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/src/ServoManager.cpp ServoManager.cpp @endlink
 */

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <Arduino.h>

//* Include custom header(s)
#include "../include/ServoManager.hpp"

// Functions prototype dev part

ServoManager::ServoManager()
    : angle(0) {};
ServoManager::ServoManager(int _angle)
    : angle(_angle) {};

void ServoManager::setup() {
  servo.attach(SERVO_PIN);
  servo.write(angle);
}

void ServoManager::rotateToRight(const int &newAngle) {
  if (newAngle > 180)
    return; // Safety check
  while (angle < newAngle) {
    angle++;
    servo.write(angle);
    delay(15);
  }
}

void ServoManager::rotateToLeft(const int &newAngle) {
  if (newAngle < 0)
    return; // Safety check
  while (angle > newAngle) {
    angle--;
    servo.write(angle);
    delay(15);
  }
}

void ServoManager::goToAngle(const int &newAngle) {
  if (newAngle < 0 || newAngle > 180)
    return;
  angle = newAngle;
  servo.write(angle);
}
