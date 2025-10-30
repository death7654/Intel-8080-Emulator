#include "memory.hpp"
#include <cstdio>

u8 memory::read(u16 address)
{
    // Handle RAM mirroring (0x4000+ mirrors 0x2000-0x3FFF)
    if (address >= 0x4000) {
        address = 0x2000 + ((address - 0x2000) & 0x1FFF);
    }
    
    if(address < MEMORY_SIZE)
    {
        return memory_bank[address];
    }

    return 0xFF;
}

void memory::write(u16 address, u8 data)
{
    // Handle RAM mirroring (0x4000+ mirrors 0x2000-0x3FFF)
    if (address >= 0x4000) {
        address = 0x2000 + ((address - 0x2000) & 0x1FFF);
    }
    
    if (address >= 0x0000 && address <= 0x1FFF)
    {
        // ROM area - writes ignored
        return; 
    }

    if (address >= 0x2000 && address <= 0x3FFF)
    {
        memory_bank[address] = data;
    }
}

bool memory::load_rom(const char* path, u16 starting_address)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if(!file.is_open())
    {
        fprintf(stderr, "ERROR: Unable to open ROM file: %s\n", path);
        return false;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(file_size < 0)
    {
        fprintf(stderr, "ERROR: Invalid file size for: %s\n", path);
        file.close();
        return false;
    }

    if(file_size > MEMORY_SIZE || starting_address > MEMORY_SIZE - file_size)
    {
        fprintf(stderr, "ERROR: ROM too large. Size: %lld, Start: 0x%04X, Memory: 0x%04X\n", 
                (long long)file_size, starting_address, MEMORY_SIZE);
        file.close();
        return false;
    }

    if(!file.read(reinterpret_cast<char*>(&memory_bank[starting_address]), file_size))
    {
        fprintf(stderr, "ERROR: Failed to read ROM data from: %s\n", path);
        file.close();
        return false;
    }
    
    file.close();
    
    printf("Loaded ROM: %s (%lld bytes at 0x%04X)\n", path, (long long)file_size, starting_address);
    return true;
}