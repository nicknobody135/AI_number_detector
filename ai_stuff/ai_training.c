#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//setup:

//file stuff
int target_file_to_choose_drawings_to_convert_to_binary = 0;
int target_drawing_to_convert_to_binary = 0;
char line_buffer[25];
float converted_binary_drawing_from_file[36][24];
char file_locations_of_training_data[11][30] = {"training_data\\0s(a).txt" , "training_data\\1s(a).txt" , "training_data\\2s(a).txt" , "training_data\\3s(a).txt" , "training_data\\4s(a).txt" , "training_data\\5s(a).txt" , "training_data\\6s(a).txt" , "training_data\\7s(a).txt" , "training_data\\8s(a).txt" , "training_data\\9s(a).txt" , "training_data\\example.txt"};
FILE *target_file;
FILE *weights_and_biases;
long weights_and_biases_file_size = 0;

//forward propagation
//*------------------------------------------------------------------------------------------------------------*//
//first Layer:
float input_layer_to_first_layer_weights[128][864];//load from file
float input_layer_to_first_layer_weighted_sum[128];
float baises_of_the_first_layer[128];//load_from_file
float result_of_the_first_layer[128];
//*------------------------------------------------------------------------------------------------------------*//
//Second Layer:
float weights_of_first_layer_to_second_layer[64][128];//load_from_file
float weighted_sum_of_first_layer_to_second_layer[64];
float baises_of_second_layer[64];//load_from_file
float result_of_second_layer[64];
//*------------------------------------------------------------------------------------------------------------*//
//Output Layer:
float weights_of_second_layer_to_output[10][64];//load_from_file
float weighted_sum_of_second_layer_to_output[10];
float biases_of_output_layer[10];//load_from_file
float final_outputs[10];
//*------------------------------------------------------------------------------------------------------------*//
//Global neural network variables:
float cost;


//function predef
int cost_function();
int convert_txt_to_binary(int target_file_to_choose_drawings_to_convert_to_binary , int target_drawing_to_convert_to_binary);
int initialize_weights_and_biases();
int forward_propagation();
int back_propagation();

//code:
int cost_function()
{
    cost = 0.0f;
    for (int i = 0  ; i < 1000 ; i++)
    {
        printf("%f\n" , (i/1000.0f)*100.0f);
        convert_txt_to_binary((int)((i/1000.0f)*10.0f) , i%100);
        forward_propagation();
        cost = cost+(-logf(final_outputs[(int)((i/1000.0f)*10.0f)] + 1e-7f));
    }
    cost = cost/1000;
    printf("%f\n" , cost);
}

int convert_txt_to_binary(int target_file_to_choose_drawings_to_convert_to_binary , int target_drawing_to_convert_to_binary)
{
    int extra_drawing_increase = (target_drawing_to_convert_to_binary*(15+936))+15;
    target_file = fopen(file_locations_of_training_data[target_file_to_choose_drawings_to_convert_to_binary] , "r");
    //getting_chars_form_the_txt
    fseek(target_file , extra_drawing_increase , SEEK_SET);
    for (int i = 0; i < 36; i++)
    {
        fgets(line_buffer , 26 , target_file);
        //printf("Line Buffer : %s\n" , line_buffer);
        for(int b = 0; b < 24 ; b++)
        {
			if (line_buffer[b] == '1')
			{
				converted_binary_drawing_from_file[i][b] = 1.0f;
			}
			if (line_buffer[b] == '0')
			{
				converted_binary_drawing_from_file[i][b] = 0.0f;
			}
        }
    }
    fclose(target_file);
    // for (int i = 0 ; i < 36 ; i++)
    // {
    //     for (int b = 0 ; b < 24 ; b++)
    //     {
    //         printf("%d" , converted_binary_drawing_from_file[i][b]);
    //     }
    //     printf("\n");
    // }
    return 0;
}

int initialize_weights_and_biases()
{
    weights_and_biases = fopen("ai_stuff\\neural_network_weights_and_biases.bin" , "rb");
    //filesize checking
    fseek(weights_and_biases , 0 , SEEK_END);
    weights_and_biases_file_size = ftell(weights_and_biases);
    fseek(weights_and_biases , 0 , SEEK_SET);
    printf("Size of file %ld , Expected : 478504\n" , weights_and_biases_file_size);

    //variable initialization:
    fread(input_layer_to_first_layer_weights, 4 , 110592 , weights_and_biases);
    fread(baises_of_the_first_layer , 4 , 128 , weights_and_biases);
    fread(weights_of_first_layer_to_second_layer , 4 , 8192 , weights_and_biases);
    fread(baises_of_second_layer , 4 , 64 , weights_and_biases);
    fread(weights_of_second_layer_to_output , 4 , 640 , weights_and_biases);
    fread(biases_of_output_layer , 4 , 10 , weights_and_biases);
}

