/**
 * @file      Melody.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Melody header file
 * @version   0.1
 * @date      2025-04-26
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/blob/main/project/Arduino/Astra%20Door%20Access/include/Melody.hpp Melody.hpp @endlink
 */

//? Pre-proccessor prototype declaration part
#ifndef __MELODY_HPP__
#define __MELODY_HPP__
#define BUZZER_PIN 3

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <Arduino.h>

//* Include custom header(s)
#include "pitches.h"

//* Class prototype declaration part

/**
 * @class Melody
 * @brief Melody class
 */
class Melody {
public:
  static constexpr int succesSound[2][3] = {
      {NOTE_C5, NOTE_E5, NOTE_G5}, // `succesSound` melody
      {150, 150, 150}};            // `succesSound` durations

  static constexpr int failSound[2][3] = {
      {NOTE_DS3, NOTE_D3, NOTE_CS3}, // `failSound` melody
      {200, 200, 300}};              // `failSound` durations

  /**
   * @fn    Melody;;play(const int [2][N], const int &)
   * @brief Play buzzer sound using one of `_Sound[2][N]`
   *
   * @tparam N         {unsigned int}
   * @param &sound     {const int [2][N]}
   * @param buzzer_pin {const int &}
   *
   * @return void
   */
  template <unsigned int N>
  static void play(const int (&sound)[2][N], unsigned int volume = 100, const unsigned int &buzzer_pin = BUZZER_PIN) {
    volume = constrain(volume, 0, 100); // Ensure the volume is between 0 and 100

    for (unsigned int i{}; i < N; ++i) {
      unsigned int note(sound[0][i]), duration(sound[1][i]);

      // Convert frequency (note) to period (in microseconds)
      unsigned long period = 1000000L / note, // Period of the note in microseconds
          pulseWidth = period * volume / 100; // Duty cycle to simulate volume

      // Play the note with PWM
      //! AnalogWrite doesn't take frequency, only duty cycle
      for (unsigned long j{}; j < duration * 1000L; j += period) {
        analogWrite(buzzer_pin, 127);           // Set to half the maximum value for a 50% duty cycle
        delayMicroseconds(pulseWidth);          // High for `pulseWidth` time
        analogWrite(buzzer_pin, 0);             // Turn off buzzer
        delayMicroseconds(period - pulseWidth); // Low for the rest of the period
      }

      noTone(buzzer_pin);    // Make sure no tone is playing
      delay(duration * 1.3); // Extra delay to prevent overlapping sounds
    }
  }
}; // Melody classs

#endif // __MELODY_HPP__
