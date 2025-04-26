/**
 * @file      Uid.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Uid source file
 * @version   0.1
 * @date      2025-04-25
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/src/Uid.cpp Uid.cpp @endlink
 */

//? Include prototype declaration part
//* Include custom header(s)
#include "../include/Uid.hpp"

// Functions prototype dev part

/**
 * @fn    Uid::Uid()
 * @brief Construct new Uid::Uid object
 */
Uid::Uid()
    : name("") {
  for (size_t i{}; i < 4; ++i)
    data[i] = 0; // Initialize all byte values to zero
}

/**
 * @fn            Uid::Uid(const byte *, const String &)
 * @brief         Construct new Uid::Uid object
 * @param _data() {const byte *}
 * @param _name   {const String &}
 */
Uid::Uid(const byte *_data, const String &_name)
    : name(_name) {
  for (size_t i{}; i < 4; ++i)
    data[i] = _data[i];
}

/**
 * @fn     Uid::print()
 * @brief  Print the UID (`name` + `data`)
 * @return void
 */
void Uid::print() const {
  for (size_t i{}; i < 4; ++i)
    Serial.print(data[i], HEX), Serial.print(" "); // add space between bytes
  Serial.println(" - " + name);                    // Print the associated name
}

/**
 * @fn     Uid::print_name()
 * @brief  Print the `name` UID
 * @return void
 */
void Uid::print_name() const {
  Serial.println(name); // Print the associated name
}

/**
 * @fn     Uid::print_data
 * @brief  Print the `data` in hex format
 * @return void
 */
void Uid::print_data() const {
  for (size_t i{}; i < 4; ++i)
    Serial.print(data[i], HEX), Serial.print(" ");
  Serial.println("");
}

/**
 * @fn    Uid::clear()
 * @brief  Reset `data` to zeros and `name` to empty String
 * @return void
 */
void Uid::clear() {
  for (size_t i{}; i < 4; ++i)
    data[i] = 0;
  name = "";
}

/**
 * @fn    Uid::get_data()
 * @brief  Get `data` (getter function)
 * @return {const byte *}
 */
const byte *Uid::get_data() const {
  return data;
}

/**
 * @fn    Uid::print_name()
 * @brief  Get `name` (getter function)
 * @return {const byte *}
 */
const String Uid::get_name() const {
  return name;
}

/**
 * @fn           Uid::operator==(const Uid &)
 * @brief        Compare only Uid's data
 * @param  other {const Uid &}
 * @return       bool
 */
bool Uid::operator==(const Uid &other) const {
  for (size_t i{}; i < 4; ++i)
    if (data[i] != other.data[i])
      return false;
  return true;
}

/**
 * @fn          Uid::operator<<(const byte *)
 * @brief       Assign `otherData` to `this->data`
 * @param other {const byte *}
 * @return      {Uid &}
 */
Uid &Uid::operator<<(const byte *otherData) {
  for (size_t i{}; i < 4; ++i)
    data[i] = otherData[i];
  return *this; // Return reference to the current object
}

/**
 * @fn              Uid::operator<<(const String &)
 * @brief           Assign `otherName` to `this->name`
 * @param otherName {const String &}
 * @return          {Uid &}
 */
Uid &Uid::operator<<(const String &otherName) {
  return name = otherName, *this; // Return reference to the current object
}
