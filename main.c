#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "game_setup\game_setup.h"
#include "render_the_screen\render_the_screen.h"
#include "update_the_state_of_things\update_the_state_of_things.h"
#include "clock\clock.h"
#include "drawing_management\drawing_management.h"
#include "file_management/update_the_files.h"
int main()
{
    setup_game();   //inisilizes all the variables and window settings
    while (!WindowShouldClose())    //game loop
    {
        update_clock();     //clock that goes from one to 60 useful for doing things 30 times a second to reduce lag
        BeginDrawing();     //idk just part of the libary for some reason
        update_the_state_of_things();     //updates the mouse location and button states
        update_drawing();
        if (game_clock%3 == 0)update_files();
        render_the_screen();
        EndDrawing();
        //printf("%s\n", txt_files_for_drawing_display[0]);
    }
    CloseWindow();
    return 0;

}