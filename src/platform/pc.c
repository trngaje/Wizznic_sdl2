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

#include <math.h>

#include "pc.h"
#include "../settings.h"

#if defined(WITH_OPENGL)
static GLuint texture;
static GLuint dlist;

static SDL_Surface* oglWindow;

#ifdef OGS_SDL2
extern SDL_Window* sdlWindow;
extern SDL_Surface* sdlSurface;
#endif

#ifdef OGS_SDL2
SDL_Surface* riftInitAccel(void)
#else
SDL_Surface* riftInitAccel(int sdlVideoModeFlags)
#endif
{
  int w=setting()->glWidth,h=setting()->glHeight;

  w = setting()->glWidth;
  h = setting()->glHeight;

  SDL_Surface* screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320,240,24, 0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
#ifdef OGS_SDL2
  sdlWindow = SDL_CreateWindow("Wizznic",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              w, h,
                              SDL_WINDOW_OPENGL);
  sdlSurface = SDL_GetWindowSurface(sdlWindow);
  oglWindow = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
#else
  oglWindow = SDL_SetVideoMode(w,h,32, SDL_OPENGL | sdlVideoModeFlags );
#endif

  glViewport(0, 0, (GLint)w, (GLint)h);

  glClearColor(1,0,0,1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, w, h, 0, 0,1);
  glColor4f(1,1,1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glDisable( GL_CULL_FACE );
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);


  glColor4f(1,1,1,1);


  glEnable(GL_TEXTURE_2D);
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );

  if( setting()->glFilter )
  {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  } else {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  }


  dlist = glGenLists (1);
  glNewList(dlist, GL_COMPILE);
  glBegin( GL_QUADS );
    glTexCoord2f(0,0);
    glVertex2i(0,0);
    glTexCoord2f(1,0);
    glVertex2i(320,0);
    glTexCoord2f(1,1);
    glVertex2i(320,240);
    glTexCoord2f(0,1);
    glVertex2i(0,240);
  glEnd();
  glEndList();

  //Set scaling
  setting()->scaleFactor=2.0f;

  return(screen);

}

#ifdef OGS_SDL2
SDL_Surface* normalInitAccel(void)
#else
SDL_Surface* normalInitAccel( int sdlVideoModeFlags )
#endif
{
#ifdef OGS_SDL2
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
#else
  const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
#endif
  int w=setting()->glWidth,h=setting()->glHeight;
#ifdef OGS_SDL2
  if(1)
#else
  if( (sdlVideoModeFlags&SDL_FULLSCREEN) )
#endif
  {
#ifdef OGS_SDL2
    w = DM.w;
    h = DM.h;
#else
    w = vidinfo->current_w;
    h = vidinfo->current_h;
#endif
  } else {
    if(w==-1||h==-1)
    {
      //If width or height is set to -1, autosize is enabled, calculate largest window size that fit on the screen, keeps aspect and scales nicely.
#ifdef OGS_SDL2
      int factor=(int)floor( (float)(DM.h-1)/240.0 );
#else
      int factor=(int)floor( (float)(vidinfo->current_h-1)/240.0 );
#endif
      w=320*factor;
      h=240*factor;
    }
  }

  SDL_Surface* screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320,240,24, 0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
#ifdef OGS_SDL2
  sdlWindow = SDL_CreateWindow("Wizznic",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              w, h,
                              SDL_WINDOW_OPENGL);
  sdlSurface = SDL_GetWindowSurface(sdlWindow);
  oglWindow = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
#else
  oglWindow = SDL_SetVideoMode(w,h,32, SDL_OPENGL | sdlVideoModeFlags );
#endif

  int vW = (GLint)h*(320.0f/240.0f);

  glViewport(w/2-vW/2, 0, vW, (GLint)h);

  glClearColor(0,0,0,1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, SCREENW, SCREENH, 0, 0,1);
  glColor4f(1,1,1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glDisable( GL_CULL_FACE );
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);


  glColor4f(1,1,1,1);


  glEnable(GL_TEXTURE_2D);
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );

  if( setting()->glFilter )
  {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  } else {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  }


  dlist = glGenLists (1);
  glNewList(dlist, GL_COMPILE);
  glBegin( GL_QUADS );
    glTexCoord2f(0,0);
    glVertex2i(0,0);
    glTexCoord2f(1,0);
    glVertex2i(320,0);
    glTexCoord2f(1,1);
    glVertex2i(320,240);
    glTexCoord2f(0,1);
    glVertex2i(0,240);
  glEnd();
  glEndList();

  //Set scaling
  setting()->scaleFactor= (float)oglWindow->h/240.0;


  return(screen);
}

#ifdef OGS_SDL2
SDL_Surface* platformInitAccel(void)
#else
SDL_Surface* platformInitAccel( int sdlVideoModeFlags )
#endif
{
#ifdef OGS_SDL2
  if( setting()->rift )
  {
    return( riftInitAccel() );
  }
  return( normalInitAccel() );
#else
  if( setting()->rift )
  {
    return( riftInitAccel(sdlVideoModeFlags) );
  }
  return( normalInitAccel(sdlVideoModeFlags) );
#endif
}

void drawRift( SDL_Surface* src )
{
  glTexImage2D( GL_TEXTURE_2D, 0, src->format->BytesPerPixel, src->w, src->h, 0, GL_BGR, GL_UNSIGNED_BYTE, src->pixels );
  glPushMatrix();
  glTranslatef(210,280,0);
  glCallList(dlist);
  glTranslatef(540,0,0);
  glCallList(dlist);
  glPopMatrix();

#ifdef OGS_SDL2
  SDL_GL_SwapWindow(sdlWindow);
#else
  SDL_GL_SwapBuffers();
#endif
}

void drawNormal( SDL_Surface* src )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTexImage2D( GL_TEXTURE_2D, 0, src->format->BytesPerPixel, src->w, src->h, 0, GL_BGR, GL_UNSIGNED_BYTE, src->pixels );
  glCallList(dlist);
#ifdef OGS_SDL2
  SDL_GL_SwapWindow(sdlWindow);
#else
  SDL_GL_SwapBuffers();
#endif
}

void platformDrawScaled( SDL_Surface* src )
{
  if( !setting()->rift )
  {
    drawNormal(src);
  } else {
    drawRift(src);
  }
}
#endif
