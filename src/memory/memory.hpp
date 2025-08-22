#include "../common.h"

class memory
{
private:
    u8 memory_bank[65536];
public:
    u8 read(u16 address);
    void write(u16 address, u8 data);

    memory(/* args */);
    ~memory();
};

memory::memory(/* args */)
{
}

memory::~memory()
{
}
