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
// A little bit of experimentation to drive the numbers down, to drive efficiency of both load and check.
const unsigned int N = 30000;

// Hash table
node *hashtab[N];

int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Create temporary array of characters of size LENGTH + 1. The increase in 1 allows storage of NUL character at the end of the word.
    char tmp[LENGTH + 1];
    //Initialise integer l to the length of the word.
    int l = strlen(word);
    //Copy contents of word array to temporary array, whilst converting all letters in word array to lower case.
    for (int i = 0; i < l; i++)
    {
        tmp[i] = tolower(word[i]);
    }
    //Assign the NUL character to the last element of the temporary array.
    tmp[l] = '\0';
    //Initialise integer k to store the output of the hash function when run over the temporary array.
    int k = hash(tmp);

    if (hashtab[k] == NULL)
    {
        return false;
    }
    //Declare a pointer cursor of type node and initialise to the kth element of the hashtable.
    node *cursor = hashtab[k];
    //While the cursor pointer does not point at NULL, if comparing the temporary array and the word in the node at which the cursor is pointing do match, return true.
    while (cursor != NULL)
    {
        if (strcmp(tmp, cursor->word) == 0)
        {
            return true;
        }
        //If the comparison does not reveal the word, the cursor pointer is pointed to the next element of the next node.
        cursor = cursor->next;
    }
    //If the cursor moves through the entire linked list pointed to from the kth element of the array and reaches a pointer to NULL without finding a matched word, the word does not exist in the dictionary.
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
    //Loads file 'dictionary' and allows reading. Declare a pointer of type file to the FILE.
    FILE *file = fopen(dictionary, "r");
    //Checks to ensure file has opened successfully, if not, returns false.
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could Not Open File %s.\n", dictionary);
        return false;
    }
    //Create an array of characters called word of size LENGTH + 1.
    char word[LENGTH + 1];
    //Use fscanf to read strings of each word until the end of the file.
    while (fscanf(file, "%s\n", word) != EOF)
    {
        //Increase counter to reflect new word found.
        counter++;
        //Declare pointer 'new_entry' of type node to create new node and allocate memory of the size of a 'node' to store word data.
        node *new_entry = malloc(sizeof(node));
        //Copy string from word and copies it to the word element of the new node.
        strcpy(new_entry->word, word);
        //Declare integer k to represent return of hash function over word.
        int k = hash(word);
        //If there is no current pointer at the kth element of the hashtable, assign the new entry node to the kth element and set the pointer at the end of the linked list to NULL
        if (hashtab[k] == NULL)
        {
            hashtab[k] = new_entry;
            new_entry->next = NULL;
        }
        else
        //If there is a pointer present at the kth element of the hashtable the new pointer to next is pointed at the head of the linked list.
        {
            new_entry->next = hashtab[k];
            //and the new node is assigned to the kth element of the hashtable.
            hashtab[k] = new_entry;
        }
    }
    //Once the file is read, it is closed.
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
    //Declare integer k and set to zero.
    int k = 0;
    //Perform contents of while loop whilst k is less than N, N being the number of buckets.
    while (k < N)
    {
        //If there are no linked lists pointed to from the kth value, k++.
        if (hashtab[k] == NULL)
        {
            k++;
        }
        else
        {
            //If there are list pointed to from the kth value.
            while (hashtab[k] != NULL)
            {
                //Create new pointer cursor to node and point it to the head of the linked list.
                node *cursor = hashtab[k];
                //Point the head of the list at the next item in the linked list.
                hashtab[k] = cursor->next;
                //free the memory currently pointed to by the cursor.
                free(cursor);
            }
            //k++
            k++;
        }
    }
    return true;
}
