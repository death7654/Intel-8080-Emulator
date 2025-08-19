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
public:
    cpu(/* args */);
    ~cpu();
};

cpu::cpu(/* args */)
{
}

cpu::~cpu()
{
}
