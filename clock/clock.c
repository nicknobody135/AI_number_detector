#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "clock.h"

int game_clock;

void update_clock()
{
    game_clock = game_clock + 1;
    if (game_clock == 61)
    {
        game_clock = 0;
        time_game_has_been_running_for = time_game_has_been_running_for + 1;
    }
}