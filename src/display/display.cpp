#include "display.hpp"

void display::draw_screen()
{
    for(int address = VRAM_START; address < VRAM_END; address++)
    {
        u8 output = ram->read(address);
        u32 vram_offset = address - VRAM_START;

        // Space Invaders VRAM layout:
        // 224 rows of 32 bytes each = 7168 bytes
        // Each byte represents 8 pixels horizontally
        int byte_row_index = vram_offset / 32;  // Which row (0-223)
        int byte_col_index = vram_offset % 32;   // Which byte in row (0-31)

        for(int bit = 0; bit < 8; bit++)
        {
            bool pixel_on = ((output >> bit) & 1) == 1;

            // Calculate position in unrotated framebuffer
            // x: 0-255 (32 bytes × 8 bits)
            // y: 0-223 (224 rows)
            int x = (byte_col_index * 8) + bit; 
            int y = byte_row_index;

            // Space Invaders display is rotated 90° counter-clockwise
            // After rotation, our display buffer is WIDTH=224, HEIGHT=256
            // Transform: (x,y) -> (y, 255-x)
            // This maps:
            //   - x=0-31 (score area) -> pixel_y=224-255 (top of screen)
            //   - x=32-223 (game area) -> pixel_y=32-223 (middle)
            //   - x=224-255 (lives area) -> pixel_y=0-31 (bottom of screen)
            //   - y=0-223 -> pixel_x=0-223
            int pixel_x = y;
            int pixel_y = 255 - x;

            // Bounds check with correct WIDTH and HEIGHT
            if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT) 
            {
                // Buffer is WIDTH * HEIGHT = 224 * 256
                // Each row has WIDTH (224) pixels
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

    // Pitch is bytes per row = WIDTH * bytes_per_pixel
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