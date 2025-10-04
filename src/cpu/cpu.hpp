#include "../common.h"
#include "memory.hpp"


// flags: bits 5 and 3 are always 0, bit 1 is always 1
#define S_FLAG 0b10000010;
#define Z_FLAG 0b01000010;
#define A_FLAG 0b00010010;
#define P_FLAG 0b00000110;
#define C_FLAG 0b00000011;

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

    bool is_halted = false;
    bool interrupts = false;

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
    u16 get_sp();


    void set_bc(u16 data);
    void set_de(u16 data);
    void set_hl(u16 data);
    void set_sp(u16 data);

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

    // set flags
    void set_s_flag(u8 &reg);
    void set_z_flag(u8 &reg);
    void set_a_flag_add_type(u8 val1, u8 val2, bool is_increment);
    void set_a_flag_sub_type(u8 val1, u8 val2, bool is_decrement);
    void set_a_flag_boolean(bool condition);
    void set_p_flag(u8 &reg);
    void set_c_flag(bool condition);

    // get flag

    // opcodes
    void nop();

    void lxi(u8 &high_byte, u8 &low_byte);
    void lxi_sp();

    void stax(u8 &high_byte, u8 &low_byte);

    void inx(u8 &high_byte, u8 &low_byte);
    void inx_sp();

    void inr(u8 &reg);
    void inr_m();

    void dcr(u8 &reg);
    void dcr_m();

    void mvi(u8 &reg);
    void mvi_m();

    void rlc();

    void dad(u8 &upper_a_reg, u8 &lower_a_reg);
    void dad_sp();

    void ldax(u8 &upper_reg, u8 &lower_reg);
    void lda();

    void dcx(u8 &upper_reg, u8 &lower_reg);
    void dcx_sp();

    void rrc();
    void ral();
    void rar();
    void shld();
    void daa();
    void lhld();
    void cma();
    void sta();
    void stc();
    void cmc();
    void lda();

    void mov(u8 &reg_a, u8 &reg_b);
    void mov_rm(u8 &reg);
    void mov_mr(u8 &reg);

    void halt();

    void add(u8 &reg);
    void add_m();

    void adc(u8 &reg);
    void adc_m();

    void sub(u8 &reg);
    void sub_m();

    void sbb(u8 &reg);
    void sbb_m();

    void ana(u8 &reg);
    void ana_m();

    void xra(u8 &reg);
    void xra_m();

    void ora(u8 &reg);
    void ora_m();

    void cmp(u8 &reg);
    void cmp_m();

    void rnz();
    void jnz();
    void jmp();
    void cnz();
    void adi();

    void rst(int n);
    void rz();
    void ret();

    void jz();
    void cz();
    void call();

    void aci();

    void rnc();
    void jnc();
    void out();
    void cnc();
    void sui();
    void rc();
    void jc();
    void in();
    void cc();
    void sbi();

    void rpo();
    void jpo();
    void xthl();
    void cpo();
    void ani();
    void rpe();
    void pchl();
    void jpe();
    void xchg();
    void cpe();
    void xri();

    void rp();
    void jp();
    void di();
    void cp();
    void ori();
    void rm();
    void sphl();
    void jm();
    void ei();
    void cm();
    void cpi();
    
    void push(u8 &upper_reg, u8 &lower_reg);
    void push_value(u8 upper, u8 lower);
    void pop(u8 &upper_reg, u8 &lower_reg);
    u16 pop_get_value();
    


};

cpu::cpu(memory* mem) : ram(mem)
{

}

cpu::~cpu()
{
}
