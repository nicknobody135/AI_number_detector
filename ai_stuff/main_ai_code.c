#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "../game_setup/game_setup.h"

//input 864
//first layer 1024
//second layer 1024
//third layer 768
//fourth layer 512
//fifth layer 256
//output layer 10

//*------------------------------------------------------------------------------------------------------------*//
//Function pre def

void initialize_weights_and_biases();

void forward_propagation(bool display_results_or_not);

//*------------------------------------------------------------------------------------------------------------*//
//Functions:


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
                    weighted_sums[b] += (forward_prop_weights[(b*864)+c] * what_boxes_in_the_middle_are_on[c/24][c%24]);
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
            prediction = 0;
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
            

            for(int c = 0 ; c < 10 ; c++)
            {
                final_outputs[c] = (expf(forward_prop_results[c+3584]-max)/sum);
                if(display_results_or_not == 1)
                {
                    printf("%d - Ans : %f\n" , c , final_outputs[c]);
                }
            }
            
            if(display_results_or_not == 1)printf("Prediction : %d\n" , prediction);
        }
    }

    //*------------------------------------------------------------------------------------------------------------*//

}


// int main()
// {
//     printf("Ai trainer....\n");
//     initialize_weights_and_biases();

//     convert_txt_to_binary(0 , 8 , 4);
//     forward_propagation(1);

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

    //printf("Sucessful Run\n");

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

    //return 0;
//}