/**
 * @file    inc.hpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   inc header file
 * @version 0.1
 * @date    2025-04-23
 * @copyright Copyright (c) 2025
 * @note MFRC522 pkg install cmd: pio pkg install --library "nfc-rfid-reader-sdk/MFRC522_PN512@^1.4.13"
 * @link https://github.com/ZouariOmar/Astra/project/Arduino/Astra+Door+Access/include/inc.hpp inc.hpp @endlink
 */

//? Pre-proccessor prototype declaration part
#define RSTPIN 9
#define SSPIN 10

//? Include prototype declaration part
//* Include std Arduino header(s)
#include <MFRC522.h>

extern int readsuccess;

// Global variables prototype declaration part

/*
 * the following are the UIDs of the card which are authorised
 * to know the UID of your card/tag use the example code 'DumpInfo'
 * from the library mfrc522 it give the UID of the card as well as
 * other information in the card on the serial monitor of the arduino
 */
extern byte defcard[][4]; // for multiple cards
extern int N;             // change this to the number of cards/tags you will use
extern byte readcard[4];  // stores the UID of current tag which is read

int getid();
