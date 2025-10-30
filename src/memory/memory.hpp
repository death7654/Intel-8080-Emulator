#pragma once 
#include "../common.h"

#define MEMORY_SIZE 65536

class memory
{
private:
    u8 memory_bank[MEMORY_SIZE];
public:
    u8 read(u16 address);
    void write(u16 address, u8 data);
    bool load_rom(const char* path, u16 starting_address);
    
    memory(/* args */);
    ~memory();
};


memory::memory(/* args */)
{
    // set the entire memory bank to 0 to remove any garbage values
    memset(memory_bank, 0, sizeof(memory_bank));
}

memory::~memory()
{
}
