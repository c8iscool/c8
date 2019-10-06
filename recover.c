#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // checks to make sure that there is only one command-line argument (name of image)
    {
        printf("Input name of forensic image.");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    unsigned char buffer[512]; // temporary storage that has 512 bytes
    int image_counter = -1; // counts the number of pictures found
    char filename[8]; // name of the file has to have " xxx.jpg \n " so 7+1 characters
    FILE *output; // the output that copies whatever has been stored

    while (fread(buffer, 1, 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // checks if it has the initial 3 characters that characterize a jpeg file
        {
            if (image_counter != -1) // if this is a new image found and it's not the first image found, close the image that has been opened before
            {
                fclose(output);
            }

            image_counter++; // every time an image is found, the counter increases
            sprintf(filename, "%03i.jpg", image_counter);
            output = fopen(filename, "w+");
        }

        if (image_counter != -1)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
}
