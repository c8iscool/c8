#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do 
    {
        n = get_int("What do you want the height to be?\n");
    }
    while (n > 8 || n < 1);
    //makes sure that height input is between 1 and 8
    
    for (int i = 0; i < n; i++)
        //i is the number of rows, also the number of hashes (j) but not using j yet because that's later
    {
        for (int k = n - i - 1; k > 0; k--)
            //k is the number of dots, each line should be the height minus the hashes
        {
            printf(".");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }       
}
