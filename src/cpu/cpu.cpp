#include "../common.h"
#include "cpu.hpp"

#define get_register(reg) \
    u8 cpu::get_##reg()   \
    {                     \
        return this->reg; \
    }
#define get_register_16bit(high_reg, low_reg)         \
    u16 cpu::get_##high_reg##low_reg()                \
    {                                                 \
        return (this->high_reg << 8) | this->low_reg; \
    }

#define set_register(reg)        \
    void cpu::set_##reg(u8 data) \
    {                            \
        this->reg = data;        \
    }

#define set_register_16bit(high_reg, low_reg)   \
    void cpu::set_##high_reg##low_reg(u16 data) \
    {                                           \
        this->a = data >> 8;                    \
        this->b = (u8)data;                     \
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

u8 cpu::fetch()
{
    u8 instruction = ram->read(this->pc);
    this->pc++;
    return instruction;
}

void cpu::execute(u8 instruction)
{
    this->cycles += 4; // each instruction fetch uses 4 cycles
    switch (instruction)
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
    case 0x03:
        inx(this->b, this->c);
        break;
    case 0x04:
        inr(this->b);
        break;
    case 0x05:
        dcr(this->b);
        break;
    case 0x06:
        mvi(this->b);
        break;
    case 0x07:
        rlc();
        break;
    case 0x08:
        nop();
        break;
    case 0x09:
        dad(this->b, this->c);
        break;
    case 0x0A:
        ldax(this->b, this->c);
        break;
    case 0x0B:
        dcx(this->b, this->c);
        break;
    case 0x0C:
        inr(this->c);
        break;
    case 0x0D:
        dcr(this->b);
        break;
    case 0x0E:
        mvi(this->c);
        break;
    case 0x0F:
        rrc();
        break;
    }
}

// set flags
void cpu::set_s_flag(u8 &reg)
{
    u8 f_reg = get_f();
    if ((reg & 0x80) != 0)
    {
        f_reg |= S_FLAG;
    }
    else
    {
        f_reg &= ~S_FLAG;
    }

    set_f(f_reg);
}

void cpu::set_z_flag(u8 &reg)
{
    u8 f_reg = get_f();
    if (reg == 0)
    {
        f_reg |= Z_FLAG;
    }
    else
    {
        f_reg &= ~Z_FLAG;
    }
    set_f(f_reg);
}

// the a flag is complex, depends on the amount added or subtracted, hence the function split

void cpu::set_a_flag_add_type(u8 val1, u8 val2, bool is_increment)
{
    u8 f_reg = get_f();
    bool condition;

    if (is_increment)
    {
        condition = (val1 & 0x0F) == 0x0F;
    }
    else
    {
        condition = ((val1 & 0x0F) + (val2 & 0x0F)) > 0x0F;
    }

    if (condition)
    {
        f_reg |= A_FLAG;
    }
    else
    {
        f_reg &= ~A_FLAG;
    }
    set_f(f_reg);
}

void cpu::set_a_flag_sub_type(u8 val1, u8 val2, bool is_decrement)
{
    u8 f_reg = get_f();
    bool condition;

    if (is_decrement)
    {
        condition = (val1 & 0x0F) == 0x00;
    }
    else
    {
        condition = (val1 & 0x0F) < (val2 & 0x0F);
    }

    if (condition)
    {
        f_reg |= A_FLAG;
    }
    else
    {
        f_reg &= ~A_FLAG;
    }
    set_f(f_reg);
}

void cpu::set_p_flag(u8 &reg)
{
    // checks for the number of 1 bits
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if ((reg >> i & 0x01) == 1)
        {
            count++;
        }
    }

    u8 f_reg = get_f();
    if (count % 2 == 0)
    {
        f_reg |= P_FLAG;
    }
    else
    {
        f_reg &= ~P_FLAG;
    }

    set_f(f_reg);
}

void cpu::set_c_flag(bool condition)
{
    u8 f_reg = get_f();
    if (condition) {
        f_reg |= C_FLAG;
    } else {
        f_reg &= ~C_FLAG;
    }
    set_f(f_reg);
}

