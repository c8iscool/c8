// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

int main(void)
{
    return 0;
}
int wordcounter = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    int x = tolower(word[0]) - 97;
    return x;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* cursor = malloc(sizeof(node));
    int x = hash(word);
    cursor = table[x];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char buffer[LENGTH + 1];

    FILE* dictpointer = fopen(dictionary, "r");

    if(dictpointer == NULL)
    {
        return false;
    }

    while(true)
    {
        node *n = malloc(sizeof(node));

        if(n == NULL)
        {
            printf("error\n");
            return false;
        }
        while ((fscanf(dictpointer, "%s", buffer)) != EOF)
        {
            int bucket = hash(n->word);
            n->next = table[bucket];
            table[bucket] = n;
            wordcounter++;
        }
    }
    fclose(dictpointer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor;
        cursor = table[i];
        while (cursor)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
            return true;
        }
    table[i] = NULL;
    }
    return false;
}
