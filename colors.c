/*
NAMEL colors.c
PURPOSE to allow for simplistic color change for output strings in the replace program.
AUTHOR: Lachlan Murray (19769390)
*/

#include <stdio.h>
#include <string.h>
#include "compare.h"
#include "macros.h"

void colors(char* colourIn, char format, char* colourOut)
{
    char* colOut;

    if(format == 'f')   /*font colour change*/
    {
        if(colCompare(colourIn, "red") == TRUE)
        {
            colOut = "\33[0;31m";
        }
        else if(colCompare(colourIn, "green") == TRUE)
        {
            colOut = "\33[0;32m";
        }
        else if(colCompare(colourIn, "yellow") == TRUE)
        {
            colOut = "\33[0;33m";
        }
        else if(colCompare(colourIn, "blue") == TRUE)
        {
            colOut = "\33[0;34m";
        }
        else if(colCompare(colourIn, "magenta") == TRUE)
        {
            colOut = "\33[0;35m";
        }
        else if(colCompare(colourIn, "cyan") == TRUE)
        {
            colOut = "\33[0;36m";
        }
    }    
    
    if(format == 'b')   /*background colour change*/
    {
        if(colCompare(colourIn, "red") == TRUE)
        {
            colOut = "\33[41m";
        }
        else if(colCompare(colourIn, "green") == TRUE)
        {
            colOut = "\33[42m";
        }
        else if(colCompare(colourIn, "yellow") == TRUE)
        {
            colOut = "\33[43m";
        }
        else if(colCompare(colourIn, "blue") == TRUE)
        {
            colOut = "\33[44m";
        }
        else if(colCompare(colourIn, "magenta") == TRUE)
        {
            colOut = "\33[45m";
        }
        else if(colCompare(colourIn, "cyan") == TRUE)
        {
            colOut = "\33[46m";
        }
    }    
    
    if(format == 'u')   /*underlined colour change*/
    {
        if(colCompare(colourIn, "red") == TRUE)
        {
            colOut = "\33[4;31m";
        }
        else if(colCompare(colourIn, "green") == TRUE)
        {
            colOut = "\33[4;32m";
        }
        else if(colCompare(colourIn, "yellow") == TRUE)
        {
            colOut = "\33[4;33m";
        }
        else if(colCompare(colourIn, "blue") == TRUE)
        {
            colOut = "\33[4;34m";
        }
        else if(colCompare(colourIn, "magenta") == TRUE)
        {
            colOut = "\33[4;35m";
        }
        else if(colCompare(colourIn, "cyan") == TRUE)
        {
            colOut = "\33[4;36m";
        }
    }

    strcpy(colourOut, colOut); 
}
