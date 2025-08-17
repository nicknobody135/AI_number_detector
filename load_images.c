#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "load_images.h"

Image temporary;
Texture2D heading;
Texture2D background_for_the_boxes_to_draw_on;
Texture2D choose_files_drop_down;
Texture2D choose_files_label;
Texture2D draw_a_number_label;
Texture2D Horizontal_line;
Texture2D Vertical_line;
Texture2D What_is_the_name_of_the_file;

Texture2D left_arrow_button_off;
Texture2D right_arrow_button_off;
Texture2D run_ai_button_off;
Texture2D train_ai_button_off;
Texture2D delete_button_off;
Texture2D new_button_off;
Texture2D save_button_off;
Texture2D reset_result_off;

Texture2D left_arrow_button_on;
Texture2D right_arrow_button_on;
Texture2D run_ai_button_on;
Texture2D train_ai_button_on;
Texture2D delete_button_on;
Texture2D new_button_on;
Texture2D save_button_on;
Texture2D reset_result_on;

void load_images()
{
        //stand still UI
        Image temporary = LoadImage("UI_elements//Button.png");
        heading = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//boxes_to_draw_on.png");
        background_for_the_boxes_to_draw_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Choose_files_drop_down.png");
        choose_files_drop_down = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//ChooseFiles.png");
        choose_files_label = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Draw_a_number.png");
        draw_a_number_label = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//H_line.png");
        Horizontal_line = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//v_line.png");
        Vertical_line = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Current_file_name.png");
        What_is_the_name_of_the_file = LoadTextureFromImage(temporary);

        //Button off UI
        temporary = LoadImage("UI_elements//Button_off//arrow_left.png");
        left_arrow_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//arrow_right.png");
        right_arrow_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Run_ai.png");
        run_ai_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//reset_result.png");
        reset_result_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Train_ai.png");
        train_ai_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Delete.png");
        delete_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//New.png");
        new_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Save.png");
        save_button_off = LoadTextureFromImage(temporary);

        //Button on UI
        temporary = LoadImage("UI_elements//Button_on//arrow_left.png");
        left_arrow_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//arrow_right.png");
        right_arrow_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Run_ai.png");
        run_ai_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//reset_result.png");
        reset_result_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Train_ai.png");
        train_ai_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Delete.png");
        delete_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//New.png");
        new_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Save.png");
        save_button_on = LoadTextureFromImage(temporary);

}