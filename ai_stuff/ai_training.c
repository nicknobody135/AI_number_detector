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
//output lyer 10

//setup:

//file stuff
int target_file_to_choose_drawings_to_convert_to_binary = 0;
int target_drawing_to_convert_to_binary = 0;
char line_buffer[25];
float converted_binary_drawing_from_file[36][24];
//char file_locations_of_training_data[11][30] = {"set_b\\0s(b).txt" , "set_b\\1s(b).txt" , "set_b\\2s(b).txt" , "set_b\\3s(b).txt" , "set_b\\4s(b).txt" , "set_b\\5s(b).txt" , "set_b\\6s(b).txt" , "set_b\\7s(b).txt" , "set_b\\8s(b).txt" , "set_b\\9s(b).txt"};
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
float pre_relu_results_of_the_first_layer[128];
float result_of_the_first_layer[128];
//*------------------------------------------------------------------------------------------------------------*//
//Second Layer:
float weights_of_first_layer_to_second_layer[64][128];//load_from_file
float weighted_sum_of_first_layer_to_second_layer[64];
float baises_of_second_layer[64];//load_from_file
float result_of_second_layer[64];
float pre_relu_results_of_the_second_layer[64];
//*------------------------------------------------------------------------------------------------------------*//
//Output Layer:
float weights_of_second_layer_to_output[10][64];//load_from_file
float weighted_sum_of_second_layer_to_output[10];
float biases_of_output_layer[10];//load_from_file
float final_outputs[10];
//*------------------------------------------------------------------------------------------------------------*//
//Global neural network variables:
float cost;
//*------------------------------------------------------------------------------------------------------------*//
//Back propagation variables:
//Output variables:
float output_gradient[10];
float expected_outputs[10];
float gradients_of_biases_of_output_layer[10];
float gradients_of_weights_of_second_layer_to_output[10][64];
//Second layer variables:
float gradient_of_the_second_layer[64];
float gradients_of_the_weights_of_the_first_layer_to_second_layer[64][128];
float gradients_of_the_baises_of_the_second_layer[64];
//First layer viarables:
float gradient_of_the_first_layer[128];
float gradient_of_the_weights_of_the_input_layer_to_first_layer[128][864];
float gradient_of_the_biases_of_first_layer[128];
//*------------------------------------------------------------------------------------------------------------*//
//Costs:
//Initial random weights and biases = Cost : 2.304301
//First file save after 20 backprops = Cost : 2.292969
//Cost : 2.276044
//100 back props Cost : 2.126523
//500 back props Cost : 0.282198
//200 back props Cost : 0.103691
//Cost after training set b Cost : 0.453097
float learning_rate = 0.1;


//function predef
int cost_function();
int convert_txt_to_binary(int target_file_to_choose_drawings_to_convert_to_binary , int target_drawing_to_convert_to_binary);
int initialize_weights_and_biases();
int forward_propagation();
int back_propagation();
int update_weights_and_baises();
int save_to_file();

//code:
int cost_function()
{
    cost = 0.0f;
    for (int i = 0  ; i < 1000 ; i++)
    {
        convert_txt_to_binary((int)((i/1000.0f)*10.0f) , i%100);
        forward_propagation();
        cost = cost+(-logf(final_outputs[(int)((i/1000.0f)*10.0f)] + 1e-7f));
    }
    cost = cost/1000;
    printf("Cost : %f\n" , cost);
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
    fclose(weights_and_biases);
}

int forward_propagation()
{
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//

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
        pre_relu_results_of_the_first_layer[a] = result_of_the_first_layer[a]; 
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
        pre_relu_results_of_the_second_layer[a] = result_of_second_layer[a];
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
        printf("%d , Ans : %f\n" , a , final_outputs[a]);
    }
    return 0;
}

