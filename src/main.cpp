#define SDL_MAIN_HANDLED

extern "C"
{
    #include <SDL3/SDL.h>
}

#include "../src/emulator/emulator.hpp"
#include <string>


int main(void)
{
    emulator emu;
    const char *path[] = {
        "/rom/invaders.h",
        "/rom/invaders.g",
        "/rom/invaders.f",
        "/rom/invaders.e",
    };
    const u32 starting_address[] = {
        0x0000,
        0x2048,
        0x4096,
        0x6144
    };
    for(int i = 0; i < 4; i++)
    {
        emu.MEMORY.load_rom(path[i], starting_address[i]);
    }

    return 0;
}