#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "C:\Users\Lenovo\Desktop\Coding\c_and_cpp\c\medium_projects\AI_number_detector\game_setup\game_setup.h"
#include "math.h"

int which_colum_counter = 0;
int which_row_counter = 0;
int mouse_distance_between_last_frame_y;
int mouse_distance_between_last_frame_x;
int mouse_y;
int mouse_x;

void update_drawing()
{   
    if (is_the_mouse_really_down && mousePos.x >= 596 && mousePos.x < 1004 && mousePos.y >= 238 && mousePos.y < 850)
    {
        int dx = mousePos.x - lastMospos.x;
        int dy = mousePos.y - lastMospos.y;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

        if (steps == 0)
        {
            steps = 1;
        }

        int tolerance = 7;

        for (int i = 0; i <= steps; i++) {
            int x = lastMospos.x + dx * i / steps;
            int y = lastMospos.y + dy * i / steps;

            int col = (x - 596) / 17;
            int row = (y - 238) / 17;

            for (int rr = row - 1; rr <= row + 1; rr++) {
                if (rr < 0 || rr >= 36) continue;

                int boxY = 238 + rr * 17;
                if (y >= boxY - tolerance && y < boxY + 17 + tolerance) {
                    for (int cc = col - 1; cc <= col + 1; cc++) 
                    {
                        if (cc < 0 || cc >= 24) continue;

                        int boxX = 596 + cc * 17;
                        if (x >= boxX - tolerance && x < boxX + 17 + tolerance) 
                        {
                            what_boxes_in_the_middle_are_on[rr][cc] = true;
                        }
                    }
                }
            }
        }
    }

    mouse_distance_between_last_frame_y = 0;
    mouse_distance_between_last_frame_x = 0;
    which_colum_counter = 0;
    which_row_counter = 0; 
}