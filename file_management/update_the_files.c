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

void load_the_drawings_into_a_char()
{
    contents_of_training_data_files = malloc(temp_len * sizeof(char*));
    for (int i = 0; i < temp_len; i++)
    {
        char *tempfile = LoadFileText(files.paths[i]);
        contents_of_training_data_files[i] = malloc(strlen(tempfile) + 1);
        contents_of_training_data_files[i] = LoadFileText(files.paths[i]);
    }
}

void load_how_many_drawings_in_each_file()
{
    how_many_drawings_in_each_file = malloc(temp_len * sizeof(int));
    for (int i = 0; i < temp_len; i++)
    {
        int n_of_lines = count_lines(contents_of_training_data_files[i]);
        how_many_drawings_in_each_file[i] = (int)n_of_lines/37;
    }
}

int count_lines(char *vicitm)
{
    int n_of_lines = 0;
    for (int j = 0;j < strlen(vicitm);j++)
    {
        if (vicitm[j] == '\n' || vicitm[j] == '\0')
        {
            n_of_lines = n_of_lines + 1;
        }
    }
    return n_of_lines + 1;
}

void update_how_many_drawings_in_each_file()
{
    for (int i = 0; i < temp_len; i++)
    {
        int n_of_lines = count_lines(contents_of_training_data_files[i]);
        how_many_drawings_in_each_file[i] = (int)n_of_lines/37;
    }
}

void load_which_file_the_user_on()
{
    which_drawing_among_the_files_is_the_user_on = malloc(temp_len * sizeof(bool *));
    for (int i = 0; i < temp_len; i++)
    {
        which_drawing_among_the_files_is_the_user_on[i] = malloc(how_many_drawings_in_each_file[i] * sizeof(bool));
        for (int j = 0; j < how_many_drawings_in_each_file[i]; j++)
        {
            which_drawing_among_the_files_is_the_user_on[i][j] = false;
        }
    }
}

void set_all_selected_files_to_false()
{
    for (int i = 0 ; i < temp_len ; i++)
    {
        for (int j = 0 ; j < how_many_drawings_in_each_file[i] ; j++)
        {
            which_drawing_among_the_files_is_the_user_on[i][j] = 0;
        }
    }
}

void load_a_new_drawing_to_the_screen(int which_file , int which_drawing)
{
    int increaseer = 0;
    int extra_drawing_increase =  14 + which_drawing*(14 + 900);
    for (int a = 0; a < 36; a++)
    {
        for (int b = 0; b < 25; b++)
        {
            if (contents_of_training_data_files[which_file][extra_drawing_increase + increaseer] == '1')
            {
                what_boxes_in_the_middle_are_on[a][b] = 1;
                
            }
            else if (contents_of_training_data_files[which_file][extra_drawing_increase + increaseer] == '0')
            {
                what_boxes_in_the_middle_are_on[a][b] = 0;
            }
            increaseer = increaseer + 1;
        }
    }
}

void save_to_file(int which_file_to_save_to , int which_drawing_in_the_file_to_save_to)
{
    int increaseer = 0;
    int extra_drawing_increase =  14 + which_drawing_in_the_file_to_save_to*(14 + 900);
    for (int a = 0; a < 36; a++)
    {
        for (int b = 0; b < 24; b++)
        {
            if (what_boxes_in_the_middle_are_on[a][b] == 1)
            {
                contents_of_training_data_files[which_file_to_save_to][extra_drawing_increase + increaseer] = '1';
                
            }
            else if (what_boxes_in_the_middle_are_on[a][b] == 0)
            {
                contents_of_training_data_files[which_file_to_save_to][extra_drawing_increase + increaseer] = '0';
                
            }
            increaseer = increaseer + 1;
        }
        increaseer = increaseer + 1;
    }

    for (int i = 0; i < temp_len; i++)
    {
        SaveFileText(files.paths[i] , contents_of_training_data_files[i]);
    }
    
}

void delete_a_drawing(int target_file , int target_drawing)
{
    clean_the_screen();
    printf("deleting....\n");
    int increaseer = 0;
    int extra_drawing_increase =  target_drawing*(14 + 900) - 1;
    memmove(contents_of_training_data_files[target_file] + extra_drawing_increase , contents_of_training_data_files[target_file] + extra_drawing_increase + (14 + 900) , strlen(contents_of_training_data_files[target_file]) - extra_drawing_increase - (14 + 900) + 1);
    for (int i = 0; i < temp_len; i++) 
    {
        free(which_drawing_among_the_files_is_the_user_on[i]);
    }
    free(which_drawing_among_the_files_is_the_user_on);
    load_which_file_the_user_on();
    if (target_drawing == 0)
    {
        which_drawing_among_the_files_is_the_user_on[target_file][target_drawing] = 1;
        load_a_new_drawing_to_the_screen(target_file , target_drawing);
    }
    else
    {
        which_drawing_among_the_files_is_the_user_on[target_file][target_drawing - 1] = 1;
        load_a_new_drawing_to_the_screen(target_file , target_drawing - 1);
    }
    update_how_many_drawings_in_each_file();
}

void create_a_new_file(int target_file , int target_drawing)
{
    printf("creating a new file.........\n");
    char string_to_add[935] = "\nstart_draw_0:\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\n000000000000000000000000\0";
    contents_of_training_data_files[target_file] = realloc(contents_of_training_data_files[target_file] , 935+strlen(contents_of_training_data_files[target_file]));
    strcat(contents_of_training_data_files[target_file] , string_to_add);
    update_how_many_drawings_in_each_file();
    clean_the_screen();
    free(which_drawing_among_the_files_is_the_user_on);
    load_which_file_the_user_on();
    which_drawing_among_the_files_is_the_user_on[target_file][target_drawing + 1] = 1;
    load_a_new_drawing_to_the_screen(target_file , target_drawing + 1);
}

