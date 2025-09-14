#ifndef SETUP_GAME
#define SETUP_GAME
#include "C:\raylib\raylib\src\raylib.h"
#include "../load_images.h"
#include <time.h>
#include <string.h>

//screen data
extern const int screenWidth;
extern const int screenHeigh;
extern float scale;

//mouse related variables
extern bool ze_mouse_is_down;
extern bool is_the_mouse_really_down;
extern Vector2 mousePos;
extern Vector2 lastMospos;

//app clock
extern int game_clock;
extern int time_game_has_been_running_for;

//bools for all the buttons
extern bool is_left_arrow_button_clicked;
extern bool is_right_arrow_button_clicked;
extern bool is_run_ai_button_clicked;
extern bool is_train_ai_button_clicked;
extern bool is_reset_result_button_clicked;
extern bool is_new_button_clicked;
extern bool is_save_button_clicked;
extern bool is_delete_button_clicked;
extern bool is_clear_screen_button_clicked;
extern bool is_file_selector_up_clicked;
extern bool is_file_selector_down_clicked;
extern bool *is_which_file_is_selected_clicked;
extern bool all_buttons_of_or_on;

//time between each button click
extern clock_t time_the_button_was_clicked;
extern clock_t time_right_now;

//drawing
extern bool what_boxes_in_the_middle_are_on[36][24];
extern int number_of_boxes_in_middle;
extern bool clear_the_screen;

//file related
extern FilePathList files;
extern char **drawing_files;
extern int drawing_files_lenght;
extern char what_files_to_show[4][30];
extern int top_file_n;
extern int temp_len;
extern char **contents_of_training_data_files; 
extern int *how_many_drawings_in_each_file;
extern bool **which_drawing_among_the_files_is_the_user_on;

//font
extern Font display_font;
void setup_game();
#endif