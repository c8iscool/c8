// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 27;
int wordcounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int bucket = hash(word);
    node *cursor = table[bucket];

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

// Hashes word to a number
unsigned int hash(const char *word)
{
    int x = tolower(word[0]) - 97;
    return x;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char buffer[LENGTH + 1];

    FILE *dictpointer = fopen(dictionary, "r");
    if (dictpointer == NULL)
    {
        return false;
    }

    while ((fscanf(dictpointer, "%s", buffer)) != EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word, buffer);
        int bucket = hash(n->word);
        n->next = table[bucket];
        table[bucket] = n;
        wordcounter++;
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
        node *cursor = table[i];
        while (table[i] != NULL)
        {
            cursor = table[i];
            table[i] = cursor->next;
            free(cursor);
        }
    }
    return true;
}