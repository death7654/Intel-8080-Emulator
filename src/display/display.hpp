#pragma once 

#define SDL_MAIN_HANDLED
extern "C"
{
    #include <SDL3/SDL.h>
}
#include "../common.h"
#include "../memory/memory.hpp"

#define WIDTH 256
#define HEIGHT 224
#define SCALE 3

#define VRAM_SIZE 0x1C00
#define VRAM_START 0x2400
#define VRAM_END 0x4000

#define WINDOW_W 800
#define WINDOW_H 800 
#define SCALED_GAME_W (WIDTH * SCALE) 
#define SCALED_GAME_H (HEIGHT * SCALE) 

const u32 COLOR_ON  = 0xFFFFFFFF;
const u32 COLOR_OFF = 0xFF000000;

class display
{
private:
    // initialize SDL
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;

    u32 pixel_buffer[WIDTH * HEIGHT]; // space invaders has a screen that has been rotated by 90 degrees

    memory* ram;
public:
    display(memory* mem);
    ~display();

    void initialize_sdl();
    void draw_screen();
    void present();

    void create_window();
};

void display::initialize_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to Initialize SDL\n Error: %s", SDL_GetError());
        return;
    }


    window = SDL_CreateWindow("Space Invaders Emulator",
                              WINDOW_W,
                              WINDOW_H,
                              0);

    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return;
    }
    
    renderer = SDL_CreateRenderer(window, NULL);
    
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return;
    }
    
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                WIDTH,
                                HEIGHT);
}
display::display(memory* mem) : ram(mem)
{
    memset(pixel_buffer, 0, sizeof(pixel_buffer));
    initialize_sdl();
}

display::~display()
{
    // cleanup
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
