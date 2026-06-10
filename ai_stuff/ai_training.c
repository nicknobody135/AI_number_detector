#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//input 864
//first layer 1024
//second layer 1024
//third layer 768
//fourth layer 512
//fifth layer 256
//output layer 10

//*------------------------------------------------------------------------------------------------------------*//
//Variables:

//File management
int target_file_to_choose_drawings_to_convert_to_binary = 0;
int target_drawing_to_convert_to_binary = 0;
char line_buffer[25];
float converted_binary_drawing_from_file[36][24];
int training_set_num = 3;
char file_locations_of_training_data[41][35] = {"training_data\\set_a\\0s(a).txt" , "training_data\\set_a\\1s(a).txt" , "training_data\\set_a\\2s(a).txt" , "training_data\\set_a\\3s(a).txt" , "training_data\\set_a\\4s(a).txt" , "training_data\\set_a\\5s(a).txt" , "training_data\\set_a\\6s(a).txt" , "training_data\\set_a\\7s(a).txt" , "training_data\\set_a\\8s(a).txt" , "training_data\\set_a\\9s(a).txt" , "training_data\\set_b\\0s(b).txt" , "training_data\\set_b\\1s(b).txt" , "training_data\\set_b\\2s(b).txt" , "training_data\\set_b\\3s(b).txt" , "training_data\\set_b\\4s(b).txt" , "training_data\\set_b\\5s(b).txt" , "training_data\\set_b\\6s(b).txt" , "training_data\\set_b\\7s(b).txt" , "training_data\\set_b\\8s(b).txt" , "training_data\\set_b\\9s(b).txt" , "training_data\\set_c\\0s(c).txt" , "training_data\\set_c\\1s(c).txt" , "training_data\\set_c\\2s(c).txt" , "training_data\\set_c\\3s(c).txt" , "training_data\\set_c\\4s(c).txt" , "training_data\\set_c\\5s(c).txt" , "training_data\\set_c\\6s(c).txt" , "training_data\\set_c\\7s(c).txt" , "training_data\\set_c\\8s(c).txt" , "training_data\\set_c\\9s(c).txt" , "training_data\\set_d\\0s(d).txt" , "training_data\\set_d\\1s(d).txt" , "training_data\\set_d\\2s(d).txt" , "training_data\\set_d\\3s(d).txt" , "training_data\\set_d\\4s(d).txt" , "training_data\\set_d\\5s(d).txt" , "training_data\\set_d\\6s(d).txt" , "training_data\\set_d\\7s(d).txt" , "training_data\\set_d\\8s(d).txt" , "training_data\\set_d\\9s(d).txt" , "training_data\\set_a\\example.txt"};
FILE *target_file;
FILE *weights_and_biases;
long weights_and_biases_file_size = 0;
bool display_results_or_not = 0;

//Forward propagation varaibles:
float forward_prop_weights[3246592];
float forward_prop_biases[3594];
float forward_prop_results[3594];
float final_outputs[10];
float cost;
int prediction;

//Back propagation:

float gradients_of_the_outputs[3594];
float gradients_of_the_baises[3594];
float gradients_of_the_weights[3246592];
float expected_outputs[10];
float learning_rate = 0.1f;

//General Neural Network variables:

bool display_result_or_not = 0;
float weighted_sums[3594];
float pre_relu_results[3594];
int individual_layer_size[6] = {1024 , 1024 , 768 , 512 , 256 , 10};
int layer_size[6] = {0 , 1024 , 2048 , 2816 , 3328 , 3584};
int weight_offsets[6] = {0 , 884736 , 1933312 , 2719744 , 3112960 , 3244032};
int training_data_size = 1000;

//*------------------------------------------------------------------------------------------------------------*//
//Function pre def

void convert_txt_to_binary(int target_file_to_choose_drawings_to_convert_to_binary , int target_drawing_to_convert_to_binary , int training_set_num);

