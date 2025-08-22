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



