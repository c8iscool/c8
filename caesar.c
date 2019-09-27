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
    string plaintext = get_string("plaintext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i])) // only applies shift to alphabetic characters
        {
            int x = plaintext[i];

            if (x >= 97 && x <= 122) // case 1: lowercase letters
            {
                x = x + key;

                if (x > 122)
                {
                    x = x - 26; // if shifted character goes outside of z, moves to the beginning of the alphabet by shifting ascii length of alphabet
                }
                plaintext[i] = x;
            }

            else if (x >= 65 && x <= 90) // case 2: uppercase letters
            {
                x = x + key;
                if (x > 90) // if shifted character goes past Z, moves back to the beginning of capital letter alphabet
                {
                    x = x - 26;
                }
                plaintext[i] = x; // both change the original component of the string to new shifted character
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
