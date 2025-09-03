#include "C:\raylib\raylib\src\raylib.h"
#include "../update_the_state_of_things.h"
#include "../mouse_updates/update_mouse.h"
#include "../../game_setup/game_setup.h"
#include "../../clock/clock.h"
#include "../../file_management/update_the_files.h"
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
    if(ze_mouse_is_down == true && time_elapsed > 0.2)
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
            clean_the_screen();
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
            if (top_file_n!= 0)
            {
                top_file_n = top_file_n - 1;
            }
        }

        //file_selector_down
        else if (mousePos.x > 490*scale && mousePos.x < 522*scale && mousePos.y > 483*scale && mousePos.y < 505*scale)
        {
            is_file_selector_down_clicked = true;
            printf("file selector down button clicked\n");
            if (top_file_n+4 != temp_len)
            {
                top_file_n = top_file_n + 1;
            }
        }
    
        //file_selector
        else if (mousePos.x > 145*scale && mousePos.x < 485*scale && mousePos.y > 400*scale && mousePos.y < 513*scale)
        {
            if (mousePos.x > 145*scale && mousePos.x < 485*scale && mousePos.y > 400*scale && mousePos.y < 426*scale)
            {
                if (is_which_file_is_selected_clicked[0+top_file_n] == 1)
                {
                    is_which_file_is_selected_clicked[0+top_file_n] = 0;
                    clean_the_screen();
                }
                
                else if (is_which_file_is_selected_clicked[0+top_file_n] == 0)
                {
                    clean_the_screen();
                    for (int i = 0 ; i < temp_len ; i++)
                    {
                        is_which_file_is_selected_clicked[i] = 0;
                    }
                    is_which_file_is_selected_clicked[0+top_file_n] = 1;
                }
            }
            else if (mousePos.x > 145*scale && mousePos.x < 485*scale && mousePos.y > 429*scale && mousePos.y < 455*scale)
            {
                if (is_which_file_is_selected_clicked[1+top_file_n] == 1)
                {
                    is_which_file_is_selected_clicked[1+top_file_n] = 0;
                    clean_the_screen();
                }
                
                else if (is_which_file_is_selected_clicked[1+top_file_n] == 0)
                {
                    for (int i = 0 ; i < temp_len ; i++)
                    {
                        is_which_file_is_selected_clicked[i] = 0;
                    }
                    is_which_file_is_selected_clicked[1+top_file_n] = 1;
                    clean_the_screen();
                }
            }
            else if (mousePos.x > 145*scale && mousePos.x < 485*scale && mousePos.y > 458*scale && mousePos.y < 484*scale)
            {
                if (is_which_file_is_selected_clicked[2+top_file_n] == 1)
                {
                    is_which_file_is_selected_clicked[2+top_file_n] = 0;
                    clean_the_screen();
                }
                
                else if (is_which_file_is_selected_clicked[2+top_file_n] == 0)
                {
                    for (int i = 0 ; i < temp_len ; i++)
                    {
                        is_which_file_is_selected_clicked[i] = 0;
                    }
                    is_which_file_is_selected_clicked[2+top_file_n] = 1;
                    clean_the_screen();
                }
            }
            else if (mousePos.x > 145*scale && mousePos.x < 485*scale && mousePos.y > 487*scale && mousePos.y < 513*scale)
            {
                if (is_which_file_is_selected_clicked[3+top_file_n] == 1)
                {
                    is_which_file_is_selected_clicked[3+top_file_n] = 0;
                    clean_the_screen();
                }
                
                else if (is_which_file_is_selected_clicked[3+top_file_n] == 0)
                {
                    for (int i = 0 ; i < temp_len ; i++)
                    {
                        is_which_file_is_selected_clicked[i] = 0;
                    }
                    is_which_file_is_selected_clicked[3+top_file_n] = 1;
                    clean_the_screen();
                }
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