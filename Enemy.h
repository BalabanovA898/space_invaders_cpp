#include "Object.h"
#include "vec2flib.cpp"

#include <SDL2/SDL.h>

#ifndef ENEMY_H
#define ENEMY_H

typedef unsigned int uint;

class Enemy: public Object {
  public:
    Enemy (vec2f pos, vec2f vel, float w, float h, SDL_Surface* sprite):
      Object (pos, vel, w, h, sprite) {
    }

    void move (float width, float player_width) {
      vec2f new_pos = add(pos, vel);
      if (new_pos.x > width - player_width || new_pos.x < 0) {
        vel.x *= -1;
      }
      pos = add(pos, vel);
    }

    void next_line (float line_height) {
      pos = add(pos, vec2f {0.0, line_height});
    }
};

#endif
