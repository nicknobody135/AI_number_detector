#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\game_setup\game_setup.h"

int which_colum_counter = 0;
int which_row_counter = 0;

void update_drawing()
{
    if (is_the_mouse_really_down == true && mousePos.x > 596 && mousePos.x < 1004 && mousePos.y > 238 && mousePos.y < 850)
    {
        for (which_row_counter = 0; which_row_counter < 36; which_row_counter ++)
        {
            for (which_colum_counter = 0; which_colum_counter < 36; which_colum_counter ++)
            {
                mousePos = GetMousePosition();
                if (mousePos.y > (238 + (which_row_counter * 17) -10) && mousePos.y < (238 + (which_row_counter * 17)+17) + 10)
                {
                    if (mousePos.x > (596 + (which_colum_counter * 17) - 10) && mousePos.x < (596 + (which_colum_counter * 17)+17) + 10)
                    {
                        what_boxes_in_the_middle_are_on[which_row_counter][which_colum_counter] = true;
                    }
                }
            }
        }
        which_colum_counter = 0;
        which_row_counter = 0;
    }
}