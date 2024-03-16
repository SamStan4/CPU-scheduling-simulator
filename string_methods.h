#ifndef STRING_MOTHODS_H
#define STRING_METHODS_H

void initialize_string(char* string, char initializer, int size)
{
    int i = 0; 
    for (i = 0; i < size; ++i)
    {
        string[i] = initializer;
    }
}

void char_concatinate(char* dest, char new_end, int size)
{
    int i = 0;
    for (i = 0; (dest[i] != '\0') && (i < size); ++i); // puts us at the end of the string

    if (i < size)
    {
        dest[i] = new_end;
    }
}

#endif