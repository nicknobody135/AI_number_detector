#include "C:\raylib\raylib\src\raylib.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\update_the_state_of_things\update_the_state_of_things.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\update_the_state_of_things\mouse_updates\update_mouse.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\game_setup\game_setup.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\clock\clock.h"
#include <time.h>
#include <stdio.h>

bool all_buttons_of_or_on = false;
clock_t time_the_button_was_clicked = 0;
clock_t time_right_now = 0;
int time_game_has_been_running_for;

void update_the_buttons()
{
    if(ze_mouse_is_down == true)
    {
        all_buttons_of_or_on = true;
        //saves the time the button was clicked so the button can turn orange for a bit
        time_the_button_was_clicked = clock();

        //arrow_left
        if (mousePos.x > 122 && mousePos.x < 310 && mousePos.y > 575 && mousePos.y < 666)
        {
            is_left_arrow_button_clicked = true;
            printf("left arrow click\n");
        }
        
        //arrow_right
        else if (mousePos.x > 358 && mousePos.x < 546 && mousePos.y > 575 && mousePos.y < 666)
        {
            is_right_arrow_button_clicked = true;
            printf("right arrow click\n");
        }

        //delete_button
        else if (mousePos.x > 122 && mousePos.x < 243 && mousePos.y > 164 && mousePos.y < 255)
        {
            is_delete_button_clicked = true;
            printf("delete button clicked\n");
        }

        //save_button
        else if (mousePos.x > 273 && mousePos.x < 394 && mousePos.y > 164 && mousePos.y < 255)
        {
            is_save_button_clicked = true;
            printf("save button clicked\n");
        }

        //new_button
        else if (mousePos.x > 425 && mousePos.x < 546 && mousePos.y > 164 && mousePos.y < 255)
        {
            is_new_button_clicked = true;
            printf("new button clicked\n");
        }

        //run_ai_button
        else if (mousePos.x > 1088 && mousePos.x < 1512 && mousePos.y > 169 && mousePos.y < 260)
        {
            is_run_ai_button_clicked = true;
            printf("run_ai_button button clicked\n");
        }

        //reset_result_button
        else if (mousePos.x > 1088 && mousePos.x < 1512 && mousePos.y > 453 && mousePos.y < 544)
        {
            is_reset_result_button_clicked = true;
            for (int a = 0; a < 36; a++)
            {
                for (int b = 0; b < 24; b++)
                {
                    what_boxes_in_the_middle_are_on[a][b] = false;
                }
            }
            printf("reset_result button clicked\n");
        }

        //train_ai_button
        else if (mousePos.x > 1088 && mousePos.x < 1512 && mousePos.y > 591 && mousePos.y < 682)
        {
            is_train_ai_button_clicked = true;
            printf("train_ai_button clicked\n");
        }
    }

    else
    {
        time_right_now = clock();
        double time_elapsed = (double)(time_right_now - time_the_button_was_clicked) / CLOCKS_PER_SEC;
        if (time_elapsed <= 0.3)
        {
            all_buttons_of_or_on = true;
        }
        else
        {
            all_buttons_of_or_on = false;

            //sets all buttons to off:
            is_left_arrow_button_clicked = false;
            is_right_arrow_button_clicked = false;
            is_delete_button_clicked = false;
            is_new_button_clicked = false;
            is_save_button_clicked = false;
            is_run_ai_button_clicked = false;
            is_reset_result_button_clicked = false;
            is_train_ai_button_clicked = false;
        }
        
    }
}