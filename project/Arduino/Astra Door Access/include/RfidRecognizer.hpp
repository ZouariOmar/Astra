/**
 * @file    RfidRecognizer.hpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   RfidRecognizer header file
 * @version 0.1
 * @date    2025-04-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar ZouariOmar @endlink
 */

//? Pre-proccessor prototype declaration part
#ifndef __RFID_RECOGNIZER__
#define __RFID_RECOGNIZER__
#define MAX_CARDS 2
#define ACCESS_SUCCESS_LED_PIN 6
#define ACCESS_DENIED_LED_PIN 7
#define RSTPIN 9
#define SSPIN 10
#define ACCESS_SUCCESS_LED_PIN 6
#define ACCESS_DENIED_LED_PIN 7

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <MFRC522.h>

//* Include std C++ header(s)

struct UID {
  byte data[4];
  String name;

  // Default constructor
  UID() {
    for (size_t i{}; i < 4; ++i)
      data[i] = 0; // Initialize all byte values to zero
    name = "";
  }

  // Constructor with parameters
  UID(byte d[4], const String &n) {
    for (size_t i{}; i < 4; ++i)
      data[i] = d[i];
    name = n;
  }

  // Print the UID in hexadecimal format
  void print() const {
    for (size_t i{}; i < 4; ++i)
      Serial.print(data[i], HEX), Serial.print(" "); // add space between bytes
    Serial.println(" - " + name);                    // Print the associated name
  }

  void printName() const {
    Serial.println(name); // Print the associated name
  }

  void printUID() const {
    for (size_t i{}; i < 4; ++i)
      Serial.print(data[i], HEX), Serial.print(" ");
    Serial.println("");
  }

  bool operator==(const UID &other) const {
    for (size_t i{}; i < 4; ++i)
      if (data[i] != other.data[i])
        return false;
    return true;
  }

  UID &operator=(const UID &other) {
    if (this != &other) { // Check for self-assignment
      for (size_t i = 0; i < 4; ++i)
        data[i] = other.data[i]; // Copy bytes to data array
      name = other.name;         // Copy the associated name
    }
    return *this; // Return reference to the current object
  }

  UID &operator<<(const byte other[4]) {
    for (size_t i{}; i < 4; ++i)
      data[i] = other[i]; // Copy each byte from the array to data
    return *this;         // Return reference to the current object
  }

  UID &operator<<(const String other) {
    return name = other, *this; // Return reference to the current object
  }
};

//* Class(es) prototype declaration part

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
  UID detectedCard,                // A single UID object to hold the detected card
      authorized_cards[MAX_CARDS]; // Store the authorized UIDs and their associated names
  inline void get_UID();
  const bool listen();
  const bool is_exist();
  void notify(const String &, const uint8_t &) const;
}; // RfidRecognizer class

#endif // !__RFID_RECOGNIZER__
