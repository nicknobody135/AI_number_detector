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
float scale;
Vector2 mousePos;
Vector2 lastMospos;

void setup_game()
{
    InitWindow(1, 1, "Dummy");
    int monitor = GetCurrentMonitor(); // usually 0
    int width = GetMonitorWidth(monitor);
    scale = width/1920.0f;
    CloseWindow();
    printf("%f\n" , scale);
    bool ze_mouse_is_down = false;
    bool what_boxes_in_the_middle_are_on[36][24] = {0};
    int number_of_boxes_in_middle = 864;
    InitWindow(1600*scale, 900*scale, "raylib [core] example - basic window");
    SetTargetFPS(120);
    load_images();
}