int back_propagation()
{
    printf("Starting Back prop......\n");
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Reset old_values
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Ouptut Layer:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int i = 0 ; i < 10 ; i++)
    {
        gradients_of_biases_of_output_layer[i] = 0.0f;
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 10 ; a++)
    {
        for(int b = 0 ; b < 64 ; b++)
        {
            gradients_of_weights_of_second_layer_to_output[a][b] = 0.0f;
        }
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Second Layer:
    for(int a = 0 ; a < 64 ; a++)
    {
        gradient_of_the_second_layer[a] = 0.0f;
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 64 ; a++)
    {
        for(int b = 0 ; b < 128 ; b++)
        {
            gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b] = 0.0f;
        }
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a  = 0 ; a < 64 ; a++)
    {
        gradients_of_the_baises_of_the_second_layer[a] = 0.0f;
    }
    //First Layer:
    for(int a = 0  ; a < 128 ; a++)
    {
        gradient_of_the_first_layer[a] = 0.0f;
    }
    for(int a = 0 ; a < 128 ; a++)
    {
        for(int b = 0 ; b < 864 ; b++)
        {
            gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b] = 0.0f;
        }
    }
    for(int a  = 0 ; a < 128 ; a++)
    {
        gradient_of_the_biases_of_first_layer[a] = 0.0f;
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//    
    //calculating for each of the thousand training examples:
    for(int i = 0 ; i < 1000 ; i++)
    {
        //Reseting results:
        for(int a  = 0 ; a < 10 ; a++)
        {
            output_gradient[a] = 0.0f;
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        for(int a = 0 ; a < 64 ; a++)
        {
            gradient_of_the_second_layer[a] = 0.0f;
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        for(int a = 0 ; a < 128 ; a++)
        {
            gradient_of_the_first_layer[a] = 0.0f;
        }
        //percent done:
        if(i%10 == 0)
        {
            //printf("Percent Done : %f\n" , (i/1000.0f)*100);
        }
        //Loading the current training example to calculate weights and biases
        convert_txt_to_binary((int)((i/1000.0f)*10.0f) , i%100);
        forward_propagation();
        //expected output:
        for(int a = 0 ; a < 10 ; a++)
        {
            if(a == (int)((i/1000.0f)*10.0f))
            {
                expected_outputs[a] = 1.0f;
            }
            else
            {
                expected_outputs[a] = 0.0f; 
            }
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //Backpropagation Start:
        //OutputLayer:
        //Calculating the loss:

        for(int a = 0 ; a < 10 ; a++)
        {
            output_gradient[a] = final_outputs[a] -  expected_outputs[a];
        }
        //Gradient of the bias:
        for(int a = 0 ; a < 10 ; a++)
        {
            gradients_of_biases_of_output_layer[a] = gradients_of_biases_of_output_layer[a] + output_gradient[a];
        }
        //Gradient of the weights:    
        for(int a = 0 ; a < 10 ; a++)
        {
            for(int b = 0 ; b < 64 ; b++)
            {   
                gradients_of_weights_of_second_layer_to_output[a][b] = gradients_of_weights_of_second_layer_to_output[a][b] + (output_gradient[a] * result_of_second_layer[b]);
            }
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //Layer 2
        //Output error of layer 2
        for(int a = 0 ; a < 64 ; a++)
        {
            for(int b = 0 ; b < 10 ; b++)
            {
                gradient_of_the_second_layer[a] = gradient_of_the_second_layer[a] + (weights_of_second_layer_to_output[b][a]* output_gradient[b]);
                
            }
            if(pre_relu_results_of_the_second_layer[a] <= 0)
            {
                gradient_of_the_second_layer[a] = 0.0f;
            }
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //Output error for weights:
        for(int a = 0 ; a < 64 ; a++)
        {
            for(int b = 0 ; b < 128 ; b++)
            {
                gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b] = gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b] + (gradient_of_the_second_layer[a] * result_of_the_first_layer[b]);
            }
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //Gradient of the baises calculation:
        for(int a = 0 ; a < 64 ; a++)
        {
            gradients_of_the_baises_of_the_second_layer[a] = gradients_of_the_baises_of_the_second_layer[a] + gradient_of_the_second_layer[a];
        }
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //Layer 1:
        //Output gradient calculation:

        for(int a  = 0 ; a < 128 ; a++)
        {
            for(int b = 0 ; b < 64 ; b++)
            {
                gradient_of_the_first_layer[a] = gradient_of_the_first_layer[a] + (weights_of_first_layer_to_second_layer[b][a] * gradient_of_the_second_layer[b]);
            }
            if(pre_relu_results_of_the_first_layer[a] <= 0)
            {
                gradient_of_the_first_layer[a] = 0.0f;
            }
        }
        
        //Weights calulation:

        for(int a  = 0 ; a < 128 ; a++)
        {
            for(int b = 0 ; b < 864 ; b++)
            {
                gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b] = gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b] + (converted_binary_drawing_from_file[b/24][b%24] * gradient_of_the_first_layer[a]);
            }
        }
        
        //Baises calulation:

        for(int a = 0 ; a < 128 ; a++)
        {
            gradient_of_the_biases_of_first_layer[a] = gradient_of_the_biases_of_first_layer[a] + gradient_of_the_first_layer[a];
        }

        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
        //End of Backprop
        //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Finalizing outputs:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Output Layer:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int i = 0 ; i < 10 ; i++)
    {
        gradients_of_biases_of_output_layer[i] = gradients_of_biases_of_output_layer[i]/1000.0f;
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 10 ; a++)
    {
        for(int b = 0 ; b < 64 ; b++)
        {
            gradients_of_weights_of_second_layer_to_output[a][b] = gradients_of_weights_of_second_layer_to_output[a][b]/1000.0f;
        }
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Layer 2:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 64 ; a++)
    {
        for(int b = 0 ; b < 128 ; b++)
        {
            gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b] = gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b]/1000.0f;
        }
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 64 ; a++)
    {
        gradients_of_the_baises_of_the_second_layer[a] = gradients_of_the_baises_of_the_second_layer[a]/1000.0f;
    }
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //Layer 1:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    for(int a = 0 ; a < 128 ; a++)
    {
        for(int b  = 0 ; b < 864 ; b++)
        {
            gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b] = gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b]/1000.0f;
        }
    }
    for(int a = 0 ; a < 128 ; a++)
    {
        gradient_of_the_biases_of_first_layer[a] = gradient_of_the_biases_of_first_layer[a]/1000.0f;
    }


    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
    //End of results:
    //*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//
}

