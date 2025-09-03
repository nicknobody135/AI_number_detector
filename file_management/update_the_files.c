#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "update_the_files.h"
#include "../game_setup/game_setup.h"
#include "string.h"

void clean_the_screen()
{
    for (int a = 0; a < 36; a++)
    {
        for (int b = 0; b < 24; b++)
        {
            what_boxes_in_the_middle_are_on[a][b] = false;
        }
    }
}

void update_files()
{
    if (game_clock%2 == 0)
    {
        //sets the file names that are displayed
        for (int i = 0; i < 4; i++) {strcpy(what_files_to_show[i] , drawing_files[i+top_file_n]);}
    }
}