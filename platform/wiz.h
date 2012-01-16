#ifndef _WIZ_H
#define _WIZ_H

/* This file was copied with little or no modification from the WizPort of OpenJazz */

//Video
#define SCREENW 320
#define SCREENH 240

//Audio
#define SOUND_RATE  22050
#define SOUND_FORMAT  AUDIO_S16
#define SOUND_BUFFERS 256
#define SOUND_MIX_CHANNELS 16

#define VOLUME_MIN 0
#define VOLUME_MAX 100
#define VOLUME_CHANGE_RATE 4
#define VOLUME_NOCHG 0
#define VOLUME_DOWN 1
#define VOLUME_UP 2

#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)

#include "../text.h"
void WIZ_ShowVolume(SDL_Surface* screen);
void WIZ_SetVolume( int volumePercent );
int WIZ_GetVolume();
void WIZ_AdjustVolume( int direction );
int WIZ_SetClock(int mhz);

#define PLATFORM_NEEDS_EXIT
void platformExit();

#endif
