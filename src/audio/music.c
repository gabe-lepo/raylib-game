#include "music.h"
#include "logging/log.h"

// extern MusicObject mainMenuSong = {
//     Music song,
//     false,
// };

void InitMusic(Music *musicObject)
{
   InitAudioDevice();
   *musicObject = LoadMusicStream(MUSIC_ASSET_PATH);
   musicObject->looping = true;

   LogMessage(LOG_INFO, "Initialized music object with {%d} frames", musicObject->frameCount);
}

void StartMusic(Music musicObject)
{
   PlayMusicStream(musicObject);

   LogMessage(LOG_INFO, "Started music");
}

void UpdateMusic(Music musicObject, bool paused)
{
   UpdateMusicStream(musicObject);

   if (paused)
   {
      PauseMusicStream(musicObject);
      LogMessage(LOG_DEBUG, "Music paused");
   }
   else
   {
      ResumeMusicStream(musicObject);
      LogMessage(LOG_DEBUG, "Music resumed");
   }
}