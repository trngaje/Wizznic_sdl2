#ifndef SWSCALE_H_INCLUDED
#define SWSCALE_H_INCLUDED

/************************************************************************
 * This file is part of Wizznic.                                        *
 * Copyright 2009-2015 Jimmy Christensen <dusted@dusted.dk>             *
 * Wizznic is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * Wizznic is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Wizznic.  If not, see <http://www.gnu.org/licenses/>.     *
 ************************************************************************/

#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#ifdef OGS_SDL2
SDL_Surface* swScaleInit(int doScale );
#else
SDL_Surface* swScaleInit( int sdlVideoModeFlags, int doScale );
#endif
void swScale( SDL_Surface* screen, int doScale );

#endif // SWSCALE_H_INCLUDED
