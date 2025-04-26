/**
 * @file      main.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Main Arduino Uno R3 lancer file
 * @version   0.1
 * @date      2025-04-11
 * @copyright Copyright (c) 2025
 * @note Give permission to the arduino board - `sudo chmod 666 /dev/ttyACM0`
 * @note Upload the code cmd                  - `pio run --target upload`
 * @note Listen to the serial monitor         - `stty -F /dev/ttyACM0 raw 9600 && cat /dev/ttyACM0`
 * @note Generate `compile_commands.json`     - pio run -t compiledb
 * @link https://www.instructables.com/Arduino-MFRC522-RFID-READER Arduino-MFRC522-RFID-READER @endlink
 * @link https://github.com/ZouariOmar/Astra/project/Arduino/Astra+Door+Access/src/main.cpp main.cpp @endlink
 */

//? Include prototype declaration part
#include "../include/RfidRecognizer.hpp"

// Global vars prototype declaration part
RfidRecognizer rfid;

//? Functions prototype dev part

/**
 * @fn     setup()
 * @brief  Setup Arduino Uno R3 part
 * @return void
 */
void setup() {
  Serial.begin(9600);
  rfid.setup();
}

/**
 * @fn     loop()
 * @brief  life time Arduino Uno R3 actions part
 * @return void
 */
void loop() {
  rfid.recognize();
}
