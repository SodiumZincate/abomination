#ifndef APP_H
#define APP_H

#include "../utils/includes.h"

#define screen_width 1200
#define screen_height 960

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Renderer* ship_renderer;
}basic_app;

bool init_app();

#endif