#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#define NO_FILE_GIVEN_ERROR 1
#define TOO_MANY_FILES_GIVEN_ERROR 2
#define FILE_DOESNT_EXIST_ERROR 3

//***************************************************************************************************************************************************************//
//     function call        : error_thrower()
//     function description : this function will display error messages to the user
//     function inputs      : int, char*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void error_thrower(int error_code, char* message)
{
    printf("ERROR --> ");

    switch (error_code)
    {
        case NO_FILE_GIVEN_ERROR:
            printf("no file given");
        break;
        case TOO_MANY_FILES_GIVEN_ERROR:
            printf("too many files given for input");
        break;
        case FILE_DOESNT_EXIST_ERROR:
            printf("unable to find \"%s\"", message);
        break;
        default:
            printf("UNKNOWN ERROR");
        break;

    }
    printf("\n");
}

//***************************************************************************************************************************************************************//

#endif