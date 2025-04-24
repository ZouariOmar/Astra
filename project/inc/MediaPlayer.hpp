/**
 * @file      MediaPlayer.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     MediaPlayer header file
 * @version   0.1
 * @date      2025-04-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/MediaPlayer.hpp MediaPlayer.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __MEDIA_PLAYER_HPP__
#define __MEDIA_PLAYER_HPP__

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

/**
 * @class MediaPlayer
 * @brief MediaPlayer class
 */
class MediaPlayer {
public:
  static void playNotif(const QString &, const int &volume = 1);
}; // MediaPlayer class

#endif // __MEDIA_PLAYER_HPP__