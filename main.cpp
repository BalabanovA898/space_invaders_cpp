#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <vector>

#include "vec2flib.cpp"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#define FPS 25
#define WIDTH 128.0
#define HEIGHT 256.0
#define SPEED 1
#define PLAYER_FLY_HEIGHT 230.0
#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 5
#define MAX_ENEMIES_PER_LINE 10
#define MAX_LINE_COUNT 22
#define LINE_HEIGHT 10

typedef unsigned short us;
typedef unsigned int uint;

void quit (SDL_Window **win, SDL_Surface **sur);
void ccr (int res, const char *e);
void clear (SDL_Surface **dst);

int init (SDL_Surface **sur, SDL_Window **win, us w, us h);

void spawn_enemy (std::vector<Enemy> &vec);

int main (void) {
    bool isRunning = true;
    us frame = 0;
    us game_difficulty = 0;
    us score = 0;

    SDL_Surface *screen_surface = nullptr;
    SDL_Window *window = nullptr;

    ccr(init(&screen_surface, &window, WIDTH, HEIGHT), "Error while initializing.");

    //Main part below
    SDL_Event e;
    Player player = Player((vec2f) {WIDTH/2.0 - PLAYER_WIDTH/2.0, PLAYER_FLY_HEIGHT},
                           (vec2f) {0.0, 0.0}, PLAYER_WIDTH, PLAYER_HEIGHT,
                           SDL_LoadBMP("./assets/cat.bmp"));

    std::vector<Enemy> enemies {Enemy((vec2f) {WIDTH/2.0 - PLAYER_WIDTH/2.0, LINE_HEIGHT},
                        (vec2f) {1.0, 0.0}, PLAYER_WIDTH, PLAYER_HEIGHT,
                        SDL_LoadBMP("./assets/cat.bmp"))};

    std::vector<Bullet> bullets {};

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        isRunning = false;
                    case SDLK_LEFT:
                        player.vel.x = -SPEED;
                        break;
                    case SDLK_RIGHT:
                        player.vel.x = SPEED;
                        break;
                }
            }
        }

        clear(&screen_surface);

        if (frame % (100 - game_difficulty) == 0) {
            spawn_enemy(enemies);
        }

        if (frame % 10 == 0) {
            player.shoot(bullets);
        }

        {
            player.move(WIDTH);

            SDL_Rect dest;
            SDL_Rect src;

            dest.x = player.pos.x;
            dest.y = player.pos.y;

            src.x = 0;
            src.y = 0;
            src.w = player.width;
            src.h = player.height;

            SDL_BlitSurface(player.sprite, &src, screen_surface, &dest);
        }

        {
            for (uint index = 0; index < enemies.size(); ++index) {
                for (uint i = 0; i < bullets.size(); ++i) {
                    if (enemies[index].check_collision(bullets[i].pos)) {
                        enemies.erase(enemies.begin() + index);
                        bullets.erase(bullets.begin() + i);
                        score += 1;
                    }
                }

                if (frame % 50 == 0) {
                    enemies[index].next_line(LINE_HEIGHT);
                }

                if (enemies[index].pos.y >= HEIGHT) {
                    isRunning = false;
                    std::cout << "Game over!!! Score: " << score << std::endl;
                }

                enemies[index].move(WIDTH, PLAYER_WIDTH);

                SDL_Rect dest;
                SDL_Rect src;

                dest.x = enemies[index].pos.x;
                dest.y = enemies[index].pos.y;

                src.x = 0;
                src.y = 0;
                src.w = enemies[index].width;
                src.h = enemies[index].height;

                SDL_BlitSurface(enemies[index].sprite, &src, screen_surface, &dest);
            }
        }

        {
            for (uint index = 0; index < bullets.size(); ++index) {
                if (frame % 6 == 0) {
                    bullets[index].move();
                }

                if (enemies[index].pos.y <= 0) {
                    bullets.erase(bullets.begin());
                }

                bullets[index].move();

                SDL_Rect dest;
                SDL_Rect src;

                dest.x = bullets[index].pos.x;
                dest.y = bullets[index].pos.y;

                src.x = 0;
                src.y = 0;
                src.w = bullets[index].width;
                src.h = bullets[index].height;

                SDL_BlitSurface(bullets[index].sprite, &src, screen_surface, &dest);
            }
        }
       
        frame += 1;

        if (frame%100 == 0) {
            if (game_difficulty <= 98)
                game_difficulty += 2;
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000/FPS);
    };
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

void clear (SDL_Surface **dst) {
    SDL_FillRect(*dst, NULL, 0x000000);
}

void quit (SDL_Window **win, SDL_Surface **sur) {
    SDL_FreeSurface(*sur);
    *sur = nullptr;
    
    SDL_DestroyWindow(*win);

    SDL_Quit();    
}

void spawn_enemy (std::vector<Enemy> &vec) {
    std::srand((unsigned)time(0));

    vec2f velocity = vec2f {(float)((int)std::rand()%2), 0.0};
    if (velocity.x == 0) {
        velocity.x = -1;
    }

    Enemy new_enemy = Enemy((vec2f) {WIDTH/2.0 - PLAYER_WIDTH/2.0, 0},
                        velocity, PLAYER_WIDTH, PLAYER_HEIGHT,
                        SDL_LoadBMP("./assets/cat.bmp"));
    vec.push_back(new_enemy);
}
