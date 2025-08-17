#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "C:/Users/Lenovo/Desktop/Coding/c_and_cpp/c/medium_projects/AI_number_detector/load_images.h"

const int screenWidth;
const int screenHeigh;
bool ze_mouse_is_down = false;
bool is_the_mouse_really_down = false;
bool is_left_arrow_button_clicked = false;
bool is_right_arrow_button_clicked = false;
bool is_run_ai_button_clicked = false;
bool is_train_ai_button_clicked = false;
bool is_reset_result_button_clicked = false;
bool is_new_button_clicked = false;
bool is_save_button_clicked = false;
bool is_delete_button_clicked = false;
bool what_boxes_in_the_middle_are_on[36][24];
Vector2 lastMospos;

void setup_game()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    bool ze_mouse_is_down = false;
    bool what_boxes_in_the_middle_are_on[36][24] = {0};
    int number_of_boxes_in_middle = 864;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(120);
    load_images();
}