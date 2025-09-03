#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "../load_images.h"
#include <string.h>
#include "../file_management/update_the_files.h"

//screen
const int screenWidth;
const int screenHeigh;
float scale;

//buttons
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

Vector2 mousePos;
Vector2 lastMospos;

//file related
FilePathList files;
char **drawing_files = NULL;
int drawing_files_lenght = 0;
char what_files_to_show[4][30] = {" " , " " , " " , " "};
bool *is_which_file_is_selected_clicked = NULL;
int top_file_n = 0;
int temp_len = 0;

//font
Font display_font;

//drawing
bool clear_the_screen = false;

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
    scale = 1.0f;
    InitWindow(1600*scale, 900*scale, "AI number detector, 0-9");
    SetTargetFPS(60);
    load_images();
    //detects existing training files
    files = LoadDirectoryFiles("training_data/");
    temp_len = files.count;
    //file names
    drawing_files = malloc(temp_len * sizeof(char*));
    //actual files
    for (int i = 0; i < files.count; i++) 
    {
        //file names
        drawing_files[i] = malloc(100);
        snprintf(drawing_files[i], 100, "%s", files.paths[i]);
        strcpy(drawing_files[i], drawing_files[i] + 15);

    }
    is_which_file_is_selected_clicked = malloc(temp_len * sizeof(bool));
    for (int i = 0; i < temp_len; i++)
    {
        //make file selections on the side
        is_which_file_is_selected_clicked[i] = malloc(sizeof(bool));
        is_which_file_is_selected_clicked[i] = 0;
        printf("%s\n", drawing_files[i]);
    }
    //font
    display_font = LoadFontEx("UI_elements//arial.ttf" , 64 , 0 , 250);
    
}