#include "memory.hpp"

u8 memory::read(u16 address)
{
    return memory::memory_bank[address];
}

void memory::write(u16 address, u8 data)
{
    memory::memory_bank[address] = data;
}