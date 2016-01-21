/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   // implementing binary search algorithm
	int mid, last = n , first = 0;
	mid = (last + first)/2;
	while(first <= last)
	{
		
		if(	values[mid] == value)
		{
			return true;
		}
		if( values[mid] < value)
			first = mid + 1;
		else	
			last = mid - 1;	    
		mid = (last + first)/2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // selection sort O(n ^2)
	int i , j ,temp;

	for(i = 0 ; i < n; i++)
	{
		for(j = i + 1; j < n; j++)
		{
			    if( values[i] > values [j])
				{
					temp = values[i];
					values[i] = values[j];
					values[j] = temp;
				}
		}
	}
return;
}
