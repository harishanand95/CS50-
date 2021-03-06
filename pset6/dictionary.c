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
#include "dictionary.h"
#include <ctype.h>
#define HASH_TABLE 143093
struct node* hashset[HASH_TABLE] = {NULL} ;

unsigned int word_count = 0;

  unsigned long hashfunction(const char *str)
  {
     unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_TABLE;
  }
  



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
     
  unsigned long hashval;
  struct node* cursor;

  char lowerword[strlen(word)+1];
   strcpy(lowerword,word);
  for(int i = 0, n = strlen(word); i < n; i++) 
    {
      lowerword[i] = tolower(word[i]);
    }
  hashval = hashfunction(lowerword);
  cursor = hashset[hashval];
  
  if(cursor == NULL)
   return false;
   
  do
    {
      if(strcmp(cursor->word,lowerword) == 0)
	{
	    return true;
	}
      else if(cursor->next == NULL)
	{
	    return false;
	    
	}
	cursor = cursor->next;
    }while(cursor != NULL);
return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
  
bool load(const char* dictionary)
{
    
  unsigned long hashval;
  
  FILE *fp = fopen(dictionary,"r");
  if (fp == NULL)
    {
      printf("Can't open the file %s.\n",dictionary);
      return -1;
    }  
  else
    {
      while(feof(fp)== 0)
	  {  
          struct node* new = malloc(sizeof(node));
          fgets(new->word, LENGTH+2, fp);
	  new->word[strlen(new->word)-1] = '\0';
	  new->next = NULL;
	  hashval = hashfunction(new->word);
	   
	  if(hashset[hashval] == NULL)
	    {
	      new->next = NULL;
	      hashset[hashval] = new;
	      word_count++;
	    }
	  else
	    {
	      struct node* cursor;
	      cursor = hashset[hashval]; 
	      while(cursor->next != NULL)  
	      {
    		  cursor = cursor->next;
	      }
	      cursor->next = new;
	      word_count++;
          new->next = NULL;                                     
        } 
          
	    }
	    word_count--;
      fclose(fp);
      return true;
   } 
  return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  if(load)
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
  if(load)
    {
      for(int i = 0;i < HASH_TABLE; i++)
	{
	  node* cursor;
	  node* temp;

	  //continue with the next i
	  if(hashset[i] == NULL )
	    continue;
	 
	  cursor = hashset[i];
	  //1 element deletion
	  if(cursor->next == NULL)
	    {
	      temp = cursor;
	      free(temp);
	    }  
	  else if(cursor->next != NULL)  //more than one element
	    {
	      for(int j = 0; cursor->next != NULL; j++)// each previous element deleted
		{
		  temp = cursor;
		  cursor = cursor->next;
		  free(temp);                                         
		}
	      //last element deleted
	      if (cursor->next == NULL)
		{
		  temp = cursor;
		  free(temp);
		} 
	    } 
	}
      return true;
    } 
  return false;
}
