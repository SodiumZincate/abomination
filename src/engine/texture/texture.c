#include "texture.h"

bool load_texture(basic_app* game, char* type) {

     if (strcmp(type, "target") == 0) {
         game->texture = SDL_CreateTexture(
             game->renderer,
             SDL_PIXELFORMAT_RGBA8888,
             SDL_TEXTUREACCESS_TARGET,
             60,
             90
         );
         if (!game->texture) {
             printf("Could not create game->texture: %s\n", SDL_GetError());
             return false;
         }
     }
     else if (strcmp(type, "static") == 0) {
         game->texture = SDL_CreateTexture(
             game->renderer,
             SDL_PIXELFORMAT_RGBA8888,
             SDL_TEXTUREACCESS_STATIC,
             60,
             90
         );
         if (!game->texture) {
             printf("Could not create game->texture: %s\n", SDL_GetError());
             return false;
         }
     }
     else if (strcmp(type, "streaming") == 0) {
         game->texture = SDL_CreateTexture(
             game->renderer,
             SDL_PIXELFORMAT_RGBA8888,
             SDL_TEXTUREACCESS_STREAMING,
             60,
             90
         );
         if (!game->texture) {
             printf("Could not create game->texture: %s\n", SDL_GetError());
             return false;
         }
     }

     u32 w = 0, h = 0, access = 0;
     u32 format;
     SDL_QueryTexture(game->texture, &format, &access, &w, &h);
     printf("Format = %u\n", format);
     printf("Access = %d\n", access);
     printf("Width = %d\n", w);
     printf("Height = %d\n", h);

     return true;
}