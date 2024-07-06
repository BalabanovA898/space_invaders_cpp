#include <iostream>
#include <SDL2/SDL.h>

typedef unsigned short us;

struct Sprites {
    SDL_Surface *sprites[512];
    int last;
};


void ccr (int res, const char *e);
int init (SDL_Surface **sur, SDL_Window **win, us w, us h); 
int load_image (Sprites &sprites, const char *path);
void quit (SDL_Window **win, SDL_Surface **sur);

int main (void) {
    const us HEIGHT = 255;
    const us WIDTH = 255;

    SDL_Surface *screen_surface = nullptr;
    SDL_Window *window = nullptr;

    Sprites objects;
    objects.last = 0;

    ccr(init(&screen_surface, &window, WIDTH, HEIGHT), "Error while initializing.");
    ccr(load_image(objects, "./assets/cat.bmp"), "Error with loading a file!");

    SDL_BlitSurface(objects.sprites[0], nullptr, screen_surface, nullptr);

    SDL_UpdateWindowSurface(window);    
    SDL_Delay(2000);
    
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

int load_image (Sprites &sprites, const char *path) {
    SDL_Surface *img = SDL_LoadBMP(path);
    if (img == nullptr) {
        return -1;
    }
    sprites.sprites[sprites.last++] = img;
    return 0;
}

void quit (SDL_Window **win, SDL_Surface **sur) {
    SDL_FreeSurface(*sur);
    *sur = nullptr;
    
    SDL_DestroyWindow(*win);

    SDL_Quit();    
}
