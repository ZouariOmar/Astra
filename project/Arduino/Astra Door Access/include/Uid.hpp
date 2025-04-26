/**
 * @file      Uid.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Uid header file
 * @version   0.1
 * @date      2025-04-25
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/include/Uid.hpp Uid.hpp @endlink
 */

//? Pre-proccessor prototype declaration part
#ifndef __UID_HPP__
#define __UID_HPP__

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <Arduino.h>

//? Class prototype declaration part

/**
 * @class  Uid
 * @brief Uid class
 */
class Uid {
private:
  byte data[4];
  String name;

public:
  explicit Uid();
  explicit Uid(const byte *, const String &);
  void print() const;
  void print_name() const;
  void print_data() const;
  void clear();
  const byte *get_data() const;
  const String get_name() const;
  bool operator==(const Uid &) const;
  Uid &operator<<(const byte *);
  Uid &operator<<(const String &);
}; // Uid class

#endif // __UID_HPP__