// Operation codes
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
    this->cycles += 3;

    high_byte = ram->read(this->pc + 2);
    this->cycles += 3;
    // 10 cycles
}

// store the accumulator at the address specifed by the highbyte and lowbyte
void cpu::stax(u8 &high_byte, u8 &low_byte)
{
    u16 address = (static_cast<u16>(high_byte) << 8) | low_byte;
    u8 data = get_a();
    ram->write(address, data);

    this->cycles += 3;

    // 7 cycles
}
// increment a 16 bit register
void cpu::inx(u8 &high_byte, u8 &low_byte)
{
    u16 data = (static_cast<u16>(high_byte) << 8) | low_byte;
    data += 1;
    high_byte = data >> 8;
    low_byte = data;
    this->cycles += 1;

    // 5 cycles
}
// increment an 8 bit register
void cpu::inr(u8 &reg)
{
    u8 old_value = reg;
    reg++;
    set_s_flag(reg);
    set_z_flag(reg);
    set_a_flag_add_type(old_value, reg, true);
    set_p_flag(reg);

    this->cycles++;
    // 5 cycles
}
// decrement an 8 bit register
void cpu::dcr(u8 &reg)
{
    u8 old_value = reg;
    reg--;
    set_s_flag(reg);
    set_z_flag(reg);
    set_a_flag_sub_type(old_value, reg, true);
    set_p_flag(reg);

    this->cycles++;
    // 5 cycles
}

// copy the intermediate value from memory onto a register
void cpu::mvi(u8 &reg)
{
    u8 data = ram->read(this->pc);
    this->pc++;
    reg = data;
    this->cycles += 3;
    // 7 cycles
}

// rotate the accumulator left
void cpu::rlc()
{
    u8 data = get_a();
    u8 msb = data & 0x80;
    data = data << 1 | msb;
    set_a(data);
    set_c_flag(msb != 0);

    // 4 cycles
}
// double add 16 bit reg
void cpu::dad(u8 &upper_a_reg, u8 &lower_a_reg)
{
    u16 a = (static_cast<u16>(upper_a_reg << 8)) | lower_a_reg;
    u16 b = get_hl();
    u32 result = a + b; // 32 bit to check for overflow

    set_hl(static_cast<u16>(result));
    set_c_flag(result > 0xFFFF);

    this->cycles += 6;
    // takes 10 cycles
}

// load data from memory at address found in 16 bit register pair
void cpu::ldax(u8 &upper_reg, u8 &lower_reg)
{
    u16 address = (static_cast<u16>(upper_reg << 8)) | lower_reg;
    u8 data = ram->read(address);
    set_a(data);

    this->cycles +=3;
    // 7 cycles
}

// decrement 16 bit register 
void cpu::dcx(u8 &upper_reg, u8 &lower_reg)
{
    u16 data = (static_cast<u16>(upper_reg << 8)) | lower_reg;
    data--;
    upper_reg = data >> 8;
    lower_reg = static_cast<u8>(data);
    this->cycles+=2;

    // 6 cycles
}

// rotate accumulator right
void cpu::rrc()
{
    u8 a = get_a();
    u8 lsb = a & 0x01;
    a = (a >> 1) | (lsb << 7);
    set_a(a);
    set_c_flag(lsb != 0);

    // takes 4 cycles
}


// push value from a 16 bit register onto stack
void cpu::push(u8 &upper_reg, u8 &lower_reg)
{
    this->sp--;
    ram->write(this->sp, upper_reg);
    this->sp--;
    ram->write(this->sp, lower_reg);
    this->cycles += 7;

    // 11 cycles
}

// retrieve a 16 bit value from stack
void cpu::pop(u8 &upper_reg, u8 &lower_reg)
{
    lower_reg = ram->read(this->sp);
    this->sp++;
    upper_reg = ram->read(this->sp);
    this->sp++;

    this->cycles += 6;
    // 10 cycles
}

