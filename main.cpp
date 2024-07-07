#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <vector>

#include "vec2flib.cpp"
#include "Object.cpp"

#define FPS 60
#define WIDTH 128
#define HEIGHT 256

typedef unsigned short us;
typedef unsigned int uint;

void quit (SDL_Window **win, SDL_Surface **sur);
void ccr (int res, const char *e);

int init (SDL_Surface **sur, SDL_Window **win, us w, us h); 

int main (void) {
    bool isRunning = true;

    SDL_Surface *screen_surface = nullptr;
    SDL_Window *window = nullptr;

    std::vector<Object> objects {};
   
    ccr(init(&screen_surface, &window, WIDTH, HEIGHT), "Error while initializing.");
    //Main part below
    objects.push_back(Object((vec2f) {0.0, 0.0}, (vec2f) {0.0, 0.0}, SDL_LoadBMP("./assets/cat.bmp")));
    objects.push_back(Object((vec2f) {100.0, 0.0}, (vec2f) {0.0, 0.0}, SDL_LoadBMP("./assets/cat.bmp")));

    SDL_Event e;

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        std::cout << "1111" << std::endl;
                }
            }
        }

        for (uint i = 0; i < objects.size(); i++) {
            SDL_Rect dest;
            dest.x = objects[i].pos.x;
            dest.y = objects[i].pos.y;
            SDL_BlitSurface(objects[i].sprite, NULL, screen_surface, &dest);
        }
        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000/FPS);
    };


    quit(&window, &screen_surface);
    return 0;
}

void ccr (int res, const char *e) {
    if (res != 0) {
        std::cerr << "Error! " << e << std::endl;
        exit(-1);
    }
}

int init (SDL_Surface **sur, SDL_Window **win, us w, us h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error with initializing." << std::endl;
        return -1;
    }
    
    *win = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                           w, h, SDL_WINDOW_SHOWN); 
    
    if (*win == NULL) {
        std::cerr << "Erorr with creating a window." << std::endl;
        return -1;
    }
    *sur = SDL_GetWindowSurface(*win);
    return 0;
}

void quit (SDL_Window **win, SDL_Surface **sur) {
    SDL_FreeSurface(*sur);
    *sur = nullptr;
    
    SDL_DestroyWindow(*win);

    SDL_Quit();    
}
