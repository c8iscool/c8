#include <stdbool.h>
#include <stdio.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./count INPUT\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int count = 0;
    while (true)
    {
        BYTE b;
        fread(&b, 1, 1, file);
        if (b > 129 && b < 192)
        if (feof(file))
        {
            break;
        }

        if ((b & 0xc0) != 0x80)
        {
            count++;
        }
    }
    printf("Number of characters: %i\n", count);
}
