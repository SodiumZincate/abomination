#include "app.h"

bool init_app(basic_app* game) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        return false;
    }
    game->window = SDL_CreateWindow(
        "GTA 6",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
    );
    if (!game->window) {
        printf("Could not create game->window: %s\n", SDL_GetError());
        return false;
    }
    game->renderer = SDL_CreateRenderer(
        game->window,
        -1,
        SDL_RENDERER_TARGETTEXTURE
    );
    if (!game->renderer) {
        printf("Could not create game->renderer: %s\n", SDL_GetError());
        return false;
    }
    return true;
}