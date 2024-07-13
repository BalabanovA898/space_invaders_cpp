#include <SDL2/SDL.h>
#include "vec2flib.cpp"

#ifndef OBJECT_H
#define OBJECT_H

class Object {
  public:
    vec2f pos;
    float width;
    float height;
    vec2f vel;
    SDL_Surface *sprite;

    Object (vec2f position, vec2f velocity, float w, float h, SDL_Surface *image) {
      pos = position;
      vel = velocity;
      width = w;
      height = h;
      sprite = image;
    }
};

#endif
