#include "emulator.hpp"
#include <iostream>

void emulator::run()
{
    const int CPU_HZ = 2000000;
    const int FPS = 60;
    const int CYCLES_PER_FRAME = CPU_HZ / FPS;
    const int CYCLES_TO_MID_SCREEN = CYCLES_PER_FRAME / 2;
    const int MS_PER_FRAME = 1000 / FPS;
    
    bool is_running = true;

    while(is_running)
    {
        Uint64 frame_start = SDL_GetTicks();
        
        int cycles_this_frame = 0;
        bool mid_screen_interrupt_triggered = false;
        
        while(cycles_this_frame < CYCLES_PER_FRAME)
        {
            u64 cycles_before = CPU.get_cycles();
            u8 opcode = CPU.fetch();
            CPU.execute(opcode);
            u64 cycles_after = CPU.get_cycles();
            
            if (cycles_after <= cycles_before) {
                std::cerr << "CPU error: cycles didn't advance" << std::endl;
                is_running = false;
                break;
            }
            
            u64 cycle_cost = cycles_after - cycles_before;
            cycles_this_frame += cycle_cost;

            if (!mid_screen_interrupt_triggered && cycles_this_frame >= CYCLES_TO_MID_SCREEN) {
                CPU.generate_interrupt(2);
                mid_screen_interrupt_triggered = true;
            }
        }
        
        if (!is_running) break;
        
        CPU.generate_interrupt(1);
        
        DISPLAY.draw_screen();
        DISPLAY.present();
        
        //is_running = handle_events();
        
        Uint64 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - frame_time);
        }
    }
}