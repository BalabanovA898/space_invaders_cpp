#include "vec2flib.cpp"
#include "Object.h"


#ifndef BULLET_H
#define BULLET_H

class Bullet : public Object {
  public:
    Bullet (vec2f position, vec2f velocity, float w, float h, SDL_Surface *image) :
      Object(position, velocity, w, h, image) {

    }
    void move (void) {
      pos = add(pos, vel);
    }
};

#endif
