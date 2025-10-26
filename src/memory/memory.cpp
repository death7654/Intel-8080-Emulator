#include "memory.hpp"

u8 memory::read(u16 address)
{
    if(address < MEMORY_SIZE)
    {
        return memory_bank[address];
    }

    return 0xFF;
}

/*
    - The only writeable areas are Work RAM, Video Ram
        - Work Ram: 0x2000 - 0x23FF
        - Video Ram: 0x2400 - 0x3FFF
*/

void memory::write(u16 address, u8 data)
{
    
    if (address >= 0x0000 && address <= 0x1FFF)
    {
        // This is ROM
        return; 
    }

    if (address >= 0x2000 && address <= 0x3FFF)
    {
        memory_bank[address] = data;
        return; 
    }

}


// the original space invaders game is split into 4 different files, invaders.h -> invaders.g

void memory::load_rom(const char* path, u16 starting_address)
{
    // opens file with set address
    std::ifstream file(path, std::ios::binary | std::ios::ate); // binary indicates the start of the file, and ate to the end. Essentially allows for better reading

    // checks if the file is open
    if(!file.is_open())
    {
        printf("Unable to open file. Aborting...\n");
        return;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(starting_address + file_size > MEMORY_SIZE)
    {
        printf("Unable to Add File. Not Enough Emulator Ram");
        return;
    }

    file.read((char*)&memory_bank[starting_address], file_size);
    file.close();

}