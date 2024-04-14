#ifndef global_h
#define global_h

#include "render/render.h"

typedef struct global {
	Render_State render;
}Global;

extern Global global;

#endif