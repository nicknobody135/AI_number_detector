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
    {
        ClearBackground(RAYWHITE); //background

        //static UI or labels:
        DrawTexture(background_for_the_boxes_to_draw_on, 596*scale, 238*scale, WHITE);
        DrawTexture(heading, 588*scale, 24*scale, WHITE);
        DrawTexture(choose_files_drop_down , 122*scale, 368*scale, WHITE);
        DrawTexture(choose_files_label , 122*scale , 285*scale , WHITE);
        DrawTexture(draw_a_number_label , 596*scale , 191*scale , WHITE);
        DrawTexture(choose_files_drop_down , 1088*scale , 252*scale , WHITE);
        DrawTexture(choose_files_drop_down , 1088*scale , 674*scale , WHITE);
        DrawTexture(What_is_the_name_of_the_file , 122*scale , 716*scale , WHITE);
        DrawTexture(What_is_the_name_of_the_file , 350*scale , 716*scale , WHITE);

        int cellSize = (int)(17 * scale);
        //Grid of lines in the middle
        while(v_line_counter <= 24)
        {
            DrawTexture(Vertical_line , 596*scale + (v_line_counter*cellSize), 238*scale, BLACK);
            v_line_counter = v_line_counter + 1;
        }
        v_line_counter = 0;

        while(h_line_counter <= 36)
        {
            DrawTexture(Horizontal_line , 596*scale, 238*scale + (h_line_counter*cellSize), BLACK);
            h_line_counter = h_line_counter + 1;
        }
        h_line_counter = 0;

        //buttons off
        DrawTexture(left_arrow_button_off ,122*scale , 575*scale , WHITE);
        DrawTexture(right_arrow_button_off , 358*scale , 575*scale , WHITE);
        DrawTexture(delete_button_off , 122*scale , 164*scale , WHITE);
        DrawTexture(save_button_off , 273*scale , 164*scale , WHITE);
        DrawTexture(new_button_off , 425*scale , 164*scale , WHITE);
        DrawTexture(run_ai_button_off , 1088*scale , 169*scale , WHITE);
        DrawTexture(reset_result_off , 1088*scale , 453*scale , WHITE);
        DrawTexture(train_ai_button_off , 1088*scale , 591*scale , WHITE);

        //buttons on
        if(all_buttons_of_or_on == true)
        {
            if(is_left_arrow_button_clicked == true)
            {
                DrawTexture(left_arrow_button_on ,122*scale , 575*scale , WHITE);
            }
            else if(is_right_arrow_button_clicked == true)
            {
                DrawTexture(right_arrow_button_on , 358*scale , 575*scale , WHITE);
            }
            else if(is_delete_button_clicked == true)
            {
                DrawTexture(delete_button_on , 122*scale , 164*scale , WHITE);
            }
            else if(is_save_button_clicked == true)
            {
                DrawTexture(save_button_on , 273*scale , 164*scale , WHITE);
            }
            else if(is_new_button_clicked == true)
            {
                DrawTexture(new_button_on , 425*scale , 164*scale , WHITE);
            }
            else if(is_run_ai_button_clicked == true)
            {
                DrawTexture(run_ai_button_on , 1088*scale , 169*scale , WHITE);
            }
            else if(is_reset_result_button_clicked == true)
            {
                DrawTexture(reset_result_on , 1088*scale , 453*scale , WHITE);
            }
            else if(is_train_ai_button_clicked == true)
            {
                DrawTexture(train_ai_button_on , 1088*scale , 591*scale , WHITE);
            }
        }
        
        //render_the_boxes_in_the_middle
        for (int a = 0; a < 36; a++)
        {
            for (int b = 0; b < 24; b++)
            {
                if (what_boxes_in_the_middle_are_on[a][b] == true)
                {
                    DrawRectangle((596*scale) + ((17*scale) * b), (238*scale) + ((17*scale) * a), (17*scale), (17*scale), BLACK);
                }
            }
        }
    }
}