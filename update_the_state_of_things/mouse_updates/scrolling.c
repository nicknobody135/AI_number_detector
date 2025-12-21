#include "C:\raylib\raylib\src\raylib.h"
#include "..\..\game_setup\game_setup.h"
#include "update_mouse.h"
#include "stdio.h"
#include "stdlib.h"
#include "..\..\file_management\update_the_files.h"

void update_the_file_selector_scroll()
{
    if (top_file_n + scroll_amount >= 0 && top_file_n + scroll_amount < temp_len - 3)
    {
        top_file_n = (int)(top_file_n + scroll_amount);
    }
}

void update_the_drawing_scroller()
{
    which_file = which_file_is_selected();
    which_drawing = which_drawing_in_said_file_is_selected(which_file);
    //set all slected files to false then set the current file as selected
    //load a new file to the screen
    if (which_file != -1 && which_drawing != -1 && which_drawing != how_many_drawings_in_each_file[which_file] - 1 && scroll_amount > 0)
    {
        set_all_selected_files_to_false();
        which_drawing_among_the_files_is_the_user_on[which_file][which_drawing + 1] = true;
        which_drawing = which_drawing_in_said_file_is_selected(which_file);
        load_a_new_drawing_to_the_screen(which_file , which_drawing);
    }

    else if(which_file != -1 && which_drawing != -1 && which_drawing != 0 && scroll_amount < 0)
    {
        set_all_selected_files_to_false();
        which_drawing_among_the_files_is_the_user_on[which_file][which_drawing - 1] = true;
        which_drawing = which_drawing_in_said_file_is_selected(which_file);
        load_a_new_drawing_to_the_screen(which_file , which_drawing);
    }
}