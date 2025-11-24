#include "display.hpp"


void display::draw_screen()
{
    for(int address = VRAM_START; address < VRAM_END; address++)
    {
        u8 output = ram->read(address);
        u32 vram_offset = address - VRAM_START;

        for(int bit = 0; bit < 8; bit++)
        {
            bool pixel_on = ((output >> bit) & 1) == 1;

            int mem_y = (vram_offset % 32) * 8 + bit;
            int mem_x = vram_offset / 32; 

            int screen_x = mem_x;
            int screen_y = HEIGHT - 1 - mem_y;

            if (screen_x < 0 || screen_x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT) {
                continue;  // Skip invalid pixels
            }

            if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT) {
                int buffer_index = (screen_y * WIDTH) + screen_x;
                pixel_buffer[buffer_index] = pixel_on ? COLOR_ON : COLOR_OFF;
            }
        }
    }
}

void display::present()
{
    if (!renderer || !texture) {
        return; 
    }

    int pitch = WIDTH * sizeof(u32); 
    SDL_UpdateTexture(
        texture,          
        NULL,             
        pixel_buffer,    
        pitch             
    );

    // clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);  
    
    
    int x_offset = (WINDOW_W - SCALED_GAME_W) / 2;
    int y_offset = (WINDOW_H - SCALED_GAME_H) / 2;

    const SDL_FRect dest_rect = {
        (float)x_offset, 
        (float)y_offset, 
        (float)SCALED_GAME_W, 
        (float)SCALED_GAME_H
    };

    SDL_RenderTexture(renderer, texture, nullptr, &dest_rect); 
    SDL_RenderPresent(renderer);
}

