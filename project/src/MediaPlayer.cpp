/**
 * @file      MediaPlayer.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     MediaPlayer
 * @version   0.1
 * @date      2025-04-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/MediaPlayer.cpp MediaPlayer.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/MediaPlayer.hpp"

//? Function prototype dev part

/**
 * @fn           MediaPlayer::playNotif(const QString &, const int &)
 * @brief        Play notification sound
 * @param path   {const QString &}
 * @param volume {const int &}
 * @return       void
 */
void MediaPlayer::playNotif(const QString &path, const int &volume) {
  QMediaPlayer *player(new QMediaPlayer);
  QAudioOutput *audioOutput(new QAudioOutput);

  player->setAudioOutput(audioOutput);
  audioOutput->setVolume(volume);
  player->setSource(QUrl::fromLocalFile(path));
  QObject::connect(player, &QMediaPlayer::mediaStatusChanged,
                   [player, audioOutput](QMediaPlayer::MediaStatus status) -> void {
                     if (status == QMediaPlayer::EndOfMedia || status == QMediaPlayer::InvalidMedia)
                       player->deleteLater(), audioOutput->deleteLater();
                   });
  player->play();
}