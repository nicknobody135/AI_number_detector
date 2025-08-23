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
    int cellSize = (int)(17 * scale);
    if (is_the_mouse_really_down && mousePos.x >= 596* scale && mousePos.x < 1004* scale && mousePos.y >= 238* scale && mousePos.y < 850* scale)
    {
        int dx = mousePos.x - lastMospos.x;
        int dy = mousePos.y - lastMospos.y;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

        if (steps == 0)
        {
            steps = 1;
        }

        int tolerance = 10* scale;

        for (int i = 0; i <= steps; i++) {
            int x = lastMospos.x + dx * i / steps;
            int y = lastMospos.y + dy * i / steps;

            int col = (x - 596* scale) / cellSize;
            int row = (y - 238* scale) / cellSize;

            for (int rr = row - 1; rr <= row + 1; rr++) {
                if (rr < 0 || rr >= 36) continue;

                int boxY = 238* scale + rr * cellSize;
                if (y >= boxY - tolerance && y < boxY + cellSize + tolerance) {
                    for (int cc = col - 1; cc <= col + 1; cc++) 
                    {
                        if (cc < 0 || cc >= 24) continue;

                        int boxX = 596* scale + cc * cellSize;
                        if (x >= boxX - tolerance && x < boxX + cellSize + tolerance) 
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