int update_weights_and_baises()
{
    //first_layer
    
    //weights:
    for(int a = 0 ; a < 128 ; a++)
    {
        for(int b = 0 ; b < 864 ; b++)
        {
            input_layer_to_first_layer_weights[a][b] = input_layer_to_first_layer_weights[a][b] - (gradient_of_the_weights_of_the_input_layer_to_first_layer[a][b] * learning_rate);
        }
    }

    //baises:
    for(int a = 0 ; a < 128 ; a++)
    {
        baises_of_the_first_layer[a] = baises_of_the_first_layer[a] - (gradient_of_the_biases_of_first_layer[a] * learning_rate);  
    }

    //second layer:

    //weights:
    for(int a = 0 ; a < 64 ; a++)
    {
        for(int b = 0 ; b < 128 ; b++)
        {
            weights_of_first_layer_to_second_layer[a][b] = weights_of_first_layer_to_second_layer[a][b] - (gradients_of_the_weights_of_the_first_layer_to_second_layer[a][b] * learning_rate);
        }
    }

    //baises:
    for(int a = 0 ; a < 64 ; a++)
    {
        baises_of_second_layer[a] = baises_of_second_layer[a] - (gradients_of_the_baises_of_the_second_layer[a] * learning_rate);
    }
    
    //Ouput layer:

    //weights:
    for(int a = 0 ; a < 10 ; a++)
    {
        for(int b = 0 ; b < 64 ; b++)
        {
            weights_of_second_layer_to_output[a][b] = weights_of_second_layer_to_output[a][b] - (gradients_of_weights_of_second_layer_to_output[a][b] * learning_rate);
        }
    }

    //baises:
    for(int a = 0 ; a < 10 ; a++)
    {
        biases_of_output_layer[a] = biases_of_output_layer[a] - (gradients_of_biases_of_output_layer[a] * learning_rate);
    }
}

int save_to_file()
{
    weights_and_biases = fopen("ai_stuff\\neural_network_weights_and_biases.bin" , "wb");
    //input layer:
    
    //weights:
    for(int a = 0 ; a < 128 ; a++)
    {
        for(int b = 0 ; b < 864 ; b++)
        {
            float val = input_layer_to_first_layer_weights[a][b];
            fwrite(&val , 4 , 1 , weights_and_biases);
        }
    }

    //baises:
    for(int a = 0 ; a < 128 ; a++)
    {
        float val = baises_of_the_first_layer[a];
        fwrite(&val , 4 , 1 , weights_and_biases);
    }
    //second layer:
    
    //weights:
    for(int a = 0 ; a < 64 ; a++)
    {
        for(int b = 0 ; b < 128 ; b++)
        {
            float val = weights_of_first_layer_to_second_layer[a][b];
            fwrite(&val , 4 , 1 , weights_and_biases);
        }
    }

    //baises:
    for(int a = 0 ; a < 64 ; a++)
    {
        float val = baises_of_second_layer[a];
        fwrite(&val , 4 , 1 , weights_and_biases);
    }
    //ouput layer:
    
    //weights:
    for(int a = 0 ; a < 10 ; a++)
    {
        for(int b = 0 ; b < 64 ; b++)
        {
            float val = weights_of_second_layer_to_output[a][b];
            fwrite(&val , 4 , 1 , weights_and_biases);
        }
    }

    //baises:
    for(int a = 0 ; a < 10 ; a++)
    {
        float val = biases_of_output_layer[a];
        fwrite(&val , 4 , 1 , weights_and_biases);
    }
    
    fseek(weights_and_biases , 0 , SEEK_END);
    weights_and_biases_file_size = ftell(weights_and_biases);
    fseek(weights_and_biases , 0 , SEEK_SET);
    printf("Size of file %ld , Expected : 478504\n" , weights_and_biases_file_size);
    fclose(weights_and_biases);
}

int main()
{
    printf("Ai trainer....\n");
    initialize_weights_and_biases();
    // cost_function();
    // for(int i = 0 ; i < 500 ; i++)
    // {
    //     printf("%d\n" , i);
    //     back_propagation();
    //     update_weights_and_baises();
    //     //cost_function();
    // }
    //cost_function();
    // save_to_file();
    convert_txt_to_binary(10 , 8);
    forward_propagation();
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