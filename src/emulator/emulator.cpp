#include "emulator.hpp"

void emulator::run()
{
    bool is_running = true;
    u8 opcode;
    while(is_running)
    {
        opcode = cpu::fetch();
    }
}