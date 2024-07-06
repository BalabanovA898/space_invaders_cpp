#include <iostream>
#include <SDL2/SDL.h>


typedef unsigned short us;

int init (SDL_Surface** sur, SDL_Window** win, us w, us h); 

int main (void) {
    const unsigned short HEIGHT = 255;
    const unsigned short WIDTH = 128;

    SDL_Surface* screen_surface = nullptr;
    SDL_Window* window = nullptr;      

    if (init(&screen_surface, &window, WIDTH, HEIGHT) != 0) {
        std::cerr << "Error while initializing." << std::endl;
    }
    
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0, 255, 0));
    SDL_UpdateWindowSurface(window);
    
    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit(); 

    return 0;
}


int init (SDL_Surface** sur, SDL_Window** win, us w, us h) {
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