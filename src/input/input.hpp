#pragma once 
#include "../common.h"
#define SDL_MAIN_HANDLED
extern "C"
{
    #include <SDL3/SDL.h>
}

class input
{
private:

    /*
        port 1
            bit 0: Coin inserted
            bit 1: Player 2 start
            bit 2: Player 1 start
            bit 3: Always 1
            bit 4: Player 1 fire
            bit 5: Player 1 left
            bit 6: Player 1 right
            bit 7: Always 0
    */
    bool coin = false;
    bool p2_start = false;
    bool p1_start = false;

    bool p1_fire = false;
    bool p1_left = false;
    bool p1_right = false;

    /*
        port 2
            bit 0: DIP Switch 3 (Lives: 3/4/5/6)
            bit 1: DIP Switch 5 (Bonus Life: 1000/1500)
            bit 2: Tilt Switch
            bit 3: DIP Switch 6 (Coinage)
            bit 4: Player 2 Fire Button
            bit 5: Player 2 Left Movement
            bit 6: Player 2 Right Movement
            bit 7: Always 0
    */
    
    bool dip_switch_3 = false;
    bool dip_switch_5 = false;
    bool tilt_switch = false;
    bool dip_switch_6 = false;
    bool p2_fire = false;
    bool p2_left = false;
    bool p2_right = false;
    bool tilt = false;
public:

    bool update_input();
    u8 get_port1();
    u8 get_port2();

    input(/* args */);
    ~input();
};

input::input(/* args */)
{
}

input::~input()
{
}
