// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 30000;

// Hash table
node *hashtab[N];

int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char tmp[LENGTH + 1];
    int l = strlen(word);
    for (int i = 0; i < l; i++)
    {
        tmp[i] = tolower(word[i]);
    }
    tmp[l] = '\0';
    int k = hash(tmp);
    if (hashtab[k] == NULL)
    {
    return false;
    }
    node* cursor = hashtab[k];
    while (cursor != NULL)
    {
        if (strcmp(tmp, cursor->word) == 0)
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
   unsigned int hash = 0;
   for (int i = 0, n = strlen(word); i < n; i++)
   {
       hash = (hash << 1) ^ word[i];
   }
   return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could Not Open File %s.\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s\n", word) != EOF)
    {
        counter++;
        node* new_entry = malloc(sizeof(node));
        strcpy(new_entry->word, word);
        int k = hash(word);

        if (hashtab[k] == NULL)
        {
            hashtab[k] = new_entry;
            new_entry->next = NULL;
        }
        else
        {
            new_entry->next = hashtab[k];
            hashtab[k] = new_entry;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int k = 0;
    while (k < N)
    {
        if (hashtab[k] == NULL)
        {
            k++;
        }
        else
        {
            while (hashtab[k] != NULL)
            {
                node* cursor = hashtab[k];
                hashtab[k] = cursor->next;
                free(cursor);
            }
            k++;
        }
    }
    return true;
}
