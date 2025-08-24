#ifndef SETUP_GAME
#define SETUP_GAME
#include "C:\raylib\raylib\src\raylib.h"
#include "C:/Users/Lenovo/Desktop/Coding/c_and_cpp/c/medium_projects/AI_number_detector/load_images.h"
#include <time.h>

extern const int screenWidth;
extern const int screenHeigh;
extern float scale;

extern bool ze_mouse_is_down;
extern bool is_the_mouse_really_down;
extern Vector2 mousePos;
extern Vector2 lastMospos;

extern int clock_main;

extern bool is_left_arrow_button_clicked;
extern bool is_right_arrow_button_clicked;
extern bool is_run_ai_button_clicked;
extern bool is_train_ai_button_clicked;
extern bool is_reset_result_button_clicked;
extern bool is_new_button_clicked;
extern bool is_save_button_clicked;
extern bool is_delete_button_clicked;
extern bool is_clear_screen_button_clicked;

extern bool all_buttons_of_or_on;

extern clock_t time_the_button_was_clicked;
extern clock_t time_right_now;

extern int game_clock;
extern int time_game_has_been_running_for;

extern bool what_boxes_in_the_middle_are_on[36][24];
extern int number_of_boxes_in_middle;
void setup_game();
#endif