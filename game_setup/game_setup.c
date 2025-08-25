#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "C:/Users/Lenovo/Desktop/Coding/c_and_cpp/c/medium_projects/AI_number_detector/load_images.h"
#include <string.h>

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
bool is_clear_screen_button_clicked = false;
bool is_file_selector_up_clicked = false;
bool is_file_selector_down_clicked = false;
bool what_boxes_in_the_middle_are_on[36][24];
float scale;
Vector2 mousePos;
Vector2 lastMospos;
FilePathList files;
char **drawing_files = NULL;
int drawing_files_lenght = 0;
Font display_font;

void setup_game()
{
    //gets the users's montior size
    InitWindow(1, 1, "Dummy");
    int monitor = GetCurrentMonitor();
    int width = GetMonitorWidth(monitor);
    scale = width/1920.0f;
    CloseWindow();
    printf("%f\n" , scale);

    //defines a few variables
    bool ze_mouse_is_down = false;
    bool what_boxes_in_the_middle_are_on[36][24] = {0};
    int number_of_boxes_in_middle = 864;

    //window set up
    InitWindow(1600*scale, 900*scale, "raylib [core] example - basic window");
    SetTargetFPS(60);

    load_images();

    //detects existing training files
    files = LoadDirectoryFiles("training_data/");
    int temp_len = files.count;
    drawing_files = malloc(temp_len * sizeof(char*));
    for (int i = 0; i < files.count; i++) 
    {
        drawing_files[i] = malloc(100);
        snprintf(drawing_files[i], 100, "%s", files.paths[i]);
        strcpy(drawing_files[i], drawing_files[i] + 15);
    }
    for (int i = 0; i < temp_len; i++) 
    {
        printf("%s\n", drawing_files[i]);
    }

    //font
    display_font = LoadFontEx("C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\UI_elements\\arial.ttf" , 64 , 0 , 250);
    
}