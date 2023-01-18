/*
NAME: replace.c
PURPOSE: holds the function to replace given substrings in a string.
AUTHOR: Lachlan Murray (19769390)
*/

#include <stdio.h>
#include <string.h>

void replace(char* inString, char* searchString, char* replaceString, char* subStringSource)
{
    /*shift the other characters in the inString located to the right of the pointer subStringSource (the insertion point) to the right or left depending on difference of length of search string and replace string*/
    memmove(subStringSource + strlen(replaceString), subStringSource + strlen(searchString), strlen(subStringSource) - strlen(searchString) + 1); /*+1 for null terminator*/

    /*insert string into position in inString pointed to by subStringSource (using memcpy (dest, src, size))*/
    memcpy(subStringSource, replaceString, strlen(replaceString));
}
