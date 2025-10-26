#pragma once 
#include "../common.h"
#include "../display/display.cpp"
#include "../memory/memory.cpp"
#include "../cpu/cpu.cpp"

class emulator
{

private:
    cpu CPU;

public:
    memory MEMORY;
    display DISPLAY;
    emulator(/* args */);
    ~emulator();
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
