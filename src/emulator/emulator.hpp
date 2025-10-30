#pragma once 
#include "../common.h"
#include "../display/display.cpp"
#include "../memory/memory.cpp"
#include "../cpu/cpu.cpp"

#define CORE_FREQ 1996800

class emulator
{

private:

public:
    cpu CPU;
    memory MEMORY;
    display DISPLAY;
    emulator(/* args */);
    ~emulator();
    void run();
};

emulator::emulator()
    : MEMORY(), 
      DISPLAY(&MEMORY), 
      CPU(&MEMORY)
{
}

emulator::~emulator()
{
}
