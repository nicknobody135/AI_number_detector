#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "update_the_state_of_things.h"
#include "mouse_updates\update_mouse.h"
#include "button_management\update_buttons.h"


void update_the_state_of_things()
{
    update_mouse_details();
    update_the_buttons();
}