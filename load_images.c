#include "C:\raylib\raylib\src\raylib.h"
#include "game_setup\game_setup.h"
#include "stdlib.h"
#include "stdio.h"
#include "load_images.h"

Image temporary;
Texture2D heading;
Texture2D background_for_the_boxes_to_draw_on;
Texture2D drop_down_box;
Texture2D choose_files_drop_down_box;
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
Texture2D clear_drawing_off;
Texture2D file_selector_up_off;
Texture2D file_selector_down_off;

Texture2D left_arrow_button_on;
Texture2D right_arrow_button_on;
Texture2D run_ai_button_on;
Texture2D train_ai_button_on;
Texture2D delete_button_on;
Texture2D new_button_on;
Texture2D save_button_on;
Texture2D reset_result_on;
Texture2D clear_drawing_on;
Texture2D file_selector_up_on;
Texture2D file_selector_down_on;

void load_images()
{
        //stand still UI
        Image temporary = LoadImage("UI_elements//Button.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        heading = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//boxes_to_draw_on.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        background_for_the_boxes_to_draw_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Choose_files_drop_down.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        drop_down_box = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//ChooseFiles.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        choose_files_label = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Draw_a_number.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        draw_a_number_label = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//H_line.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height);
        Horizontal_line = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//v_line.png");
        ImageResize(&temporary, temporary.width, temporary.height * scale);
        Vertical_line = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Current_file_name.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        What_is_the_name_of_the_file = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//real_choose_files_dropdown.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        choose_files_drop_down_box = LoadTextureFromImage(temporary);


        //Button off UI
        temporary = LoadImage("UI_elements//Button_off//arrow_left.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        left_arrow_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//arrow_right.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        right_arrow_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Run_ai.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        run_ai_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//reset_result.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        reset_result_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Train_ai.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        train_ai_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Delete.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        delete_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//New.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        new_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Save.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        save_button_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//Clear_drawing.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        clear_drawing_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//file_selector_down.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        file_selector_down_off = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_off//file_selector_up.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        file_selector_up_off = LoadTextureFromImage(temporary);

        //Button on UI
        temporary = LoadImage("UI_elements//Button_on//arrow_left.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        left_arrow_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//arrow_right.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        right_arrow_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Run_ai.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        run_ai_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//reset_result.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        reset_result_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Train_ai.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        train_ai_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Delete.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        delete_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//New.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        new_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Save.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        save_button_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//Clear_drawing.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        clear_drawing_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//file_selector_down.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        file_selector_down_on = LoadTextureFromImage(temporary);
        temporary = LoadImage("UI_elements//Button_on//file_selector_up.png");
        ImageResize(&temporary, temporary.width * scale, temporary.height * scale);
        file_selector_up_on = LoadTextureFromImage(temporary);
}