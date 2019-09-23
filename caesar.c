#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error.");
        return 1;
    }
    // makes sure that the user only inputs the name of the program and the key, total 2

    int key = atoi(argv[1]);
    //converts the key character number into an integer
    string plaintext = get_string("plaintext: \n");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i])) // only applies shift to alphabetic characters
        {
            char letter = plaintext[i];
            if (letter >= 'a' && letter <= 'z') // case 1: lowercase letters
            {
                letter = letter + key;

                if(letter > 'z')
                {
                    letter = letter - 'z' + 'a' - 1; // if shifted character goes outside of z, moves to the beginning of the alphabet by shifting ascii - (z-a) which is length of alphabet
                }
            plaintext[i] = letter;
            }
            else if (letter >= 'A' && letter <= 'Z') // case 2: uppercase letters
            {
                letter = letter + key;
                if (letter > 'Z') // if shifted character goes past Z, moves back to the beginning of capital letter alphabet
                {
                    letter = letter - 'Z' + 'A' - 1;
                }
            plaintext[i] = letter; // both change the original component of the string to new shifted character
            }
        }
    }
    printf("cipher text: %s \n", plaintext);
    return 0;
}
