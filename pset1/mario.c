#include <stdio.h>
#include <cs50.h>

int main(void) {

    int height;

    do  {

        //ask user for input
        printf("Height:\n");

        //get the user input
        height = GetInt();

    } while (height < 0 || height > 23);

    for (int j = 0; j < height; j++) {

        for (int i = 0; i < (height - 1 - j); i++) {
            printf(" ");
        }   
        for (int i = 0; i < (j + 2); i++)
        {
            printf("#");
        }
        printf("\n");
    }

}
