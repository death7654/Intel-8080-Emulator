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
    // const char *path[] = {
    //     "../rom/invaders.h",
    //     "../rom/invaders.g",
    //     "../rom/invaders.f",
    //     "../rom/invaders.e",
    // };
    // const u32 starting_address[] = {
    //     0x0000,
    //     0x0800,
    //     0x1000,
    //     0x1800
    // };

    const char *path[] = 
    {
        "../rom/cpu_tests/TST8080.COM"
    };
    const u32 starting_address[] = 
    {
        0x0100,
    };

    emu.MEMORY.set_debug_mode(true);


    for(int i = 0; i < 1; i++)
    {
        emu.MEMORY.load_rom(path[i], starting_address[i]);
    }

    emu.MEMORY.write(0x0000, 0xC9);  // JMP opcode
    emu.MEMORY.write(0x0001, 0x00);  // low byte of 0100h
    emu.MEMORY.write(0x0002, 0x01);  // high byte of 0100h

    // 0005h: RET (in case BDOS is not hooked properly)
    emu.MEMORY.write(0x0005, 0xC9);

    // ---- Initialize CPU ----
    emu.CPU.set_sp(0xF000); // stack near top of RAM
    emu.CPU.set_pc(0x0100); // start execution at CP/M program start

    emu.run();

    return 0;
}