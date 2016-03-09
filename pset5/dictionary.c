/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"
#define SIZE 18500

node* hash_table[SIZE] = {NULL};
int words = 0;

/*
 * Returns true if word is in dictionary else false.
 */

bool check(const char* word)
{
  int index = hash(word);

  if (hash_table[index] == NULL)
    return false;

  if (strcasecmp(hash_table[index]->word, word) == 0)
    return true;

  node* search = hash_table[index]->next;
  if (search != NULL)
  {
    while (search != NULL)
    {   
      if (strcasecmp(search->word, word) == 0)
        return true;
      search = search->next;
    }
    return false;
  }
  else
    return false;
}


/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dict)
{   
  FILE* dictionary = fopen(dict, "r");
  if (dictionary == NULL)
  {
    printf("Could not open file %s.\n", dict);
    return 1;
  }

  while (!(feof(dictionary)))
  {
    node* n = malloc(sizeof(node));
    if(n == NULL)
    {
      fclose(dictionary);
      return false;
    }

    fscanf(dictionary, "%s", n->word);
    int index = hash(n->word);

    if (hash_table[index] == NULL)
    {
      hash_table[index] = n;
      n->next = NULL;
    }
    else if(hash_table[index] != NULL)
    {
      n->next = hash_table[index]->next;
      hash_table[index]->next = n;
    }
    words++;
  }
  fclose(dictionary);
  return true;
}

int hash(const char* word)
{
  int n = strlen(word);
  // FNV Hash
  //unsigned h = 2166136261;
  unsigned h = 0;
  int i;

  for (i = 0; i < n; i++)
  {
      // Hashing example alogirithms from:
      // http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx

      // Rotating hash       
      // h = (h << 4) ^ (h >> 28) ^ tolower(word[i]);
      
      // Modified Bernstein
      //h = 33 * h ^ tolower(word[i]);

      // Shift-Add-XOR hash
      //h ^= (h << 5) + (h >> 2) + tolower(word[i]);

      // FNV hash
      //h = (h * 16777619) ^ tolower(word[i]);
      
      // One-at-a-Time hash
      h += tolower(word[i]);
      h += (h << 10);
      h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);
  return h % SIZE;
}

/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int size(void)
{
  return words - 1;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool unload(void)
{
  // iterate over the whole hash table
  for(int index = 0; index < SIZE; index++)
  {
    // if current hash index is not empty free all elements in the index
    if(hash_table[index] != NULL)
      freehash(hash_table[index]);
  }
  return true;
}

/*
 * void
 * freehash(node *next)
 *
 * Frees all allocated memory within the hash table
 */

void freehash(node* next)
{
  // if the current node isn't the last element, free the next node first
  if(next->next != NULL)
    freehash(next->next);
  free(next);
}