void initialize_weights_and_biases();

void forward_propagation(bool display_results_or_not);

void cost_function();

void back_propagation();

void weight_updater();

void save_weights_and_biases_to_file();

//*------------------------------------------------------------------------------------------------------------*//
//Functions:

void convert_txt_to_binary(int target_file_to_choose_drawings_to_convert_to_binary , int target_drawing_to_convert_to_binary , int training_set_num)
{
    int extra_drawing_increase = (target_drawing_to_convert_to_binary*(15+936))+15;
    target_file = fopen(file_locations_of_training_data[(training_set_num*10) + target_file_to_choose_drawings_to_convert_to_binary] , "r");
    //printf("%s\n" , file_locations_of_training_data[(training_set_num*10) + target_file_to_choose_drawings_to_convert_to_binary]);
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
    //         printf("%d" , (int)(converted_binary_drawing_from_file[i][b]));
    //     }
    //     printf("\n");
    // }
}

void initialize_weights_and_biases()
{
    weights_and_biases = fopen("ai_stuff\\neural_network_weights_and_biases.bin" , "rb");

    //filesize checking

    fseek(weights_and_biases , 0 , SEEK_END);
    weights_and_biases_file_size = ftell(weights_and_biases);
    fseek(weights_and_biases , 0 , SEEK_SET);
    printf("Size of file %ld , Expected : 13000744\n" , weights_and_biases_file_size);

    //weights and biases initialization:

    fread(forward_prop_weights, 4 , 3246592 , weights_and_biases);
    fread(forward_prop_biases, 4 , 3594 , weights_and_biases);
    fclose(weights_and_biases);
}

void forward_propagation(bool display_results_or_not)
{
    //*------------------------------------------------------------------------------------------------------------*//

    for(int a = 0 ; a < 6 ; a++)
    {
        //input layer
        //*------------------------------------------------------------------------------------------------------------*//
        if(a == 0)
        {
            for(int b = 0 ; b < individual_layer_size[a] ; b++)
            {
                weighted_sums[b] = 0.0f;
                for(int c = 0 ; c < 864 ; c++)
                {
                    weighted_sums[b] += (forward_prop_weights[(b*864)+c] * converted_binary_drawing_from_file[c/24][c%24]);
                }
            }
        }
        //*------------------------------------------------------------------------------------------------------------*//

        //weights for the normal layers
        if(a != 0)
        {
            for(int b = 0 ; b < individual_layer_size[a] ; b++)
            {
                weighted_sums[b+layer_size[a]] = 0.0f;
                for(int c = 0 ; c < +individual_layer_size[a-1] ; c++)
                {
                    weighted_sums[b+layer_size[a]] += (forward_prop_weights[((b*individual_layer_size[a-1]) + c) + weight_offsets[a]] * forward_prop_results[c+layer_size[a-1]]);
                }
            }
        }

        //biases
        for(int b = 0 ; b < individual_layer_size[a] ; b++)
        {
            pre_relu_results[b+layer_size[a]] = weighted_sums[b+layer_size[a]] + forward_prop_biases[b+layer_size[a]];
        }

        //output
        if (a != 5)
        {
            for(int b = 0 ; b < individual_layer_size[a] ; b++)
            {
                forward_prop_results[b + layer_size[a]] = pre_relu_results[b + layer_size[a]];
                if(forward_prop_results[b + layer_size[a]] < 0 && a != 5)
                {
                    forward_prop_results[b + layer_size[a]] = 0.0f;
                }
            }
        }

        if(a == 5)
        {
            for(int b = 0 ; b < 10 ; b++)
            {
                forward_prop_results[b + layer_size[a]] = pre_relu_results[b + layer_size[a]];
            }   
            float max = forward_prop_results[3584];
            for(int c = 3584 ; c < 3594 ; c++)
            {
                if(forward_prop_results[c] > max)
                {
                    max = forward_prop_results[c];
                    prediction = c - 3584;
                }
            }
            float sum = 0.0f;
            for(int c = 3584 ; c < 3594 ; c++)
            {
                sum = sum + expf(forward_prop_results[c] - max);
            }
            
            if(display_results_or_not == 1)printf("Prediction : %d\n" , prediction);

            for(int c = 0 ; c < 10 ; c++)
            {
                final_outputs[c] = (expf(forward_prop_results[c+3584]-max)/sum);
                if(display_results_or_not == 1)
                {
                    printf("%d , Ans : %f\n" , c , final_outputs[c]);
                }
            }
            
        }
    }

    //*------------------------------------------------------------------------------------------------------------*//

}

