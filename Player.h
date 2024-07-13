#include "Object.h"
#include "vec2flib.cpp"
#include <SDL2/SDL.h>

#ifndef PLAYER_H
#define PLAYER_H

typedef unsigned int uint;

class Player: public Object {
  public:
    Player (vec2f position, vec2f velocity, float w, float h, SDL_Surface *image):
      Object (position, velocity, w, h, image) {

    }
    void move (uint screen_width) {
      vec2f new_pos = add(pos, vel);
      if (new_pos.x + width/2.0 < 0) {
        new_pos.x = screen_width - width/2.0 - 1.0;
      } else if (new_pos.x - width/2.0 > screen_width) {
        new_pos.x = 0 - width/2.0 + 1.0;
      }
      pos = new_pos;
    }
};

#endif
