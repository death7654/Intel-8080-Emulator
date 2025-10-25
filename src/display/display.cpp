#include "display.hpp"


void display::initialize_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to Initialize SDL\n Error: %s", SDL_GetError());
        return;
    }

    // create window
    window = SDL_CreateWindow("Space Invaders Emulator",
                                HEIGHT * SCALE,
                                WIDTH * SCALE,
                                0 // 0 flags
                              );

    // create renderer
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                HEIGHT,
                                WIDTH);
}

void display::draw_screen()
{
    for(int address = VRAM_START; address < VRAM_END; address++)
    {
        u8 output = ram->read(address);
        u32 vram_offset = address - VRAM_START;

        for(int bit = 0; bit < 8; bit++)
        {
            bool pixel_on = ((output >> bit)) & 1 == 1;

            int mem_x = (vram_offset % 32) * 8 + (7 - bit); 
            int mem_y = vram_offset / 32; 

            int screen_x = mem_y;
            int screen_y = HEIGHT - 1 - mem_x;

            int buffer_index = (screen_y * WIDTH) + screen_x;

            pixel_buffer[buffer_index] = pixel_on ? COLOR_ON : COLOR_OFF;
        }
    }
}

void display::present()
{
    if (!renderer || !texture) {
        return; 
    }

    int pitch = 224 * sizeof(u32); 
    SDL_UpdateTexture(
        texture,          
        NULL,             
        pixel_buffer,    
        pitch             
    );

    // clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);                      

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    SDL_RenderPresent(renderer);
}
