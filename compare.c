/*
NAME: compare.c
PURPOSE: to hold the functions for comparing strings
AUTHOR: Lachlan Murray (19769390)
*/

#include <stdio.h>
#include <ctype.h>  /*tolower*/
#include "replace.h"
#include "macros.h"

int compare(int i, char* inString, char* searchString, char* replaceString)
{
    int j = 0, temp = i, replaced = FALSE;

    /*running comparison*/
    if (tolower(inString[i]) == tolower(searchString[j]))
    {
        while ((tolower(inString[i]) == tolower(searchString[j]))&&(replaced != TRUE))
        {
            i++;    
            j++;    /*iterate through the string portions and compare each char*/
            
            if (searchString[j] == '\0')
            {
                /*set replaced bool to true for the main to know what to print*/
                replaced = TRUE;
            }
        }
        
        if (replaced == TRUE)   /*if the end of the replace string was reached (e.g. the whole string was found)*/
        {
            char* subStringSource = &inString[temp]; /*set a pointer to where in the inString the subString starts*/
            
            /*conditional compilation*/
            #ifdef INDEX
            printf("The Search term was found at index %d of the inString.\n", temp);
            #endif

            /*call replace function with all of the required details to replace with colour*/
            replace(inString, searchString, replaceString, subStringSource);
        }
    }

    return replaced;
}

int colCompare(char* colourIn, char* compareCol)
{
    int same = FALSE, i = 0;    
 
    if (tolower(colourIn[i]) == tolower(compareCol[i]))
    {
        while ((tolower(colourIn[i]) == tolower(compareCol[i]))&&(same != TRUE))
        {
            i++;    /*iterate through the string portions and compare each char*/
            
            if (compareCol[i] == '\0')   /*if the end of the colour string was reached*/
            {
                same = TRUE;
            }
        }
    }

    return same;
}

