#ifndef render_internal_h
#define render_internal_h

#include <SDL2/SDL.h>

#include <type.h>
#include "render.h"

typedef struct render_state_internal {
	u32 vao_quad;
	u32 vbo_quad;
	u32 ebo_quad;
}Render_State_Internal;

SDL_Window* render_init_window(u32 width, u32 height);
void render_init_quad(u32* vao, u32* vbo, u32* ebo);

#endif