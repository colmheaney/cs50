/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define INPUT "card.raw"
#define BLOCK 512

typedef uint8_t  BYTE;

int main (void)
{
    //open input file
    FILE *inptr = fopen (INPUT, "r");
    if (inptr == NULL)
    {
        printf ("Could not open %s.\n", INPUT);
        return 1;
    } 

    //define buffer and filename to read first block into and read in first block
    char filename[10] = "./000.jpg";            
    BYTE buffer[BLOCK];
    fread (buffer, sizeof(BYTE), BLOCK, inptr);

    int i = 0;
    while (!feof(inptr))
    {   
        //check for jpeg headers
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {

            //if jpeg found open output file
            sprintf(filename, "./%.3d.jpg", i);
            FILE *outptr = fopen (filename, "w");
            if (outptr == NULL)
            {
                printf ("Could not open %s.\n", filename);
                return 1;
            } 

            //write to output and read in next block. check that block is not start of new jpeg or if eof reached
            do{
                fwrite (buffer, sizeof(BYTE), BLOCK, outptr);
                fread (buffer, sizeof(BYTE), BLOCK, inptr);
            }while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) && !feof(inptr));

            //if new jpg found close output file and move to next image
            fclose (outptr);
            i++;    
        }
        else 
            fread (buffer, sizeof(BYTE), BLOCK, inptr);
    } 
    fclose (inptr);
}
