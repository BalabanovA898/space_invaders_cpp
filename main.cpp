#include <iostream>
#include <SDL2/SDL.h>

typedef unsigned short us;

int init (SDL_Surface **sur, SDL_Window **win, us w, us h); 
int load_image (SDL_Surface **img, const char *path);
void quit (SDL_Window **win, SDL_Surface **sur);

int main (void) {
    const us HEIGHT = 255;
    const us WIDTH = 255;

    SDL_Surface* screen_surface = nullptr;
    SDL_Window* window = nullptr;      
    SDL_Surface* cat = nullptr;

    if (init(&screen_surface, &window, WIDTH, HEIGHT) != 0) {
        std::cerr << "Error while initializing." << std::endl;
        return -1;
    }
    if (load_image(&cat, "./assets/cat.bmp") != 0) {
        std::cerr << "Error while loading a file." << std::endl;
        return -1;
    }
    
    SDL_Surface *sprites[512] = {cat};

    SDL_BlitSurface(cat, nullptr, screen_surface, nullptr);
    
    SDL_UpdateWindowSurface(window);    
    SDL_Delay(2000);
    
    quit(&window, &screen_surface);
    return 0;
}

int init (SDL_Surface **sur, SDL_Window **win, us w, us h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 1) {
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

int load_image (SDL_Surface **img, const char *path) {
    *img = SDL_LoadBMP(path);
    if (*img == nullptr) {
        return -1;
    }    
    return 0; 
}

void quit (SDL_Window **win, SDL_Surface **sur) {
    SDL_FreeSurface(*sur);
    *sur = nullptr;
    
    SDL_DestroyWindow(*win);

    SDL_Quit();    
}
