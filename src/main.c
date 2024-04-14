#include "engine/utils/includes.h"

#include "engine/app/app.h"

void kill(u32 value);
void draw_platform();
void render_character();
void clear_rendered_character(SDL_Rect dest);
void render_current_character(SDL_Texture *character, SDL_Rect dest);
SDL_Rect get_ship_rect(u32 x, u32 y, u32 w, u32 h);
u32 frame_wait(u32 initial_tick);

basic_app* game;

SDL_Rect clear_char;

u32 main(u32 argc, char* argv[]) {
    game = (basic_app*)malloc(sizeof(basic_app));
    if (!init_app(game)) {
        exit(1);
    }

    if (!load_texture(game,"target")) {
        exit(1);
    }

    draw_platform();
    render_character();

    kill(0);

    return 0;
}

void draw_platform() {
    SDL_SetRenderDrawColor(game->renderer, 123, 123, 123, 255);
    SDL_RenderClear(game->renderer);

    SDL_SetTextureBlendMode(game->texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(game->texture, 200);
    SDL_SetTextureColorMod(game->texture, 165, 42, 42);

    SDL_Rect plat_rect_1, plat_rect_2, plat_rect_3, plat_rect_4;
    plat_rect_1.x = 0;
    plat_rect_1.y = 120;
    plat_rect_1.w = screen_width / 4;
    plat_rect_1.h = screen_height / 16;

    plat_rect_2.x = screen_width-screen_width/4;
    plat_rect_2.y = 120;
    plat_rect_2.w = screen_width / 4;
    plat_rect_2.h = screen_height / 16;

    plat_rect_3.x = 0;
    plat_rect_3.y = 120+screen_height/16;
    plat_rect_3.w = screen_width / 4;
    plat_rect_3.h = screen_height / 16;

    plat_rect_4.x = 120;
    plat_rect_4.y = 600;
    plat_rect_4.w = screen_width - 240;
    plat_rect_4.h = screen_height / 16;

    SDL_SetRenderTarget(game->renderer, game->texture);
    SDL_RenderClear(game->renderer);

    SDL_SetRenderTarget(game->renderer, NULL);
    //SDL_RenderCopy(game->renderer, game->texture, NULL, &rect_1);
    //SDL_RenderCopy(game->renderer, game->texture, NULL, &rect_2);
    //SDL_RenderCopy(game->renderer, game->texture, NULL, &rect_3);
    SDL_RenderCopy(game->renderer, game->texture, NULL, &plat_rect_1);
    SDL_RenderCopy(game->renderer, game->texture, NULL, &plat_rect_2);
    SDL_RenderCopy(game->renderer, game->texture, NULL, &plat_rect_4);
    
    SDL_RenderPresent(game->renderer);
}

void render_loop(SDL_Texture* character,SDL_Rect* dest,u32 x_offset, u32 y_offset) {

    SDL_SetRenderDrawColor(game->renderer, 123, 123, 123, 255);
    SDL_RenderFillRect(game->renderer, dest);

    if(x_offset){
        if (dest->x > 10) {
            dest->x += x_offset;
        }
        else {
            dest->x = 10;
        }
        if (dest->x < screen_width - dest->w - 10) {
            dest->x += x_offset;
        }
        else {
            dest->x = screen_width - dest->w - 10;
        }
    }
    if (y_offset) {
        if (dest->y > 10) {
            dest->y -= y_offset;
        }
        else {
            dest->y = 10;
        }
        if (dest->y < screen_height - dest->h - 10) {
            dest->y -= y_offset;
        }
        else {
            dest->y = screen_height - dest->h - 10;
        }
    }

    SDL_RenderCopy(game->renderer, character, NULL, dest);
    SDL_RenderPresent(game->renderer);
}

u32 frame_wait(u32 initial_tick, u32 no_of_sprites) {

    // if no_of_sprites = 7
    // delay 1/6 * 1000/2
    // delay = 83 i.e half a second to render all sprites
    // for 6 sprites, each sprite takes 166.67ms for them to render in 1 second

    if(no_of_sprites>=3){
        u32 delay = ((f32)1 / (no_of_sprites) * 1000 / 2) - 2;
        //u32 delay = 30;
        printf("Delay = %d\n", delay);
        u64 tick_diff = 0;
        tick_diff = SDL_GetTicks64() - initial_tick;
        if (tick_diff < delay) {
            SDL_Delay((u64)delay - tick_diff);
        }
        return SDL_GetTicks64();
    }
    else if (no_of_sprites < 3 && no_of_sprites > 0) {
        u32 delay = 60;
        printf("Delay = %d\n", delay);
        u32 tick_diff = 0;
        tick_diff = SDL_GetTicks64() - initial_tick;
        if (tick_diff < delay) {
            SDL_Delay(delay - tick_diff);
        }
        return SDL_GetTicks64();
    }
}

void render_char(SDL_Texture** ship_texture, SDL_Rect* rect,u32 no_of_sprites, u32 x_offset, u32 y_offset){

    for (u32 i = 0; i < no_of_sprites; i++) {
        if(x_offset){
            for (u32 j = 0; j < abs(x_offset); j++) {
                u64 initial_tick = SDL_GetTicks64();
                render_loop(ship_texture[i], rect, x_offset, y_offset);
                //initial_tick = frame_wait(initial_tick, no_of_sprites);
            }
        }
        if (y_offset) {
            for (u32 j = 0; j < abs(y_offset); j++) {
                u64 initial_tick = SDL_GetTicks64();
                render_loop(ship_texture[i], rect, x_offset, y_offset);
                //initial_tick = frame_wait(initial_tick, no_of_sprites);
            }
        }
    }
}

SDL_Rect get_rect(u32 x, u32 y, u32 w, u32 h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

void get_texture(SDL_Texture** ship_texture, u32 no_of_surfaces, char* f_name, SDL_Rect* ship_rect) {
    SDL_Surface** ship_surface = (SDL_Surface**)malloc(no_of_surfaces * sizeof(SDL_Surface*));

    for (u32 i = 0; i < no_of_surfaces; i++) {
        sprintf(f_name, "assets/ship_%d.bmp", i);
        printf("%s\n", f_name);
        ship_surface[i] = SDL_LoadBMP_RW(SDL_RWFromFile(f_name, "rb"), 1);
        if (!ship_surface[i]) {
            printf("Couldn't initialize surface: %s\n", SDL_GetError());
            kill(1);
        }
        ship_texture[i] = SDL_CreateTextureFromSurface(game->renderer, ship_surface[i]);
        if (!ship_texture[i]) {
            printf("Couldn't initialize texture: %s\n", SDL_GetError());
            kill(1);
        }
        int width, height;
        width = ship_surface[i]->w;
        height = ship_surface[i]->h;
        *ship_rect = get_rect(120, 600- height, width, height);
        SDL_FreeSurface(ship_surface[i]);
    }
    free(ship_surface);
}

void render_character() {

    char f_name[52];
    strcpy(f_name, "assets/ship_0.bmp");
    
    SDL_Rect* ship_rect = (SDL_Rect*)malloc(1 * sizeof(SDL_Rect));
    SDL_Texture** ship_texture = (SDL_Texture**)malloc(1 * sizeof(SDL_Texture*));

    get_texture(ship_texture,1, f_name, ship_rect);

    bool facingLeft = false;
    bool isRunning = true;
    render_loop(ship_texture[0], ship_rect, 0, 0);
    while (isRunning) {
        const u8* key_state = SDL_GetKeyboardState(NULL);
        u64 initial_tick = SDL_GetTicks64(), current_tick = 0, tick_diff = 0;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }

        if(key_state[SDL_SCANCODE_SPACE])
        {
            u32 in = SDL_GetTicks64();
            printf("Initial Tick = %d\n", in);
            render_char(ship_texture, ship_rect, 1, 0, 0);
            printf("1%d\n", ship_rect[0].x);
            printf("Final Tick = %d\n", (SDL_GetTicks64()-in)/6);
        }
        else if (key_state[SDL_SCANCODE_D])
        {
            u32 in = SDL_GetTicks64();
            render_char(ship_texture, ship_rect, 1, 1, 0);
            printf("2Final = %d\n", ship_rect->x);
            facingLeft = false;
            printf("Final Tick = %d\n", (SDL_GetTicks64() - in) / 6);
        }
        else if (key_state[SDL_SCANCODE_A])
        {
            render_char(ship_texture, ship_rect, 1, -1, 0);
            printf("3Final = %d\n", ship_rect[0].x);
            facingLeft = true;
            printf("Tick = %d\n", SDL_GetTicks64());
        }
        else if (key_state[SDL_SCANCODE_W])
        {
            render_char(ship_texture, ship_rect, 1, 0, 1);
            printf("3Final = %d\n", ship_rect[0].x);
            facingLeft = true;
            printf("Tick = %d\n", SDL_GetTicks64());
        }
        else if (key_state[SDL_SCANCODE_S])
        {
            render_char(ship_texture, ship_rect, 1, 0, -1);
            printf("3Final = %d\n", ship_rect[0].x);
            facingLeft = true;
            printf("Tick = %d\n", SDL_GetTicks64());
        }
    }

    for (u32 i = 0; i < 1; i++) {
        if (!ship_texture[i])
            break;
        SDL_DestroyTexture(ship_texture[i]);
    }
    free(ship_rect);
    free(ship_texture);
}

void kill(u32 value) {
    SDL_DestroyTexture(game->texture);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
    SDL_Quit();
    exit(value);
}