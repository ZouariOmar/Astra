/**
 * @file      RfidRecognizer.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     RfidRecognizer source file
 * @version   0.1
 * @date      2025-04-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/src/RfidRecognizer.cpp RfidRecognizer.cpp @endlink
 */

//? Include prototype declaration part
//* Include custom header(s)
#include "../include/RfidRecognizer.hpp"
#include "../include/Melody.hpp"

// Functions prototype dev part

/**
 * @fn    RfidRecognizer::RfidRecognizer()
 * @brief Construct new RfidRecognizer::RfidRecognizer object
 */
RfidRecognizer::RfidRecognizer()
    : rc(SSPIN, RSTPIN),
      sm() {
  // Index Me :°
  byte uid[4] = {0x7E, 0x00, 0x18, 0x2};
  authorized_cards[0] = Uid(uid, "omardabouza8");

  // Index `Rayen`
  byte uid1[4] = {0x25, 0x52, 0xC1, 0x01};
  authorized_cards[1] = Uid(uid1, "rayendabouza12");
}

/**
 * @fn      RfidRecognizer::setup()
 * @details The main RfidRecognizer setup function!
 * @brief   Setup RfidRecognizer object
 * @return  void
 */
void RfidRecognizer::setup() {
  pinMode(ACCESS_SUCCESS_LED_PIN, OUTPUT); // led for authorised
  pinMode(ACCESS_DENIED_LED_PIN, OUTPUT);  // led for not authorised
  SPI.begin();                             // Init Serial Peripheral Interface
  rc.PCD_Init();                           // Init the receiver
  rc.PCD_DumpVersionToSerial();            // Show details of card reader module
  sm.setup();
}

/**
 * @fn      RfidRecognizer::recognize()
 * @brief   Listen to the `RFID-RC522` detector and verify thte existence of the `detectedCard`
 * @details The main RfidRecognizer lancer function!
 * @return  void
 */
void RfidRecognizer::recognize() {
  if (listenFromExternal()) {
    if (is_exist())
      detectedCard.print(), detectedCard.clear();
    else {
      notify(ACCESS_DENIED_LED_PIN);
      return;
    }
  }
  // notify("CARD NOT AUTHORISED", ACCESS_DENIED_LED_PIN);
  const String appMsg = listenFromInternal();
  if (appMsg.indexOf(AUTHORIZATION_SUCCESS_MSG) != -1)
    notify(ACCESS_SUCCESS_LED_PIN), sm.goToAngle(90);
  else if (appMsg.indexOf(AUTHORIZATION_DENIED_MSG) != -1)
    notify(ACCESS_DENIED_LED_PIN), sm.goToAngle(0);
}

/**
 * @fn    RfidRecognizer::get_UID()
 * @brief Store the detected UID in `detectedCard`
 * @retrn void
 */
inline void RfidRecognizer::get_UID() {
  detectedCard << rc.uid.uidByte; // Copy bytes to detectedCard UID
}

/**
 * @fn    RfidRecognizer::is_exist()
 * @brief  Return `true` if the UID of the `detectedCard` exist in `authorized_cards`, otherwise return `false`
 * @return {const bool}
 */
const bool RfidRecognizer::is_exist() {
  for (size_t i{}; i < MAX_CARDS; i++)
    if (authorized_cards[i] == detectedCard) {
      detectedCard << authorized_cards[i].get_name();
      return true; // UID found in `authorized_cards`
    }
  return detectedCard.clear(), false; // UID not found
}

/**
 * @fn     RfidRecognizer::listen()
 * @brief  Return `false` if no card present/detected, otherwise retrun `true`
 * @return {const bool}
 */
const bool RfidRecognizer::listenFromExternal() {
  if (!rc.PICC_IsNewCardPresent() || !rc.PICC_ReadCardSerial())
    return false;
  return get_UID(), rc.PICC_HaltA(), true;
}

const String RfidRecognizer::listenFromInternal() const {
  String incomingData("");

  // Read data from serial buffer
  while (Serial.available()) {
    incomingData += (char)Serial.read();
    delay(10); // Add delay to allow more data to arrive
  }

  return incomingData; // Return the recived msg
}

/**
 * @fn           RfidRecognizer::notify(const String &, const uint8_t &)
 * @brief         Notify the user/employee physically
 * @param msg     {const String &}
 * @param led_pin {const uint8_t &}
 * @return        void
 */
void RfidRecognizer::notify(const uint8_t &led_pin) const {
  digitalWrite(led_pin, HIGH);
  delay(2000);
  (led_pin == ACCESS_SUCCESS_LED_PIN) ? Melody::play(Melody::succesSound) : Melody::play(Melody::failSound);
  digitalWrite(led_pin, LOW);
  delay(500);
};