void cost_function()
{
    printf("Calculating Cost ...........\n");
    cost = 0.0f;
    for (int i = 0  ; i < training_data_size ; i++)
    {
        convert_txt_to_binary((int)((i/(training_data_size/1.0f))*10.0f) , i%((int)training_data_size/10) , training_set_num);
        forward_propagation(0);
        cost = cost+(-logf(final_outputs[(int)((i/(training_data_size/1.0f))*10.0f)] + 1e-7f));

        // if(i%100 == 0)
        // {
        //     printf("Percent Done : %f\n" , ((float)i/(float)training_data_size)*100.0f);
        // }
    }
    cost = cost/training_data_size;
    printf("Cost : %f\n" , cost);
}

void back_propagation()
{

    printf("Backprop Starting.......\n");

    //*------------------------------------------------------------------------------------------------------------*//
    //reseting all the old values

    for(int a = 0 ; a < 3594 ; a++)
    {
        gradients_of_the_baises[a] = 0.0f;
    }

    for(int a = 0 ; a < 3246592 ; a++)
    {
        gradients_of_the_weights[a] = 0.0f;
    }

    //*------------------------------------------------------------------------------------------------------------*//

    for(int a = 0 ; a < training_data_size ; a++)
    {
        for(int b = 0 ; b < 3594 ; b++)
        {
            gradients_of_the_outputs[b] = 0.0f;
        }

        //percent done:
        // if(a%100 == 0)
        // {
        //     printf("Percent Done : %f\n" , ((float)a/(float)training_data_size)*100.0f);
        // }

        convert_txt_to_binary((int)((a/(training_data_size/1.0f))*10.0f) , a%((int)training_data_size/10) , training_set_num);
        forward_propagation(0);

        for(int b = 0 ; b < 10 ; b++)
        {
            if(b == (int)(((float)a/(float)training_data_size)*10.0f))
            {
                expected_outputs[b] = 1.0f;
            }
            else
            {
                expected_outputs[b] = 0.0f; 
            }
        }

        for(int b = 5 ; b > -1 ; b--)
        {
            //output layer
            if(b == 5)
            {
                //gradient
                for(int c = 0 ; c < 10 ; c++)
                {
                    gradients_of_the_outputs[layer_size[b]+c] = final_outputs[c] - expected_outputs[c];
                }
            }

            if(b != 5)
            {
                //normal outputs
                for(int c = 0 ; c < individual_layer_size[b] ; c++)
                {
                    for(int d = 0 ; d < individual_layer_size[b+1] ; d++)
                    {
                        gradients_of_the_outputs[layer_size[b]+c] += forward_prop_weights[weight_offsets[b+1]+(d*individual_layer_size[b])+c]*gradients_of_the_outputs[layer_size[b+1]+d];
                    }

                    if(pre_relu_results[layer_size[b]+c] < 0.0f)
                    {
                        gradients_of_the_outputs[layer_size[b]+c] = 0.0f;
                    }
                }
            }

            //baises
            for(int c = 0 ; c < individual_layer_size[b] ; c++)
            {
                gradients_of_the_baises[layer_size[b]+c] += gradients_of_the_outputs[layer_size[b]+c];
            }

            //last_layer

            //weights
            if(b !=0)
            {
                for(int c = 0 ; c < individual_layer_size[b] ; c++)
                {
                    for(int d = 0 ; d < individual_layer_size[b-1] ; d++)
                    {
                        gradients_of_the_weights[weight_offsets[b]+(c*individual_layer_size[b-1])+d] += gradients_of_the_outputs[layer_size[b]+c] * forward_prop_results[layer_size[b-1]+d];
                    }
                }
            }
            
            if(b == 0)
            {
                for(int c = 0 ; c < individual_layer_size[b] ; c++)
                {
                    for(int d = 0 ; d < 864 ; d++)
                    {
                        gradients_of_the_weights[(c*864)+d] += gradients_of_the_outputs[c] * converted_binary_drawing_from_file[d/24][d%24];
                    }
                }
            }

            //End of back prop
        }
    }
    //*------------------------------------------------------------------------------------------------------------*//
    //Finalzing results

    for(int a = 0 ; a < 3594 ; a++)
    {
        gradients_of_the_baises[a] = gradients_of_the_baises[a]/training_data_size; 
    }

    for(int a = 0 ; a < 3246592 ; a++)
    {
        gradients_of_the_weights[a] = gradients_of_the_weights[a]/training_data_size;
    }
}

