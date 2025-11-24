#include "input.hpp"
#include <cstdio> // Required for printf

bool input::update_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
        {
            bool is_down = (event.type == SDL_EVENT_KEY_DOWN);
            
            switch (event.key.scancode) 
            {
            case SDL_SCANCODE_C:
                coin = is_down;
                break;
            case SDL_SCANCODE_RETURN:
                p1_start = is_down;
                break;
            case SDL_SCANCODE_2:
                p2_start = is_down;
                break;
            case SDL_SCANCODE_SPACE:
                p1_fire = is_down;
                break;
            case SDL_SCANCODE_LEFT:
                p1_left = is_down;
                break;
            case SDL_SCANCODE_RIGHT:
                p1_right = is_down;
                break;

            case SDL_SCANCODE_LSHIFT:
                p2_fire = is_down;
                break;
            case SDL_SCANCODE_A:
                p2_left = is_down;
                break;
            case SDL_SCANCODE_D:
                p2_right = is_down;
                break;

            case SDL_SCANCODE_T:
                tilt = is_down;
                break;
            default:
                printf("Unmapped scancode: %d\n", event.key.scancode);
            }
        }
    }
    return true;
}

u8 input::get_port1()
{
    u8 port1 = 0b00001000;

    if (coin)
    {
        port1 |= 0x01;
    }
    if (p2_start)
    {
        port1 |= 0x02;
    }

    if (p1_start)
    {
        port1 |= 0x04;
    }

    if (p1_fire)
    {
        port1 |= 0x10;
    }

    if (p1_left)
    {
        port1 |= 0x20;
    }

    if (p1_right)
    {
        port1 |= 0x40;
    }

    return port1;
}

u8 input::get_port2()
{
    u8 port2 = 0x00;

    if (dip_switch_3)
    {
        port2 |= 0x01;
    }

    if (dip_switch_5)
    {
        port2 |= 0x02;
    }

    if (tilt)
    {
        port2 |= 0x04;
    }

    if (dip_switch_6)
    {
        port2 |= 0x08;
    }

    if (p2_fire)
    {
        port2 |= 0x10;
    }

    if (p2_left)
    {
        port2 |= 0x20;
    }

    if (p2_right)
    {
        port2 |= 0x40;
    }

    return port2;
}