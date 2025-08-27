#include "C:\raylib\raylib\src\raylib.h"
#include "../update_the_state_of_things.h"
#include "../mouse_updates/update_mouse.h"
#include "../../game_setup/game_setup.h"
#include "../../clock/clock.h"
#include <time.h>
#include <stdio.h>

bool all_buttons_of_or_on = false;
clock_t time_the_button_was_clicked = 0;
clock_t time_right_now = 0;
int time_game_has_been_running_for;

void update_the_buttons()
{
    time_right_now = clock();
    double time_elapsed = (double)(time_right_now - time_the_button_was_clicked) / CLOCKS_PER_SEC;
    if(ze_mouse_is_down == true && time_elapsed > 0.5)
    {
        
        all_buttons_of_or_on = true;
        //saves the time the button was clicked so the button can turn orange for a bit
        time_the_button_was_clicked = clock();

        //arrow_left
        if (mousePos.x > 122*scale && mousePos.x < 310*scale && mousePos.y > 575*scale && mousePos.y < 666*scale)
        {
            is_left_arrow_button_clicked = true;
            printf("left arrow click\n");
        }
        
        //arrow_right
        else if (mousePos.x > 358*scale && mousePos.x < 546*scale && mousePos.y > 575*scale && mousePos.y < 666*scale)
        {
            is_right_arrow_button_clicked = true;
            printf("right arrow click\n");
        }

        //delete_button
        else if (mousePos.x > 122*scale && mousePos.x < 243*scale && mousePos.y > 164*scale && mousePos.y < 255*scale)
        {
            is_delete_button_clicked = true;
            printf("delete button clicked\n");
        }

        //save_button
        else if (mousePos.x > 273*scale && mousePos.x < 394*scale && mousePos.y > 164*scale && mousePos.y < 255*scale)
        {
            is_save_button_clicked = true;
            printf("save button clicked\n");
        }

        //new_button
        else if (mousePos.x > 425*scale && mousePos.x < 546*scale && mousePos.y > 164*scale && mousePos.y < 255*scale)
        {
            is_new_button_clicked = true;
            printf("new button clicked\n");
        }

        //run_ai_button
        else if (mousePos.x > 1088*scale && mousePos.x < 1512*scale && mousePos.y > 169*scale && mousePos.y < 260*scale)
        {
            is_run_ai_button_clicked = true;
            printf("run_ai_button button clicked\n");
        }

        //reset_result_button
        else if (mousePos.x > 1088*scale && mousePos.x < 1258*scale && mousePos.y > 453*scale && mousePos.y < 544*scale)
        {
            is_reset_result_button_clicked = true;
            printf("reset_result button clicked\n");
        }

        //clear_screen
        else if (mousePos.x > 1342*scale && mousePos.x < 1512*scale && mousePos.y > 453*scale && mousePos.y < 544*scale)
        {
            printf("clear screen button was clicked\n");
            for (int a = 0; a < 36; a++)
            {
                for (int b = 0; b < 24; b++)
                {
                    what_boxes_in_the_middle_are_on[a][b] = false;
                }
            }
            is_clear_screen_button_clicked = true;
        }

        //train_ai_button
        else if (mousePos.x > 1088*scale && mousePos.x < 1512*scale && mousePos.y > 591*scale && mousePos.y < 682*scale)
        {
            is_train_ai_button_clicked = true;
            printf("train_ai_button clicked\n");
        }
        
        //file_selector_up
        else if (mousePos.x > 490*scale && mousePos.x < 522*scale && mousePos.y > 400*scale && mousePos.y < 423*scale)
        {
            is_file_selector_up_clicked = true;
            printf("file selector up button clicked\n");
        }

        //file_selector_down
        else if (mousePos.x > 490*scale && mousePos.x < 522*scale && mousePos.y > 483*scale && mousePos.y < 505*scale)
        {
            is_file_selector_down_clicked = true;
            printf("file selector down button clicked\n");
        }
    
        //file_selector
        else if (mousePos.x > 146*scale && mousePos.x < 479*scale && mousePos.y > 400*scale && mousePos.y < 506*scale)
        {
            if (mousePos.x > 146*scale && mousePos.x < 479*scale && mousePos.y > 400*scale && mousePos.y < 426*scale)
            {
                is_which_file_is_selected_clicked[0] = 1;
                is_which_file_is_selected_clicked[1] = 0;
                is_which_file_is_selected_clicked[2] = 0;
                is_which_file_is_selected_clicked[3] = 0;
                printf("file selector 1 clicked\n");
            }
            else if (mousePos.x > 146*scale && mousePos.x < 479*scale && mousePos.y > 427*scale && mousePos.y < 452*scale)
            {
                is_which_file_is_selected_clicked[0] = 0;
                is_which_file_is_selected_clicked[1] = 1;
                is_which_file_is_selected_clicked[2] = 0;
                is_which_file_is_selected_clicked[3] = 0;
                printf("file selector 2 clicked\n");
            }
            else if (mousePos.x > 146*scale && mousePos.x < 479*scale && mousePos.y > 453*scale && mousePos.y < 479*scale)
            {
                is_which_file_is_selected_clicked[0] = 0;
                is_which_file_is_selected_clicked[1] = 0;
                is_which_file_is_selected_clicked[2] = 1;
                is_which_file_is_selected_clicked[3] = 0;
                printf("file selector 3 clicked\n");
            }
            else if (mousePos.x > 146*scale && mousePos.x < 479*scale && mousePos.y > 480*scale && mousePos.y < 506*scale)
            {
                is_which_file_is_selected_clicked[0] = 0;
                is_which_file_is_selected_clicked[1] = 0;
                is_which_file_is_selected_clicked[2] = 0;
                is_which_file_is_selected_clicked[3] = 1;
                printf("file selector 4 clicked\n");
            }
        }
    }

    else
    {
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
            is_clear_screen_button_clicked = false;
            is_file_selector_down_clicked = false;
            is_file_selector_up_clicked = false;
        }
        
    }
}