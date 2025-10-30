#define SDL_MAIN_HANDLED

extern "C"
{
    #include <SDL3/SDL.h>
}

#include "../src/emulator/emulator.cpp"
#include <string>


int main(void)
{
    emulator emu;
    const char *path[] = {
        "../rom/invaders.h",
        "../rom/invaders.g",
        "../rom/invaders.f",
        "../rom/invaders.e",
    };
    const u32 starting_address[] = {
        0x0000,
        0x0800,
        0x1000,
        0x1800
    };

    // const char *path[] = 
    // {
    //     "../rom/cpu_tests/CPUTEST.COM"
    // };
    // const u32 starting_address[] = 
    // {
    //     0x0000,
    // };


    for(int i = 0; i < 4; i++)
    {
        emu.MEMORY.load_rom(path[i], starting_address[i]);
    }

    // emu.CPU.set_sp(0xFFFE);
    // emu.CPU.set_pc(0x100);
    

    emu.run();

    return 0;
}