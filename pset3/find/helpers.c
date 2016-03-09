/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0) return false; 

    int lo = 0;
    int hi = n - 1;
    while (lo <= hi) 
    {
        int mid = lo + (hi - lo) / 2;
        if      (value < values[mid]) hi = mid - 1;
        else if (value > values[mid]) lo = mid + 1;
        else return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int tmp;
    int min;

    for (int j = 0; j < n; j++)
    {
        min = values[j];

        for (int i = j; i < n; i++)
        {
            if (values[i] < min)
            {
                tmp = min;
                min = values[i];
                values[i] = tmp;
            }
        }
        values[j] = min;
    }
    return;
}
