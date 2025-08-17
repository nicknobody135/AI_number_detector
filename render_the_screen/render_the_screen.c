#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\game_setup\game_setup.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\clock\clock.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\update_the_state_of_things\button_management\update_buttons.h"

int h_line_counter = 0;
int v_line_counter = 0;


void render_the_screen()
{
    ClearBackground(RAYWHITE); //background

    //static UI or labels:
    DrawTexture(background_for_the_boxes_to_draw_on, 596, 238, WHITE);
    DrawTexture(heading, 588, 24, WHITE);
    DrawTexture(choose_files_drop_down , 122 , 368 , WHITE);
    DrawTexture(choose_files_label , 122 , 285 , WHITE);
    DrawTexture(draw_a_number_label , 596 , 191 , WHITE);
    DrawTexture(choose_files_drop_down , 1088 , 252 , WHITE);
    DrawTexture(choose_files_drop_down , 1088 , 674 , WHITE);
    DrawTexture(What_is_the_name_of_the_file , 122 , 716 , WHITE);
    DrawTexture(What_is_the_name_of_the_file , 350 , 716 , WHITE);

    //Grid of lines in the middle
    while(v_line_counter <= 24)
    {
        DrawTexture(Vertical_line , 596 + (v_line_counter*17), 238 , BLACK);
        v_line_counter = v_line_counter + 1;
    }
    v_line_counter = 0;

    while(h_line_counter <= 36)
    {
        DrawTexture(Horizontal_line , 596 , 238 + (17*h_line_counter) , BLACK);
        h_line_counter = h_line_counter + 1;
    }
    h_line_counter = 0;

    //buttons off
    DrawTexture(left_arrow_button_off ,122 , 575 , WHITE);
    DrawTexture(right_arrow_button_off , 358 , 575 , WHITE);
    DrawTexture(delete_button_off , 122 , 164 , WHITE);
    DrawTexture(save_button_off , 273 , 164 , WHITE);
    DrawTexture(new_button_off , 425 , 164 , WHITE);
    DrawTexture(run_ai_button_off , 1088 , 169 , WHITE);
    DrawTexture(reset_result_off , 1088 , 453 , WHITE);
    DrawTexture(train_ai_button_off , 1088 , 591 , WHITE);

    //buttons on
    if(all_buttons_of_or_on == true)
    {
        if(is_left_arrow_button_clicked == true)
        {
            DrawTexture(left_arrow_button_on ,122 , 575 , WHITE);
        }
        else if(is_right_arrow_button_clicked == true)
        {
            DrawTexture(right_arrow_button_on , 358 , 575 , WHITE);
        }
        else if(is_delete_button_clicked == true)
        {
            DrawTexture(delete_button_on , 122 , 164 , WHITE);
        }
        else if(is_save_button_clicked == true)
        {
            DrawTexture(save_button_on , 273 , 164 , WHITE);
        }
        else if(is_new_button_clicked == true)
        {
            DrawTexture(new_button_on , 425 , 164 , WHITE);
        }
        else if(is_run_ai_button_clicked == true)
        {
            DrawTexture(run_ai_button_on , 1088 , 169 , WHITE);
        }
        else if(is_reset_result_button_clicked == true)
        {
            DrawTexture(reset_result_on , 1088 , 453 , WHITE);
        }
        else if(is_train_ai_button_clicked == true)
        {
            DrawTexture(train_ai_button_on , 1088 , 591 , WHITE);
        }
    }
    
    //render_the_boxes_in_the_middle
    for (int a = 0; a < 36; a++)
    {
        for (int b = 0; b < 24; b++)
        {
            if (what_boxes_in_the_middle_are_on[a][b] == true)
            {
                DrawRectangle(596 + (17 * b), 238 + (17 * a), 17, 17, BLACK);
            }
        }
    }
}