#ifndef UPDATE_FILES
#define UPDATE_FILES
#include "C:\raylib\raylib\src\raylib.h"
#include "../game_setup/game_setup.h"
void update_files();
void clean_the_screen();
void load_the_drawings_into_a_char();
void load_how_many_drawings_in_each_file();
void update_how_many_drawings_in_each_file();
int count_lines(char *vicitm);
void load_which_file_the_user_on();
void set_all_selected_files_to_false();
void load_a_new_drawing_to_the_screen(int which_file , int which_drawing);
void save_to_file(int which_file_to_save_to , int which_drawing_in_the_file_to_save_to);
void delete_a_drawing(int target_file , int target_drawing);
void create_a_new_file(int target_file , int target_drawing);
#endif