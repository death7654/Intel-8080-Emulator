#include "display.hpp"

void display::draw_screen()
{
    for(int address = VRAM_START; address < VRAM_END; address++)
    {
        u8 output = ram->read(address);
        u32 vram_offset = address - VRAM_START;

        
        int byte_row_index = vram_offset / 32;  
        int byte_col_index = vram_offset % 32;   

        for(int bit = 0; bit < 8; bit++)
        {
            bool pixel_on = ((output >> bit) & 1) == 1;

           
            int x = (byte_col_index * 8) + bit; 
            int y = byte_row_index;

      
            int pixel_x = y;
            int pixel_y = 255 - x;

            if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT) 
            {
                int buffer_index = (pixel_y * WIDTH) + pixel_x;
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);    
    


    SDL_RenderTexture(renderer, texture, nullptr, nullptr); 
    SDL_RenderPresent(renderer);
}