void weight_updater()
{
    for(int a = 0 ; a < 3246592 ; a++)
    {
        forward_prop_weights[a] -= gradients_of_the_weights[a] * learning_rate;
    }

    for(int a = 0 ; a < 3594 ; a++)
    {
        forward_prop_biases[a] -= gradients_of_the_baises[a] * learning_rate;
    }
}

void save_weights_and_biases_to_file()
{
    weights_and_biases = fopen("ai_stuff\\neural_network_weights_and_biases.bin" , "wb");

    for(int a = 0 ; a < 3246592 ; a++)
    {
        float val = forward_prop_weights[a];
        fwrite(&val , 4 , 1 , weights_and_biases);
    }

    for(int a = 0 ; a < 3594 ; a++)
    {
        float val = forward_prop_biases[a];
        fwrite(&val , 4 , 1 , weights_and_biases);
    }

    printf("Size of file %ld , Expected : 13000744\n" , weights_and_biases_file_size);
    fclose(weights_and_biases);
}

int main()
{
    printf("Ai trainer....\n");
    initialize_weights_and_biases();

    convert_txt_to_binary(0 , 8 , 4);
    forward_propagation(1);

    // training_set_num = 0;
    
    //cost_function();

    // for(int i = 0 ; i < 20 ; i++)
    // {
    //     printf("%d\n" , i);
    //     for(int a = 0 ; a < 4 ; a++)
    //     {
    //         training_set_num = a;
    //         back_propagation();
    //         weight_updater();
    //         if(i%5==0)cost_function();
    //     }
    //     save_weights_and_biases_to_file();
    // }

    // cost_function();

    // save_weights_and_biases_to_file();

    //*------------------------------------------------------------------------------------------------------------*//
    //for(int i = 0 ; i < 4 ; i++)
    //{
    //    training_set_num = i;
    //    cost_function();
    //}
    //*------------------------------------------------------------------------------------------------------------*//

    printf("Sucessful Run\n");

    //*------------------------------------------------------------------------------------------------------------*//
    // srand(time(NULL));
    // float val = ((float)rand()/RAND_MAX)*0.2f - 0.1f;
    // weights_and_biases = fopen("ai_stuff\\new_neural_network_weights_and_biases.bin" , "wb");
    // for(int a = 0 ; a < 3250186 ; a++)
    // {
    //     float val = ((float)rand()/RAND_MAX)*0.2f - 0.1f;
    //     fwrite(&val , 4 , 1 , weights_and_biases);
    // }
    //*------------------------------------------------------------------------------------------------------------*//

    return 0;
}