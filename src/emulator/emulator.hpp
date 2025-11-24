#pragma once 
#include "../common.h"
#include "../display/display.cpp"
#include "../memory/memory.cpp"
#include "../cpu/cpu.cpp"
#include "../input/input.cpp"

#define CORE_FREQ 1996800

class emulator
{

private:

public:
    cpu CPU;
    memory MEMORY;
    display DISPLAY;
    input INPUT;
    emulator(/* args */);
    ~emulator();
    void run();
    bool handle_events();
};

emulator::emulator()
    : MEMORY(),
      INPUT(),  
      DISPLAY(&MEMORY), 
      CPU(&MEMORY, &INPUT)
{
}

emulator::~emulator()
{
}
