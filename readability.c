#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: \n");
    
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        letters++;
    // counts number of alphabetic characters in the string text
    }
    
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ' && isalpha(text[i + 1] != 0))
        words++;
    }    
    // counts number of spaces in the string, since there is one fewer space than #words words=1
    // checks that the next char after space is an alphabetic letter

    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!')
        sentences++;
    }
    
    float W = 100.0f / words;
    float L = (letters * W);
    float S = (sentences * W);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 16 && index >= 1)
    printf("Grade %i", index);
    
    if (index > 16)
    printf("Grade 16+");
    
    if(index < 1)
    printf("Before Grade 1");
        
}
