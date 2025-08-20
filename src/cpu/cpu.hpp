#include "../common.h"s


// flags: bits 5 and 3 are always 0, bit 1 is always 1
#define S_FLAG 1000_0010;
#define Z_FLAG 0100_0010;
#define A_FLAG 0001_0010;
#define P_FLAG 0000_0110;
#define C_FLAG 0000_0011;

class cpu
{

private:
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8 e; 
    u8 h;
    u8 l;
    u8 f;

    u16 sp;
    u16 pc;

    u8 input;
    u8 output;
public:
    cpu(/* args */);
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
    u8 set_a();
    u8 set_b();
    u8 set_c();
    u8 set_d();
    u8 set_e();
    u8 set_h();
    u8 set_l();
    u8 set_f();


    // 16 bit regs
    u16 get_bc();
    u16 get_de();
    u16 get_hl();

    u16 set_bc();
    u16 set_de();
    u16 set_hl();

    // input output
    u8 get_input();
    u8 get_output();

    u8 set_input();
    u8 set_output();
};

cpu::cpu(/* args */)
{
}

cpu::~cpu()
{
}
