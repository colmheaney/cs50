/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If argc is not equal to either 2 or 3 print the usage instrctions.
    // So if the user doesn't enter a number of random numbers, and doesn't enter
    // a seed then print the instructions
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Declare n and set it equal to argv[1]. Atoi takes the user input and makes
    // an interger out of a string. n is the number of random numbers to produce
    int n = atoi(argv[1]);

    // If a seed is provided get an interger from the string.
    // If no seed is provided seed rand with current system time
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // For the number of random numbers print the number returned from rand mod 65536
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
