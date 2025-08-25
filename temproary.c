#include <stdio.h>
#include <windows.h>

int main(void) 
{
    char fruits[3][20];

    // Modify one string
    sprintf(fruits[1], "Blueberry");

    for (int i = 0; i < sizeof(fruits)/20;i++) {
        printf("%s\n", fruits[i]);
    }
    printf("%d\n" , sizeof(fruits)/20);

    return 0;
}