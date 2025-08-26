#include "../common.h"
#include "memory.hpp"


// flags: bits 5 and 3 are always 0, bit 1 is always 1
#define S_FLAG 1000_0010;
#define Z_FLAG 0100_0010;
#define A_FLAG 0001_0010;
#define P_FLAG 0000_0110;
#define C_FLAG 0000_0011;

class cpu
{

private:
    u8 a = 0;
    u8 b = 0;
    u8 c = 0;
    u8 d = 0;
    u8 e = 0; 
    u8 h = 0;
    u8 l = 0;
    u8 f = 0;

    u16 sp = 0;
    u16 pc = 0;

    u8 input;
    u8 output;

    u64 cycles = 0;
    memory* ram;

public:
    cpu(memory* mem); 
    ~cpu();

    // get reg values
    u8 get_a();
    u8 get_b();
    u8 get_c();
    u8 get_d();
    u8 get_e();
    u8 get_h();
    u8 get_l();
    u8 get_f();

    // set reg values
    void set_a(u8 data);
    void set_b(u8 data);
    void set_c(u8 data);
    void set_d(u8 data);
    void set_e(u8 data);
    void set_h(u8 data);
    void set_l(u8 data);
    void set_f(u8 data);


    // 16 bit regs
    u16 get_bc();
    u16 get_de();
    u16 get_hl();

    void set_bc(u16 data);
    void set_de(u16 data);
    void set_hl(u16 data);

    // input output
    u8 get_input();
    u8 get_output();

    void set_input();
    void set_output();

    // stack

    void push(u16 data);
    u16 pop();

    // fetch - execute
    u8 fetch();
    void execute(u8 instruction);

    // opcodes
    void nop();
    void lxi(u8 &high_byte, u8 &low_byte);
    void stax(u8 &high_byte, u8 &low_byte);

    

};

cpu::cpu(memory* mem) : ram(mem)
{

}

cpu::~cpu()
{
}
