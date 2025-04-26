/**
 * @file      RfidRecognizer.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     RfidRecognizer header file
 * @version   0.1
 * @date      2025-04-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/Arduino/Astra+Door+Access/include/RfidRecognizer.cpp RfidRecognizer.hpp @endlink
 */

//? Pre-proccessor prototype declaration part
#ifndef __RFID_RECOGNIZER_HPP__
#define __RFID_RECOGNIZER_HPP__
#define MAX_CARDS 2
#define ACCESS_SUCCESS_LED_PIN 6
#define ACCESS_DENIED_LED_PIN 7
#define RSTPIN 9
#define SSPIN 10
#define ACCESS_SUCCESS_LED_PIN 6
#define ACCESS_DENIED_LED_PIN 7
#define AUTHORIZATION_DENIED_MSG "CARD NOT AUTHORISED"
#define AUTHORIZATION_SUCCESS_MSG "CARD AUTHORISED"

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <MFRC522.h>

//* Include custom header(s)
#include "ServoManager.hpp"
#include "Uid.hpp"

//* Class prototype declaration part

/**
 * @class RfidRecognizer
 * @brief RfidRecognizer class
 */
class RfidRecognizer {
public:
  explicit RfidRecognizer();
  void setup();
  void recognize();

private:
  MFRC522 rc;
  ServoManager sm;
  Uid detectedCard,                // A single UID object to hold the detected card
      authorized_cards[MAX_CARDS]; // Store the authorized UIDs and their associated names
  inline void get_UID();
  const bool is_exist();
  const bool listenFromExternal();
  const String listenFromInternal() const;
  void notify(const uint8_t &) const;
}; // RfidRecognizer class

#endif // __RFID_RECOGNIZER_HPP__
