#ifndef MUSIC_H
#define MUSIC_H

#include "raylib.h"

#define MUSIC_ASSET_PATH "assets/music/kick_hat_140bpm.wav"

typedef struct MusicObject
{
   Music music;
   bool paused;
} MusicObject;

void InitMusic(Music *musicObject);
void StartMusic(Music musicObject);
void UpdateMusic(Music musicObject, bool paused);

#endif