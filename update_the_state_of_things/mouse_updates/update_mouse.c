#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "update_mouse.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\game_setup\game_setup.h"


void update_mouse_details()
{
    lastMospos = mousePos;
    mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ze_mouse_is_down = true;
    }
    else
    {
        ze_mouse_is_down = false;
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        is_the_mouse_really_down = true;
    }
    else
    {
        is_the_mouse_really_down = false;
    }
}