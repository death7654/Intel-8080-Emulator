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
        this->b = static_cast<u8>(data);        \
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

u16 cpu::get_sp()
{
    return this->sp;
}

set_register_16bit(b, c);
set_register_16bit(d, e);
set_register_16bit(h, l);

void cpu::set_sp(u16 data)
{
    this->sp = data;
}

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
    // 0x00 -> 0x0F
    case 0x00:
        nop();
        break;
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
        dcr(this->c);
        break;
    case 0x0E:
        mvi(this->c);
        break;
    case 0x0F:
        rrc();
        break;
    // 0x10 - 0x1F
    case 0x10:
        nop();
        break;
    case 0x11:
        lxi(this->d, this->e);
        break;
    case 0x12:
        stax(this->d, this->e);
        break;
    case 0x13:
        inx(this->d, this->e);
        break;
    case 0x14:
        inr(this->d);
        break;
    case 0x15:
        dcr(this->d);
        break;
    case 0x16:
        mvi(this->d);
        break;
    case 0x17:
        ral();
        break;
    case 0x18:
        nop();
        break;
    case 0x19:
        dad(this->d, this->e);
        break;
    case 0x1A:
        ldax(this->d, this->e);
        break;
    case 0x1B:
        dcx(this->d, this->e);
        break;
    case 0x1C:
        inr(this->e);
        break;
    case 0x1D:
        dcr(this->e);
        break;
    case 0x1E:
        mvi(this->e);
        break;
    case 0x1F:
        rar();
        break;
    // 0x20 => 0x2F
    case 0x20:
        nop();
        break;
    case 0x21:
        lxi(this->h, this->f);
        break;
    case 0x22:
        shld();
        break;
    case 0x23:
        inx(this->h, this->l);
        break;
    case 0x24:
        inr(this->h);
        break;
    case 0x25:
        dcr(this->h);
        break;
    case 0x26:
        mvi(this->h);
        break;
    case 0x27:
        daa();
        break;
    case 0x28:
        nop();
        break;
    case 0x29:
        dad(this->h, this->l);
        break;
    case 0x2A:
        lhld();
        break;
    case 0x2B:
        dcx(this->h, this->l);
        break;
    case 0x2C:
        inr(this->l);
        break;
    case 0x2D:
        dcr(this->l);
        break;
    case 0x2E:
        mvi(this->l);
        break;
    case 0x2F:
        cma();
        break;
    // 0x30 - 0x3F
    case 0x30:
        nop();
        break;
    case 0x31:
        lxi_sp();
        break;
    case 0x32:
        sta();
        break;
    case 0x33:
        inx_sp();
        break;
    case 0x34:
        inr_m();
        break;
    case 0x35:
        dcr_m();
        break;
    case 0x36:
        mvi_m();
        break;
    case 0x37:
        stc();
        break;
    case 0x38:
        nop();
        break;
    case 0x39:
        dad_sp();
        break;
    case 0x3A:
        lda();
        break;
    case 0x3B:
        dcx_sp();
        break;
    case 0x3C:
        inr(this->a);
        break;
    case 0x3D:
        dcr(this->a);
        break;
    case 0x3E:
        mvi(this->a);
        break;
    case 0x3F:
        cmc();
        break;
    // 0x40 -> 0x4F
    case 0x40:
        mov(this->b, this->b);
        break;
    case 0x41:
        mov(this->b, this->c);
        break;
    case 0x42:
        mov(this->b, this->d);
        break;
    case 0x43:
        mov(this->b, this->e);
        break;
    case 0x44:
        mov(this->b, this->h);
        break;
    case 0x45:
        mov(this->b, this->l);
        break;
    case 0x46:
        mov_rm(this->b);
        break;
    case 0x47:
        mov(this->b, this->a);
        break;
    case 0x48:
        mov(this->c, this->b);
        break;
    case 0x49:
        mov(this->c, this->c);
        break;
    case 0x4A:
        mov(this->c, this->d);
        break;
    case 0x4B:
        mov(this->c, this->e);
        break;
    case 0x4C:
        mov(this->c, this->h);
        break;
    case 0x4D:
        mov(this->c, this->l);
        break;
    case 0x4E:
        mov_rm(this->c);
        break;
    case 0x4F:
        mov(this->c, this->a);
        break;
    // 0x50 -> 0x5F
    case 0x50:
        mov(this->d, this->b);
        break;
    case 0x51:
        mov(this->d, this->c);
        break;
    case 0x52:
        mov(this->d, this->d);
        break;
    case 0x53:
        mov(this->d, this->e);
        break;
    case 0x54:
        mov(this->d, this->h);
        break;
    case 0x55:
        mov(this->d, this->l);
        break;
    case 0x56:
        mov_rm(this->d);
        break;
    case 0x57:
        mov(this->d, this->a);
        break;
    case 0x58:
        mov(this->e, this->b);
        break;
    case 0x59:
        mov(this->e, this->c);
        break;
    case 0x5A:
        mov(this->e, this->d);
        break;
    case 0x5B:
        mov(this->e, this->e);
        break;
    case 0x5C:
        mov(this->e, this->h);
        break;
    case 0x5D:
        mov(this->e, this->l);
        break;
    case 0x5E:
        mov_rm(this->e);
        break;
    case 0x5F:
        mov(this->e, this->a);
        break;
    // 0x60 -> 0x6F
    case 0x60:
        mov(this->h, this->b);
        break;
    case 0x61:
        mov(this->h, this->c);
        break;
    case 0x62:
        mov(this->h, this->d);
        break;
    case 0x63:
        mov(this->h, this->e);
        break;
    case 0x64:
        mov(this->h, this->h);
        break;
    case 0x65:
        mov(this->h, this->l);
        break;
    case 0x66:
        mov_rm(this->h);
        break;
    case 0x67:
        mov(this->h, this->a);
        break;
    case 0x68:
        mov(this->l, this->b);
        break;
    case 0x69:
        mov(this->l, this->c);
        break;
    case 0x6A:
        mov(this->l, this->d);
        break;
    case 0x6B:
        mov(this->l, this->e);
        break;
    case 0x6C:
        mov(this->l, this->h);
        break;
    case 0x6D:
        mov(this->l, this->l);
        break;
    case 0x6E:
        mov_rm(this->l);
        break;
    case 0x6F:
        mov(this->l, this->a);
        break;
    case 0x70:
        mov_mr(this->b);
        break;
    case 0x71:
        mov_mr(this->c);
        break;
    case 0x72:
        mov_mr(this->d);
        break;
    case 0x73:
        mov_mr(this->e);
        break;
    case 0x74:
        mov_mr(this->h);
        break;
    case 0x75:
        mov_mr(this->l);
        break;
    case 0x76:
        halt();
        break;
    case 0x77:
        mov_mr(this->a);
        break;
    case 0x78:
        mov(this->a, this->b);
        break;
    case 0x79:
        mov(this->a, this->c);
        break;
    case 0x7A:
        mov(this->a, this->d);
        break;
    case 0x7B:
        mov(this->a, this->e);
        break;
    case 0x7C:
        mov(this->a, this->h);
        break;
    case 0x7D:
        mov(this->a, this->l);
        break;
    case 0x7E:
        mov_rm(this->a);
        break;
    case 0x7F:
        mov(this->a, this->a);
        break;
    // 0x80 -> 0x8F
    case 0x80:
        add(this->b);
        break;
    case 0x81:
        add(this->c);
        break;
    case 0x82:
        add(this->d);
        break;
    case 0x83:
        add(this->e);
        break;
    case 0x84:
        add(this->h);
        break;
    case 0x85:
        add(this->l);
        break;
    case 0x86:
        add_m();
        break;
    case 0x87:
        add(this->a);
        break;
    case 0x88:
        adc(this->b);
        break;
    case 0x89:
        adc(this->c);
        break;
    case 0x8A:
        adc(this->d);
        break;
    case 0x8B:
        adc(this->e);
        break;
    case 0x8C:
        adc(this->h);
        break;
    case 0x8D:
        adc(this->l);
        break;
    case 0x8E:
        adc_m();
        break;
    case 0x8F:
        adc(this->a);
        break;
    // 0x90 -> 0x9F
    case 0x90:
        sub(this->b);
        break;
    case 0x91:
        sub(this->c);
        break;
    case 0x92:
        sub(this->d);
        break;
    case 0x93:
        sub(this->e);
        break;
    case 0x94:
        sub(this->h);
        break;
    case 0x95:
        sub(this->l);
        break;
    case 0x96:
        sub_m();
        break;
    case 0x97:
        sub(this->a);
        break;
    case 0x98:
        sbb(this->b);
        break;
    case 0x99:
        sbb(this->c);
        break;
    case 0x9A:
        sbb(this->d);
        break;
    case 0x9B:
        sbb(this->e);
        break;
    case 0x9C:
        sbb(this->h);
        break;
    case 0x9D:
        sbb(this->l);
        break;
    case 0x9E:
        sbb_m();
        break;
    case 0x9F:
        sbb(this->a);
        break;
    // 0xA0 -> 0xAF
    case 0xA0:
        ana(this->b);
        break;
    case 0xA1:
        ana(this->c);
        break;
    case 0xA2:
        ana(this->d);
        break;
    case 0xA3:
        ana(this->e);
        break;
    case 0xA4:
        ana(this->h);
        break;
    case 0xA5:
        ana(this->l);
        break;
    case 0xA6:
        ana_m();
        break;
    case 0xA7:
        ana(this->a);
        break;
    case 0xA8:
        xra(this->b);
        break;
    case 0xA9:
        xra(this->c);
        break;
    case 0xAA:
        xra(this->d);
        break;
    case 0xAB:
        xra(this->e);
        break;
    case 0xAC:
        xra(this->h);
        break;
    case 0xAD:
        xra(this->l);
        break;
    case 0xAE:
        xra_m();
        break;
    case 0xAF:
        xra(this->a);
        break;
    // 0xB0 -> 0xBF
    case 0xB0:
        ora(this->b);
        break;
    case 0xB1:
        ora(this->c);
        break;
    case 0xB2:
        ora(this->d);
        break;
    case 0xB3:
        ora(this->e);
        break;
    case 0xB4:
        ora(this->h);
        break;
    case 0xB5:
        ora(this->l);
        break;
    case 0xB6:
        ora_m();
        break;
    case 0xB7:
        ora(this->a);
        break;
    case 0xB8:
        cmp(this->b);
        break;
    case 0xB9:
        cmp(this->c);
        break;
    case 0xBA:
        cmp(this->d);
        break;
    case 0xBB:
        cmp(this->e);
        break;
    case 0xBC:
        cmp(this->h);
        break;
    case 0xBD:
        cmp(this->l);
        break;
    case 0xBE:
        cmp_m();
        break;
    case 0xBF:
        cmp(this->a);
        break;
    // 0xC0 - 0xCF
    case 0xC0:
        rnz();
        break;
    case 0xC1:
        pop(this->b, this->c);
        break;
    case 0xC2:
        jnz();
        break;
    case 0xC3:
        jmp();
        break;
    case 0xC4:
        cnz();
        break;
    case 0xC5:
        push(this->b, this->c);
        break;
    case 0xC6:
        adi();
        break;
    case 0xC7:
        rst(0);
        break;
    case 0xC8:
        rz();
        break;
    case 0xC9:
        ret();
        break;
    case 0xCA:
        jz();
        break;
    case 0xCB:
        jmp();
        break;
    case 0xCC:
        cz();
        break;
    case 0xCD:
        call();
        break;
    case 0xCE:
        aci();
        break;
    case 0xCF:
        rst(1);
        break;

    // 0xD0 -> 0xDF
    case 0xD0:
        rnc();
        break;
    case 0xD1:
        pop(this->d, this->e);
        break;
    case 0xD2:
        jnc();
        break;
    case 0xD3:
        out();
        break;
    case 0xD4:
        cnc();
        break;
    case 0xD5:
        push(this->d, this->e);
        break;
    case 0xD6:
        sui();
        break;
    case 0xD7:
        rst(2);
        break;
    case 0xD8:
        rc();
        break;
    case 0xD9:
        break;
    case 0xDA:
        jc();
        break;
    case 0xDB:
        in();
        break;
    case 0xDC:
        cc();
        break;
    case 0xDD:
        break;
    case 0xDE:
        sbi();
        break;
    case 0xDF:
        rst(3);
        break;
        // 0xE0 ->0xEF
    case 0xE0:
        rpo();
        break;
    case 0xE1:
        pop(this->h, this->l);
        break;
    case 0xE2:
        jpo();
        break;
    case 0xE3:
        xthl();
        break;
    case 0xE4:
        cpo();
        break;
    case 0xE5:
        push(this->h, this->l);
        break;
    case 0xE6:
        ani();
        break;
    case 0xE7:
        rst(4);
        break;
    case 0xE8:
        rpe();
        break;
    case 0xE9:
        pchl();
        break;
    case 0xEA:
        jpe();
        break;
    case 0xEB:
        xchg();
        break;
    case 0xEC:
        cpe();
        break;
    case 0xED:
        break;
    case 0xEE:
        xri();
        break;
    case 0xEF:
        rst(5);
        break;

    case 0xF0:
        rp();
        break;
    case 0xF1:
        rp();
        break;
    case 0xF2:
        jp();
        break;
    case 0xF3:
        di();
        break;
    case 0xF4:
        cp();
        break;
    case 0xF5:
        push(this->a, this->f);
        break;
    case 0xF6:
        ori();
        break;
    case 0xF7:
        rst(6);
        break;
    case 0xF8:
        rm();
        break;
    case 0xF9:
        sphl();
        break;
    case 0xFA:
        jm();
        break;
    case 0xFB:
        ei();
        break;
    case 0xFC:
        cm();
        break;
    case 0xFD:
        break;
    case 0xFE:
        cpi();
        break;
    case 0xFF:
        rst(7);
        break;
    default:
        printf("OPCODE not implemented %d", instruction);
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