int forward_propagation()
{
    //*------------------------------------------------------------------------------------------------------------*//

    //First Layer:

    //Weighted sum of input layers to first layer
    for(int a = 0 ; a < 128 ; a++)
    {
        input_layer_to_first_layer_weighted_sum[a] = 0;
        for(int b = 0 ; b < 864 ; b++)
        {
            input_layer_to_first_layer_weighted_sum[a] = input_layer_to_first_layer_weighted_sum[a] + (input_layer_to_first_layer_weights[a][b] * converted_binary_drawing_from_file[b/24][b%24]); 
        }
    }

    //Bias adding
    for(int a = 0 ; a < 128 ; a++)
    {
        result_of_the_first_layer[a] = input_layer_to_first_layer_weighted_sum[a] + baises_of_the_first_layer[a];
    }

    //Relu fucntion:
    for(int a = 0 ; a < 128 ; a++)
    {
        if (result_of_the_first_layer[a] <= 0)
        {
            result_of_the_first_layer[a] = 0;
        }
    }
    //*------------------------------------------------------------------------------------------------------------*//

    //Second Layer:

    //weighted sum of the first layer outputs:
    for(int a = 0 ; a < 64 ; a++)
    {
        weighted_sum_of_first_layer_to_second_layer[a] = 0;
        for(int b = 0 ; b < 128 ; b++)
        {
            weighted_sum_of_first_layer_to_second_layer[a] = weighted_sum_of_first_layer_to_second_layer[a] + (weights_of_first_layer_to_second_layer[a][b] * result_of_the_first_layer[b]);
        }
    }

    //Baises adding:
    for(int a = 0 ; a < 64 ; a++)
    {
        result_of_second_layer[a] = weighted_sum_of_first_layer_to_second_layer[a] + baises_of_second_layer[a]; 
    }

    //Relu function:
    for(int a = 0 ; a<64 ; a++)
    {
        if (result_of_second_layer[a] <= 0)
        {
            result_of_second_layer[a] = 0;
        }
    }
    //*------------------------------------------------------------------------------------------------------------*//

    //Output Layer:

    //Weighted sum of the output layer:

    for(int a = 0 ; a < 10 ; a++)
    {
        weighted_sum_of_second_layer_to_output[a] = 0;
        for(int b = 0 ; b < 64 ; b++)
        {
            weighted_sum_of_second_layer_to_output[a] = weighted_sum_of_second_layer_to_output[a] + (weights_of_second_layer_to_output[a][b] * result_of_second_layer[b]);
        }
    }

    //Baises adding:

    for(int a = 0 ; a < 10 ; a++)
    {
        final_outputs[a] = weighted_sum_of_second_layer_to_output[a] + biases_of_output_layer[a];
    }

    //Output Layer 
    float max = final_outputs[0];
    for(int a = 0 ; a < 10 ; a++)
    {
        if(final_outputs[a] > max)max = final_outputs[a];
    }
    float sum = 0.0f;
    for(int a = 0 ; a < 10 ; a++)
    {
        sum = sum + expf(final_outputs[a] - max);
    }
    for(int a = 0 ; a < 10 ; a++)
    {
        final_outputs[a] = (expf(final_outputs[a]-max)/sum);
        //printf("Ans : %f\n" , final_outputs[a]);
    }
    return 0;
}


int main()
{
    printf("Ai trainer....\n");
    //convert_txt_to_binary(9 , 54);
    initialize_weights_and_biases();
    //forward_propagation();
    cost_function();
    printf("Sucessful Run\n");
    // srand(time(NULL));
    // float val = ((float)rand()/RAND_MAX)*0.2f - 0.1f;
    // weights_and_biases = fopen("ai_stuff\\neural_network_weights_and_biases.bin" , "wb");
    // for(int a = 0 ; a < 119626 ; a++)
    // {
    //     float val = ((float)rand()/RAND_MAX)*0.2f - 0.1f;
    //     fwrite(&val , 4 , 1 , weights_and_biases);
    // }
    // float r = ((float)rand() / RAND_MAX) * 10.0f - 1.0f;
    return 0;
}