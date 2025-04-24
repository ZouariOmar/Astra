/**
 * @file    RfidRecognizer.cpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   RfidRecognizer source file
 * @version 0.1
 * @date    2025-04-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar ZouariOmar @endlink
 */

#include "../include/RfidRecognizer.hpp"

/**
 * @fn    RfidRecognizer::RfidRecognizer()
 * @brief Construct new RfidRecognizer::RfidRecognizer object
 */
RfidRecognizer::RfidRecognizer()
    : rc(SSPIN, RSTPIN) {
  // Index Me :°
  byte uid[4] = {0x7E, 0x00, 0x18, 0x2};
  authorized_cards[0] = UID(uid, "omarzouari1");

  // Index `Rayen`
  byte uid1[4] = {0x25, 0x52, 0xC1, 0x01};
  authorized_cards[1] = UID(uid1, "rayen");
}

/**
 * @fn     RfidRecognizer::setup()
 * @brief  Setup RfidRecognizer object
 * @return void
 */
void RfidRecognizer::setup() {
  SPI.begin();                  // Init Serial Peripheral Interface
  rc.PCD_Init();                // Init the receiver
  rc.PCD_DumpVersionToSerial(); // Show details of card reader module
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
 * @fn     RfidRecognizer::listen()
 * @brief  Return `false` if no card present, otherwise retrun `true`
 * @return {const bool}
 */
const bool RfidRecognizer::listen() {
  if (!rc.PICC_IsNewCardPresent() || !rc.PICC_ReadCardSerial())
    return false;
  return get_UID(), rc.PICC_HaltA(), true;
}

const bool RfidRecognizer::is_exist() {
  for (size_t i{}; i < MAX_CARDS; i++)
    if (authorized_cards[i] == detectedCard) {
      detectedCard << authorized_cards[i].name;
      detectedCard.print();
      return true; // UID found in `authorized_cards`
    }
  detectedCard << "";
  detectedCard.print();
  return false; // UID not found
}

void RfidRecognizer::recognize() {
  if (listen())
    (is_exist()) ? notify("CARD AUTHORISED", ACCESS_SUCCESS_LED_PIN) : notify("CARD NOT Authorised", ACCESS_DENIED_LED_PIN);
}

void RfidRecognizer::notify(const String &msg, const uint8_t &led_pin) const {
  Serial.println(msg);
  digitalWrite(led_pin, HIGH);
  delay(2000);
  digitalWrite(led_pin, LOW);
  delay(500);
};
