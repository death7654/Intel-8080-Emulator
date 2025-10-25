#include "../common.h"
#include "memory.hpp"
#include <SDL.h>

#define WIDTH 256
#define HEIGHT 224
#define SCALE 3

#define VRAM_SIZE 0x1C00
#define VRAM_START 0x2400
#define VRAM_END 0x3FFF

const u32 COLOR_ON  = 0xFFFFFFFF;
const u32 COLOR_OFF = 0xFF000000;

class display
{
private:
    // initialize SDL
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;

    u32 pixel_buffer[HEIGHT * WIDTH]; // space invaders has a screen that has been rotated by 90 degrees

    memory* ram;
public:
    display(memory* mem);
    ~display();

    void initialize_sdl();
    void draw_screen();
    void present();
};
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
