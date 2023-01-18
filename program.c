/*
NAME: program.c
PURPOSE: to provide a search-and-replace program for Strings, with a fancy colour-coded display.
AUTHOR: Lachlan Murray (19769390)
LAST MOD:
*/

#include <stdio.h>
#include <string.h>     /*str*/
#include <stdlib.h>     /*system*/
#include <unistd.h>     /*sleep*/
#include <ctype.h>      /*tolower*/
#include "colors.h"     /*coloring*/
#include "macros.h"     /*true and false*/
#include "replace.h"    /*replace*/
#include "compare.h"    /*comparisons*/

int main(int argc, char** argv)
{
    /*variable/pointer declarations*/
    char *inString, *cpyString, *searchString, *replaceString, *colourS, *colourR, *colOutRep, *colOutNf, *colOutBoldReplaced, *underSearchString, *underReplaceString;
    int i = 0, j, l = 0, m = 0;     /*loop indexes*/
    int cursor = i;                 /*cursor for moving through sentence*/
    int replaced = FALSE;           /*boolean to know when a replacement has occurred*/

    /*check for correct number of arguments*/
    if (argc == 6)
    {
        /*
        ALLOCATE STRINGS
        */
        inString = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));         /*The string to read through, allocated a number of char equal to the length of the input + 1 for the null terminator*/
        strncpy(inString, argv[1], strlen(argv[1]));
        inString[strlen(argv[1])] = '\0';                                       /*adding null terminator to heap-allocated string*/
        
        cpyString = (char*)malloc(strlen(inString) * sizeof(char));             /*A copy of inString, used in the final output of the program where it displays the original, unedited string*/
        strcpy(cpyString, inString);
        
        searchString = (char*)malloc((strlen(argv[2]) + 1) * sizeof(char));     /*The String term to search for in inString*/
        strncpy(searchString, argv[2], strlen(argv[2]));
        searchString[strlen(argv[2])] = '\0';

        replaceString = (char*)malloc((strlen(argv[3]) + 1) * sizeof(char));    /*The String term to replace searchString with in inString*/
        strncpy(replaceString, argv[3], strlen(argv[3]));
        replaceString[strlen(argv[3])] = '\0';        

        colourS = (char*)malloc((strlen(argv[4]) + 1) * sizeof(char));          /*Colour option one*/
        strncpy(colourS, argv[4], strlen(argv[4]));
        colourS[strlen(argv[4])] = '\0';        

        colourR = (char*)malloc((strlen(argv[5]) + 1) * sizeof(char));          /*Colour option two*/
        strncpy(colourR, argv[5], strlen(argv[5]));
        colourR[strlen(argv[5])] = '\0';        

        colOutRep = (char*)malloc(20 * sizeof(char));                           /*Coloured string "replaced", allocated enough space for escape code either side of the string "replaced" and the null terminator*/
        colors(colourR, 'f', colOutRep);                                        /*strcpy's the colour escape code into the beginning of colOutRep String*/
        strcat(colOutRep, "replaced\33[0m");                                    /*appends string and exit code onto colOutRep*/

        colOutNf = (char*)malloc(22 * sizeof(char));                            /*Coloured string "not found", allocated enough space for escape code either side of the string "not found" and the null terminator*/
        colors(colourS, 'f', colOutNf);
        strcat(colOutNf, "not found\33[0m");

        colOutBoldReplaced = (char*)malloc((10 + strlen(replaceString)) * sizeof(char));    /*Coloured and highlighted replaceString, used for inserting into the inString and used for the final output strings, where it is searched for in the final replaced sentence and replaced with the term underlined instead*/
        colors(colourR, 'b', colOutBoldReplaced);
        strcat(colOutBoldReplaced, replaceString);
        strcat(colOutBoldReplaced, "\33[0m");
     
        underSearchString = (char*)malloc((12 + strlen(searchString)) * sizeof(char));      /*Coloured and underlined searchString, used for the final output strings, where it is inserted in the place of searchString in cpyString*/
        colors(colourS, 'u', underSearchString);
        strcat(underSearchString, searchString);
        strcat(underSearchString, "\33[0m");

        underReplaceString = (char*)malloc((12 + strlen(replaceString)) * sizeof(char));
        colors(colourR, 'u', underReplaceString);
        strcat(underReplaceString, replaceString);
        strcat(underReplaceString, "\33[0m");

        /*program iterates through each element in the inString (until strlen(searchString)-1 elements are left at the end (e.g. has reached the end)), 
        checking to see if the current char is the first char of the search term. If so, will call compare and if the strings match, compare() calls replace() to perform replacement, altering the original inString.*/
        while (i < (strlen(inString) - (strlen(searchString) - 1)))
        {
            /*
            CLEAR SCREEN
            */
            system("clear");
    
            /*
            COMPARISON (AND THEN REPLACEMENT if needed)
            */
            replaced = compare(i, inString, searchString, colOutBoldReplaced);
    
            /*
            OUTPUT
            */
            printf("replace: %s -> %s\n\n", searchString, replaceString);
    
            printf("%s\n", inString);
    
            for(j = 0; j < cursor; j++)  /*spacing for pointing arrow*/
            {            
                printf(" ");
            }
            printf("^\n");  /*arrow pointing at inString*/ 
    
            for(j = 0; j < cursor; j++)  /*spacing for words below arrow*/
            {            
                printf(" ");
            }
            if (replaced == TRUE)
            {
                /*coloured "replaced" output*/
                printf("%s", colOutRep);
                printf("\n");
            }
            else if (i == (strlen(inString) - strlen(searchString)))    /*end of the program, program does not currently reach here for some reason*/
            {
                printf("\33[0;33mEND\33[0m\n");
                
                sleep(1);
    
                system("clear");            
    
                /*run a compare and replace for the original term (stored in cpyString at the beginning) to replace with the string with underlined search terms*/
                while (l < (strlen(cpyString) - (strlen(searchString) - 1)))
                {
                    replaced = compare(l, cpyString, searchString, underSearchString);
                    /*increment loop index*/
                    if (replaced == TRUE)
                    {
                        l = l + strlen(underSearchString);  /*move index to past the replaced chunk (with color format)*/
                        replaced = FALSE;   /*reset replaced bool for next iteration*/
                    }
                    else
                    {
                        l++;
                    }
                }
                printf("%s", cpyString);
                printf("\n");
    
                /*do the same for the replaced string, underlining the replaced terms*/
                while (m < (strlen(inString) - (strlen(replaceString) - 1)))
                {
                    replaced = compare(m, inString, colOutBoldReplaced, underReplaceString);
                    /*increment loop index*/
                    if (replaced == TRUE)
                    {
                        m = m + strlen(underReplaceString);  /*move index to past the replaced chunk (with color format)*/
                        replaced = FALSE;   /*reset replaced bool for next iteration*/
                    }
                    else
                    {
                        m++;
                    }
                }
                printf("%s", inString);
                printf("\n");

                i = strlen(inString);   /*set original loop index to out of bounds so program ends here*/
            }
            else 
            {
                /*coloured "not found" output*/
                printf("%s", colOutNf);
                printf("\n");
            }
    
            /*
            CHANGE POSITION of cursor if a replacement has occured
            */
            if (replaced == TRUE)
            {
                i = i + strlen(colOutBoldReplaced);  /*move index to past the replaced chunk (with color format)*/
                cursor = i - 9;    /*move cursor to past the replaced chunk (without color format chars which arent output to the terminal)*/
                replaced = FALSE;   /*reset replaced bool for next iteration*/
            }
            else
            {
                i++;
                cursor++;
            }
    
            /*
            ONE SECOND SLEEP BETWEEN CHARACTER CHECKS
            */
            sleep(1);
        }
    }
    else
    {
        printf("Error, the program requires 5 parameters as such: ./program <String_to_search_through> <String_to_search_for> <String_to_replace_with> <Colour_option_one> <Colour_option_two>\n");
    }
 
    /*
    FREE HEAP-ALLOCATED MEMORY
    */
    free(inString);
    inString = NULL;
    free(cpyString);
    cpyString = NULL;
    free(searchString);
    searchString = NULL;
    free(replaceString);
    replaceString = NULL;
    free(colourS);
    colourS = NULL;
    free(colourR);   
    colourR = NULL;
    free(colOutRep);
    colOutRep = NULL;
    free(colOutNf);
    colOutNf = NULL;
    free(colOutBoldReplaced);
    colOutBoldReplaced = NULL;
    free(underSearchString);
    underSearchString = NULL;
    free(underReplaceString);
    underReplaceString = NULL;

    return 0;
}
