#include "C:\raylib\raylib\src\raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "update_the_state_of_things.h"
#include "mouse_updates\update_mouse.h"
#include "button_management\update_buttons.h"
#include "mouse_updates/scrolling.h"
#include "..\file_management\update_the_files.h"


void update_the_state_of_things()
{
    update_mouse_details();
    update_the_buttons();

    //check for scrolling on the file selector
    if (mousePos.x > 145*scale && mousePos.x < 569*scale && mousePos.y > 368*scale && mousePos.y < 544*scale && scroll_amount != 0.0f)
    {
        update_the_file_selector_scroll();
    }

    //check for scrolling on the drawing

    is_any_file_selected = check_if_any_file_is_selected();

    if (mousePos.x > 596*scale && mousePos.x < 1004*scale && mousePos.y > 238*scale && mousePos.y < 850*scale && scroll_amount != 0.0f && is_any_file_selected == 1)
    {
        printf("drawing scrolling\n");
        update_the_drawing_scroller();
    }
}