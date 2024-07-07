#include <iostream>
#include <SDL2/SDL.h>
#include "vec2flib.cpp"

class Object {
  public:
    vec2f pos;
    vec2f vel;
    SDL_Surface *sprite;

    Object (vec2f position, vec2f velocity, SDL_Surface *image) {
      pos = position;
      vel = velocity;
      sprite = image;
    }
};
