#include "../common.h"
#include "cpu.hpp"

#define get_register(reg) \
u8 cpu::get_##reg() \
{ \
    return this->reg; \
}
#define get_register_16bit(high_reg, low_reg) \
u16 cpu::get_##high_reg##low_reg() \
{ \
    return (this->high_reg << 8) | this->low_reg; \
}

#define set_register(reg) \
void cpu::set_##reg(u8 data) \
{ \
    this->reg = data; \
}

#define set_register_16bit(high_reg, low_reg) \
void cpu::set_##high_reg##low_reg(u16 data)\
{ \
    this->a = data >> 8;\
    this->b = (u8)data;\
}

get_register(a);
get_register(b);
get_register(c);
get_register(d);
get_register(e);
get_register(h);
get_register(l);
get_register(f);

set_register(a);
set_register(b);
set_register(c);
set_register(d);
set_register(e);
set_register(h);
set_register(l);
set_register(f);

get_register_16bit(b, c);
get_register_16bit(d, e);
get_register_16bit(h, l);

set_register_16bit(b, c);
set_register_16bit(d, e);
set_register_16bit(h, l);

void cpu::push(u16 data)
{
    u8 higher = (data >> 8) & 0xFF;
    u8 lower = (data & 0xFF);
    sp--;
    ram->write(sp, higher);
    sp--;
    ram->write(sp-2, lower);
}

u16 cpu::pop()
{
    u8 lower = ram->read(sp);
    sp++;
    u8 higher = ram->read(sp);
    sp++;

    return (higher << 8) | lower;
}

u8 cpu::fetch()
{
    u8 instruction = ram->read(pc);
    pc++;
    return instruction;
}

void cpu::execute(u8 instruction)
{
    this->cycles += 4; // each instruction fetch uses 4 cycles
    switch(instruction)
    {
        // NOP
        case 0x00:
            nop();
            break;
        // LXI
        case 0x01:
            lxi(this->b, this->c);
            break;
        case 0x02:
            stax(this->b, this->c);
            break;
            

    }

}
// do nothing instruction
void cpu::nop()
{
    return;
    // 4 cycles
}

// load eXtensible instruction (16 bit load)
void cpu::lxi(u8 &high_byte, u8 &low_byte)
{
    low_byte = ram->read(this->pc + 1);
    this->cycles +=3;

    high_byte = ram->read(this->pc + 2);
    this->cycles += 3;

    this->pc += 2;

    // 10 cycles
}

// store the accumulator at the address specifed by the highbyte and lowbyte
void cpu::stax(u8 &high_byte, u8 &low_byte)
{
    u16 address = (static_cast<u16>(high_byte) << 8 )| low_byte;
    u8 data = get_a();
    ram->write(address, data);

    this->cycles +=3; 

    // 7 cycles
}