void cpu::set_a_flag_boolean(bool condition)
{
    u8 f_reg = get_f();
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
    if (condition)
    {
        f_reg |= C_FLAG;
    }
    else
    {
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
    low_byte = fetch();
    this->cycles += 3;

    high_byte = fetch();
    this->cycles += 3;
    // 10 cycles
}

// load sp value from the next 2 bytes
void cpu::lxi_sp()
{
    u8 sp_lower = fetch();
    this->cycles += 3;

    u8 sp_upper = fetch();
    this->cycles += 3;

    u16 data = (static_cast<u16>(sp_upper) << 8) | sp_lower;
    set_sp(data);
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

void cpu::inx_sp()
{
    u16 sp = get_sp();
    set_sp(sp + 1);
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
// increment memory
void cpu::inr_m()
{
    u16 address = get_hl();

    u8 old_data = ram->read(address);
    this->cycles += 3;

    u8 new_data = old_data + 1;
    ram->write(address, new_data);
    this->cycles += 3;

    set_s_flag(new_data);
    set_z_flag(new_data);
    set_a_flag_add_type(old_data, new_data, true);
    set_p_flag(new_data);

    // 10 cycles
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

// decrement memory
void cpu::dcr_m()
{
    u16 address = get_hl();

    u8 old_data = ram->read(address);
    this->cycles += 3;

    u8 new_data = old_data - 1;
    ram->write(address, new_data);
    this->cycles += 3;

    set_s_flag(new_data);
    set_z_flag(new_data);
    set_a_flag_sub_type(old_data, new_data, true);
    set_p_flag(new_data);

    // 10 cycles
}

// copy the intermediate value from memory onto a register
void cpu::mvi(u8 &reg)
{
    u8 data = fetch();
    reg = data;
    this->cycles += 3;
    // 7 cycles
}

void cpu::mvi_m()
{
    u16 address = get_hl();
    u8 data = fetch();

    ram->write(address, data);
    this->cycles += 6;

    // 10 cycles
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

    set_c_flag(result > 0xFFFF);

    set_hl(static_cast<u16>(result));

    this->cycles += 6;
    // takes 10 cycles
}

// double add stack pointer
void cpu::dad_sp()
{
    u16 sp = get_sp();
    u16 hl = get_hl();
    u32 result = sp + hl;

    set_c_flag(result > 0xFFFF);

    set_hl(static_cast<u16>(result));

    this->cycles += 6;
    // 10 cycles
}

// load data from memory at address found in 16 bit register pair
void cpu::ldax(u8 &upper_reg, u8 &lower_reg)
{
    u16 address = (static_cast<u16>(upper_reg << 8)) | lower_reg;
    u8 data = ram->read(address);
    set_a(data);

    this->cycles += 3;
    // 7 cycles
}

// decrement 16 bit register
void cpu::dcx(u8 &upper_reg, u8 &lower_reg)
{
    u16 data = (static_cast<u16>(upper_reg << 8)) | lower_reg;
    data--;
    upper_reg = data >> 8;
    lower_reg = static_cast<u8>(data);
    this->cycles += 2;

    // 6 cycles
}

// decrement sp
void cpu::dcx_sp()
{
    u16 sp = get_sp();
    sp--;
    set_sp(sp);
    this->cycles += 2;
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

// treats the carry flag as the 9th bit and does a rotate left
void cpu::ral()
{
    u8 a = get_a();
    u8 msb = a & 0x80;
    bool carry_flag = (get_f() & 0x01) != 0;
    a = a << 1;

    if (carry_flag)
    {
        a |= 0x01;
    }
    set_a(a);

    set_c_flag(msb != 0);
    // takes 4 cycles
}

// treats the carry flag as the 9th bit and does a rotate right
void cpu::rar()
{
    u8 a = get_a();
    u8 lsb = a & 0x01;
    bool original_carry_flag = (get_f() & 0x01) != 0;

    a >>= 1;

    if (original_carry_flag)
    {
        a |= 0x80;
    }
    else
    {
        a &= ~0x80;
    }

    set_a(a);

    set_c_flag(lsb != 0);

    // 4 cycles
}

// store the 16 bit register HL into memory
void cpu::shld()
{
    u8 lower_address = fetch();
    this->cycles += 3;

    u8 upper_address = fetch();
    this->cycles += 3;

    u16 address = (static_cast<u16>(upper_address) << 8) | lower_address;

    ram->write(address, this->l);
    this->cycles += 3;

    ram->write(address + 1, this->h);
    this->cycles += 3;

    // 16 cycles
}

// converts a illegal bcd into legal bcd
void cpu::daa()
{
    u8 old_a = get_a();
    u8 a = old_a;

    u8 current_flags = get_f();
    bool original_carry = (current_flags & 0x01) != 0;
    bool original_aux_carry = (current_flags & 0b00010010) != 0;

    bool carry_set_by_daa_adjustment = false;
    bool aux_carry_set_by_daa_adjustment = false;

    if ((a & 0x0F) > 0x09 || original_aux_carry)
    {
        a += 0x06;
        aux_carry_set_by_daa_adjustment = true;
    }

    if ((a & 0xF0) > 0x90 || original_carry)
    {
        u16 temp_sum = (u16)a + 0x60;
        a = (u8)temp_sum;
        if (temp_sum > 0xFF)
        {
            carry_set_by_daa_adjustment = true;
        }
    }

    set_a(a);

    set_s_flag(this->a);
    set_z_flag(this->a);
    set_p_flag(this->a);

    u8 final_flags = get_f();

    if (aux_carry_set_by_daa_adjustment)
    {
        final_flags |= A_FLAG;
    }
    else
    {
        final_flags &= ~A_FLAG;
    }

    if (carry_set_by_daa_adjustment)
    {
        final_flags |= C_FLAG;
    }
    else
    {
        if (original_carry)
        {
            final_flags |= C_FLAG;
        }
        else
        {
            final_flags &= ~C_FLAG;
        }
    }
    set_f(final_flags);

    // 4 cycles
}

// loads memory into a specified address into 16 bit address HL
void cpu::lhld()
{
    u8 lower = fetch();
    this->cycles += 3;

    u8 upper = fetch();
    this->cycles += 3;

    u16 address = (static_cast<u16>(upper) << 8) | lower;

    set_l(ram->read(address));
    this->cycles += 3;

    set_h(ram->read(address + 1));
    this->cycles += 3;

    // 16 cycles
}
// push value from a 16 bit register onto stack

// flips every bit in the accumlator
void cpu::cma()
{
    set_a(~get_a());

    // 4 cycles
}

// stores a in the address specified by the next 2 bytes
void cpu::sta()
{
    u8 lower = fetch();
    this->cycles += 3;

    u8 upper = fetch();
    this->cycles += 3;

    u16 address = (static_cast<u16>(upper) << 8) | lower;

    ram->write(address, get_a());
    this->cycles += 3;

    // 13 cycles
}

// sets carry flag to true
void cpu::stc()
{
    set_c_flag(true);

    // 4 cycles
}

// flips the carry bit
void cpu::cmc()
{
    u8 flags = get_f();
    flags ^= 0x01;
    set_f(flags);

    // 4 cycles
}

// gets the address from rom, and sets a to the data held at that memory address
void cpu::lda()
{
    u8 address_low = fetch();
    this->cycles += 3;

    u8 address_high = fetch();
    this->cycles += 3;

    u16 address = (static_cast<u16>(address_high << 8)) | address_low;

    u8 data = ram->read(address);
    this->cycles += 3;

    set_a(data);

    // 13 cycles
}

// copy reg b onto reg a
void cpu::mov(u8 &reg_a, u8 &reg_b)
{
    reg_a = reg_b;
    this->cycles += 1;
}

// copy data from memory onto reg
void cpu::mov_rm(u8 &reg)
{
    u16 address = cpu::get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;
    reg = data;
}
// copy data from reg onto memory
void cpu::mov_mr(u8 &reg)
{
    u16 address = cpu::get_hl();
    ram->write(address, reg);
    this->cycles += 3;
}

/// halts the cpu execution
void cpu::halt()
{
    this->is_halted = true;
    this->cycles += 3;
}

// add to reg a with the specified reg
void cpu::add(u8 &reg)
{
    u8 old_a = get_a();
    u16 result = static_cast<u16>(this->a) + static_cast<u16>(reg);
    u8 a = static_cast<u8>(result);
    set_a(a);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(old_a, a, false);
    // 4 cycles
}

// add memory data to reg a
void cpu::add_m()
{
    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 old_a = get_a();
    u16 result = static_cast<u16>(this->a) + static_cast<u16>(data);
    u8 a = static_cast<u8>(result);
    set_a(a);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(old_a, a, false);
    // 4 cycles
}

// add with carry
void cpu::adc(u8 &reg)
{
    u8 old_a = get_a();
    u16 result = static_cast<u16>(this->a) + static_cast<u16>(reg);

    u8 f = get_f();
    u8 carry = f & C_FLAG;
    if (carry != 0)
    {
        result++;
    }

    u8 a = static_cast<u8>(result);
    set_a(a);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(old_a, a, false);
}

// add specified memory with carry
void cpu::adc_m()
{
    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 old_a = get_a();
    u16 result = static_cast<u16>(this->a) + static_cast<u16>(data);

    u8 f = get_f();
    u8 carry = f & C_FLAG;
    if (carry != 0)
    {
        result++;
    }

    u8 a = static_cast<u8>(result);
    set_a(a);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(old_a, a, false);
    // 4 cycles
}

// sub a from the specified memory
void cpu::sub(u8 &reg)
{
    u8 a = get_a();
    u8 result = a - reg;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(a < reg);
    set_a_flag_sub_type(a, result, false);

    // 4 cycles
}

// subtract memory data from reg A
void cpu::sub_m()
{
    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a - data;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(a < data);
    set_a_flag_sub_type(a, result, false);

    // 7 cycles
}

// subtract memory data from reg a with borrow
void cpu::sbb(u8 &reg)
{
    u8 a = get_a();

    // borrow in this case is just the carry flag
    bool borrow = get_f() & 0b00000001 != 0;
    u8 result = a - reg - (borrow ? 1 : 0);

    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag((a < reg) || (a - reg < (borrow ? 1 : 0)));
    set_a_flag_sub_type(a, result, false);

    // 4 cycles
}

void cpu::sbb_m()
{
    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 a = get_a();

    // borrow in this case is just the carry flag
    bool borrow = get_f() & 0b00000001 != 0;
    u8 result = a - data - (borrow ? 1 : 0);

    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag((a < data) || (a - data < (borrow ? 1 : 0)));
    set_a_flag_sub_type(a, result, false);

    // 7 cycles
}

// bitwise and reg A and the specified register
void cpu::ana(u8 &reg)
{
    u8 a = get_a();
    u8 result = a & reg;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(((a | reg) & 0x08) != 0);
    // 4 cycles
}

void cpu::ana_m()
{
    u8 a = get_a();

    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 result = a & data;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(((a | data) & 0x08) != 0);

    // 7 cycles
}

// performs XOR on reg A and the specified register
void cpu::xra(u8 &reg)
{
    u8 a = get_a();
    u8 result = a ^ reg;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(false);
    // 4 cycles
}

void cpu::xra_m()
{
    u8 a = get_a();

    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 result = a ^ data;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(false);
    // 4 cycles
}

// peforms an or operation on reg A and the specified register
void cpu::ora(u8 &reg)
{
    u8 a = get_a();
    u8 result = a | reg;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(false);
    // 4 cycles
}

void cpu::ora_m()
{
    u8 a = get_a();

    u16 address = get_hl();
    u8 data = ram->read(address);
    this->cycles += 3;

    u8 result = a | data;
    set_a(result);

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(false);
    set_a_flag_boolean(false);
    // 4 cycles
}

// compare the value of reg a and the specified register
void cpu::cmp(u8 &reg)
{
    u8 a = get_a();
    u8 result = a - reg;

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(a < reg);
    set_a_flag_sub_type(a, reg, false);

    // 4 cycles
}

void cpu::cmp_m()
{
    u8 a = get_a();

    u16 address = get_hl();
    u8 data = ram->read(address);

    u8 result = a - data;

    set_z_flag(result);
    set_s_flag(result);
    set_p_flag(result);
    set_c_flag(a < data);
    set_a_flag_sub_type(a, data, false);

    // 4 cycles
}

// if the zero flag is set, two stack values are popped and pushed onto pc
void cpu::rnz()
{
    u8 f = get_f();
    bool zero = (f & 0x40) != 0;

    if (!zero)
    {
        u16 pc_value = pop_get_value();
        this->pc = pc_value;
    }
    this->cycles += 1;
    // 11 cycles if zero is true, 5 cycles if zero is false
}

// if the zero flag is true, then the address found in the following two bytes are pushed onto the pc
void cpu::jnz()
{
    u8 f = get_f();
    bool zero = (f & 0x40) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    if (!zero)
    {
        u16 address = ((static_cast<u16>(upper) << 8)) | lower;
        this->pc = address;
    }
    // 10 cycles
}

// unconditional jump to a new program address
void cpu::jmp()
{
    u8 f = get_f();
    bool zero = (f & 0x40) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u16 address = ((static_cast<u16>(upper) << 8)) | lower;
    this->pc = address;

    // 10 cycles
}

// pushes pc to stack and sets it to the next 2 bytes if the zero flag is true
void cpu::cnz()
{
    u8 f = get_f();
    bool zero = (f & 0x40) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    if (!zero)
    {
        u16 pc = this->pc;
        u8 upper_pc = pc >> 8;
        u8 lower_pc = pc;

        push_value(upper_pc, lower_pc);
        u16 new_pc = ((static_cast<u16>(upper)) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if flag is zero, 11 cycles is not zero
}

// add inteermediate
void cpu::adi()
{
    u8 a = get_a();

    u8 b = fetch();
    this->cycles += 3;

    u8 result = a + b;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);

    // 7 cycles
}

void cpu::rst(int n)
{
    u16 pc = this->pc;
    push_value((pc >> 8), pc);

    pc = 8 * n;
    this->pc = pc;

    // 4 cycles
}

// resets the pc to the top of the stack if the zero flag is set
void cpu::rz()
{
    u8 flags = get_f();
    bool z_set = (flags & 0b01000000) != 0;

    if (z_set)
    {
        u16 new_pc = pop_get_value();
        this->pc = new_pc;
    }
    this->cycles += 1;

    // 11 cycles if true 5 if false
}

// unconditional return
void cpu::ret()
{
    this->pc = pop_get_value();

    // 10 cycles in total, pop function adds 6, function fetch adds 4
}

// jump to the address found in the next 2 bytes of data if the zero flag is set
void cpu::jz()
{
    u8 flags = get_f();
    bool z_set = (flags & 0b01000000) != 0;

    u16 low_byte = fetch();
    this->cycles += 3;
    u16 high_byte = fetch();
    this->cycles += 3;
    u16 address = (high_byte << 8) | low_byte;

    if (z_set)
    {
        this->pc = address;
    }

    // 10 cycles
}

// conditional subreturn, pushes pc onto stack, and sets new value otherwise skip
void cpu::cz()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool z_set = (flags & 0b01000000) != 0;

    if (z_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if z flag is set, 11 if not
}

// saves the pc into the stack and jumps the next instruction
void cpu::call()
{
    push_value((this->pc >> 8), this->pc);

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
    this->pc = new_pc;
    // 17 cycles
}

// add intermediate and carry to accumulator
void cpu::aci()
{
    int carry = get_f() & 0x01;

    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a + data + carry;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);

    // 7 cycles
}

// if the zero flag is not set pop from the stack and set pc to new value
void cpu::rnc()
{
    u8 f = get_f();
    bool zero = (f & 0x01) != 0;

    if (!zero)
    {
        u16 pc_value = pop_get_value();
        this->pc = pc_value;
    }
    this->cycles += 1;
    // 11 cycles if zero is true, 5 cycles if zero is false
}

// jump if zero flag is set
void cpu::jnc()
{
    u8 f = get_f();
    bool zero = (f & 0x01) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    if (!zero)
    {
        u16 address = ((static_cast<u16>(upper) << 8)) | lower;
        this->pc = address;
    }
}

// output accumulator to a port address with the accumator as the data
void cpu::out()
{
    u8 lower = fetch();
    this->cycles += 3;

    u8 upper = fetch();
    this->cycles += 3;

    printf("Data has been requested to be exported");

    // 10 cycles
}

void cpu::cnc()
{
    u8 f = get_f();
    bool carry = (f & 0x01) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    if (!carry)
    {
        u16 pc = this->pc;
        u8 upper_pc = pc >> 8;
        u8 lower_pc = pc;

        push_value(upper_pc, lower_pc);
        u16 new_pc = ((static_cast<u16>(upper)) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if flag is zero, 11 cycles is not zero
}
// subtract intermediate value from the accumulator
void cpu::sui()
{
    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a - data;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_sub_type(a, result, false);

    // 7 cycles
}

void cpu::rc()
{
    u8 flags = get_f();
    bool carry_set = (flags & 0x01) != 0;

    if (carry_set)
    {
        u16 new_pc = pop_get_value();
        this->pc = new_pc;
    }
    this->cycles += 1;

    // 11 cycles if true 5 if false
}

// jumps if carry flag is set
void cpu::jc()
{
    u8 flags = get_f();
    bool z_set = (flags & 0x01) != 0;

    u16 low_byte = fetch();
    this->cycles += 3;
    u16 high_byte = fetch();
    this->cycles += 3;
    u16 address = (high_byte << 8) | low_byte;

    if (z_set)
    {
        this->pc = address;
    }

    // 10 cycles
}

// reads an input
void cpu::in()
{
    u8 half_address = fetch();
    this->cycles += 3;

    u16 address = (static_cast<u16>(half_address) << 8) | half_address;

    printf("An input has been requested");
}

// call if the carry flag is set
void cpu::cc()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool c_set = (flags & 0x01) != 0;

    if (c_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if z flag is set, 11 if not
}

void cpu::sbi()
{
    int borrow = get_f() & 0x01;

    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a - data - borrow;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);

    // 7 cycles
}

void cpu::rpo()
{
    u8 f = get_f();
    bool parity = (f & 0x04) != 0;

    if (!parity)
    {
        u16 pc_value = pop_get_value();
        this->pc = pc_value;
    }
    this->cycles += 1;
    // 11 cycles if zero is true, 5 cycles if zero is false
}

void cpu::jpo()
{
    u8 f = get_f();
    bool parity = (f & 0x01) != 0;

    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    if (!parity)
    {
        u16 address = ((static_cast<u16>(upper) << 8)) | lower;
        this->pc = address;
    }
}

void cpu::xthl()
{
    u16 stack = pop_get_value();
    u8 upper = stack >> 8;
    u8 lower = stack;

    push_value(lower, upper);

    this->cycles += 1;

    // 18 cycles
}

void cpu::cpo()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool c_set = (flags & 0x04) != 0;

    if (!c_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if z flag is set, 11 if not
}

void cpu::ani()
{
    u8 a = get_a();

    u8 data = fetch();
    this->cycles += 3;

    u8 result = a & data;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);
}

void cpu::rpe()
{
    u8 flags = get_f();
    bool p_set = (flags & 0x04) != 0;

    if (p_set)
    {
        u16 new_pc = pop_get_value();
        this->pc = new_pc;
    }
    this->cycles += 1;
}

void cpu::pchl()
{
    u16 hl = get_hl();
    this->pc = hl;
    this->cycles += 1;
}

void cpu::jpe()
{
    u8 flags = get_f();
    bool p_set = (flags & 0x04) != 0;

    u16 low_byte = fetch();
    this->cycles += 3;
    u16 high_byte = fetch();
    this->cycles += 3;
    u16 address = (high_byte << 8) | low_byte;

    if (p_set)
    {
        this->pc = address;
    }
}

void cpu::xchg()
{
    u16 de = get_de();
    set_de(get_hl());
    set_hl(de);
}
void cpu::cpe()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool c_set = (flags & 0x04) != 0;

    if (c_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if z flag is set, 11 if not
}

void cpu::xri()
{
    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a ^ data;

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);
}

void cpu::rp()
{
    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    if (!s_set)
    {
        u16 new_pc = pop_get_value();
        this->pc = new_pc;
    }
    this->cycles += 1;
}

void cpu::jp()
{
    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    u16 low_byte = fetch();
    this->cycles += 3;
    u16 high_byte = fetch();
    this->cycles += 3;
    u16 address = (high_byte << 8) | low_byte;

    if (!s_set)
    {
        this->pc = address;
    }
}

void cpu::di()
{
    this->interrupts = false;
}

void cpu::cp()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    if (!s_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }

    // 17 cycles if z flag is set, 11 if not
}

void cpu::ori()
{
    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u8 result = a | data;
    set_a(result);

    set_z_flag(this->a);
    set_s_flag(this->a);
    set_p_flag(this->a);
    set_c_flag(result > 0xFF);
    set_a_flag_add_type(a, result, false);
}

void cpu::rm()
{
    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    if (s_set)
    {
        u16 new_pc = pop_get_value();
        this->pc = new_pc;
    }
    this->cycles += 1;
}

void cpu::sphl()
{
    set_sp(get_hl());
    this->cycles += 1;
}

void cpu::jm()
{
    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    u16 low_byte = fetch();
    this->cycles += 3;
    u16 high_byte = fetch();
    this->cycles += 3;
    u16 address = (high_byte << 8) | low_byte;

    if (s_set)
    {
        this->pc = address;
    }
}

void cpu::ei()
{
    this->interrupts = true;
}

void cpu::cm()
{
    u8 lower = fetch();
    this->cycles += 3;
    u8 upper = fetch();
    this->cycles += 3;

    u8 flags = get_f();
    bool s_set = (flags & 0x80) != 0;

    if (s_set)
    {
        u16 old_pc = this->pc;
        push_value((old_pc >> 8), old_pc);

        u16 new_pc = (static_cast<u16>(upper) << 8) | lower;
        this->pc = new_pc;
    }
    else
    {
        this->cycles += 1;
    }
}

void cpu::cpi()
{
    u8 data = fetch();
    this->cycles += 3;

    u8 a = get_a();
    u16 res_16 = static_cast<u16>(a) - data;

    u8 res_8 = static_cast<u8>(res_16);

    u8 flags = 0;

    // set z flag
    if (res_8 == 0)
    {
        flags |= 0x40;
    }
    // set s flag
    if (res_8 & 0x80)
    {
        flags |= 0x80;
    }

    // set c flag
    if ((res_16 & 0x100) == 0x100)
    {
        flags |= 0x01;
    }

    // set p flag
    int parity_bits = 0;
    while (res_8) {
        parity_bits += res_8 & 1;
        res_8 >>= 1;
    }
    if (parity_bits % 2 == 0)
    {
        flags |= 0x04;
    }

    // set A flag
    if (((a & 0x0F) - (data & 0x0F)) & 0x10)
    {
        flags |= 0x10;
    }

    set_f(flags);
}

// push reg pair onto stack
void cpu::push(u8 &upper_reg, u8 &lower_reg)
{
    this->sp--;
    ram->write(this->sp, upper_reg);
    this->sp--;
    ram->write(this->sp, lower_reg);
    this->cycles += 7;

    // 11 cycles
}

// push value pair onto the stack
void cpu::push_value(u8 upper, u8 lower)
{
    this->sp--;
    ram->write(this->sp, upper);
    this->sp--;
    ram->write(this->sp, lower);
    this->cycles += 7;
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

// get the 16 bit value of the stack
u16 cpu::pop_get_value()
{
    u8 lower = ram->read(this->sp);
    this->sp++;
    u8 upper = ram->read(this->sp);
    this->sp++;

    this->cycles += 6;
    u16 value = (static_cast<u16>(upper) << 8) | lower;
    return value;
}