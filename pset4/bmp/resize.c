/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy infile outfile integer\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    char *s = argv[1];
    
    int scale = atoi(s);
    if (!(scale >= 1 && scale <= 100))
    {
        printf("Usage: copy infile outfile integer\n");
        return 5;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER nbf;
    BITMAPINFOHEADER nbi;

    // header information and padding for new image
    nbi = bi;
    nbf = bf;
    nbi.biWidth = bi.biWidth * scale;
    int new_padding =  (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    nbi.biHeight = bi.biHeight * scale;
    nbi.biSizeImage = (nbi.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(nbi.biHeight);
    nbf.bfSize = nbi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - ((bi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {   
        for (int l = 0; l < scale; l++)
        { 
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                int m = 0;
                while (m < scale)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    m++;
                }
                
            }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // write padding to outfile
            for (int n = 0; n < new_padding; n++)
                fputc(0x00, outptr);
 
            int line = - (bi.biWidth) * sizeof(RGBTRIPLE) - padding;
            fseek(inptr, line, SEEK_CUR);
        }
        
        fseek(inptr, bi.biWidth * sizeof(RGBTRIPLE) + padding, SEEK_CUR);
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
