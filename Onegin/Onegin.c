/**
@mainpage Sort "Onegin" in alphabetical order, from the beginning and from the end of the lines.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

struct Line
{
    char * line_begin;
    int len;
};

///Error message.
const int ERROR = -1;

/**
@brief The function reads the text and sorts it.
*/
int do_program(FILE * file, const int mode);

/**
@brief Copy data from file to memory.
*/
char * copy_data(FILE * file, size_t f_size);

/**
@brief The function calculates file size (number of characters).
*/
size_t file_size(FILE * file);

/**
@brief The function counts the number of lines in the file.
*/
int count_lines(char *data);

/**
@brief The function converts read data, breaks into lines.
*/
int edit_data(struct Line * text, char * data);

/**
@brief The function sorts an array with strings.
*/
int sort_lines(struct Line * text, int n_lines, const int mode);

/**
@brief Comparison function for strings.
*/
int lines_cmp(const void * line_1, const void * line_2);

/**
@brief The function isplays sorted text to file.
*/
int print_text(struct Line * text, int n_lines, const char * output_name);

/**
@brief Compares strings from the end in alphabetical order.
*/
int reverse_lines_cmp(const void * line_1, const void * line_2);

/**
@brief Communication with the user.
*/
int user_interface(int * mode);

/**
@brief Checks input data.
*/
int data_checking(FILE * file, int mode);

/**
@brief Frees up memory and closes the data file.
*/
int free_memory(struct Line * text, char * data);

/**
@function
The main function prompts the user to enter the file name,\n
calls the functions for printing,\nsorting and outputting the file.
@return 1) ERROR = -1, if file was not found.
@return 2) 0 if program the program was successful
*/

int main()
{
    int mode = 0;
    user_interface(&mode);

    FILE * file = fopen("Onegin_eng.txt", "r");

    if (data_checking(file, mode) == ERROR)
    {
        printf("FILE IS NOT SORTED! Invalid sort mode entered or file was not found.");
        return ERROR;
    }

    int check =  do_program(file, mode);
    printf("Dictionary is ready.\n#By Konyk Mikhail, 06.10.18");
    return 0;
}

/**
@function
@param file - Pointer to read file;
@param mode - Mode - Sorting mode(1 or 2);
@return 0 - if program the program was successful.
*/

int data_checking(FILE * file, int mode)
{
    assert(file);

    if (file == 0)
    {
        printf("sadasdasd\n");
    }

    if(mode != 1  && mode != 2)
        return ERROR;
    else
        return 0;
}

/**
@function
@param file - Pointer to read file.
@return Number of characters in the file;
*/
size_t file_size(FILE * file)
{
    assert(file);
    size_t symbol_number = 0;

    fseek(file, 0, SEEK_END);
    symbol_number = ftell(file);
    fseek(file, 0, SEEK_SET);

    return symbol_number;
}

/**
@function
The function creates a copy of the file,\n
calculates its size, splits it into lines,\n
calculates the number of lines in it, sorts them.
@param file - Pointer to read file;
@param text - Array with pointers to strings;
@param data - Array - a copy of the file;
@param mode - Sorting mode(1 or 2);
@param n_lines - Pointer to the number of lines in the file;
@return 0 - if program the program was successful.
*/

int do_program(FILE * file, const int mode)
{
    assert(file);
    assert(mode == 1 || mode == 2);

    size_t f_size = file_size(file);

    char * data = copy_data (file, f_size);

    int n_lines = count_lines(data);

    struct Line * text = (struct Line *) calloc(n_lines + 1, sizeof(struct Line));


    edit_data(text, data);

    sort_lines(text, n_lines, mode);

    if (mode == 1)
        print_text(text, n_lines, "Sorted_file_from_Begin_of_strings.txt");
    else if (mode == 2)
        print_text(text, n_lines, "Sorted_file_from_End_of_strings.txt");
    free_memory(text, data);
    return 0;
}

/**
@function
Creates an array into which it copies the data of the file,\n
appends a '\ 0' at the end.
@param file - Pointer to read file;
@param f_size - File size.
@return data - Array - a copy of the file.
*/

char * copy_data(FILE * file, size_t f_size)
{
    assert(file);
    assert(f_size > 0);

    char * data = (char *) calloc(f_size + 1, sizeof(char));
    assert((data));


    int read_res = fread(data, sizeof(char), f_size, file);

    fclose(file);

    return data;
}

/**
@function
@param file - Pointer to read file;
@return n_lines - Number of lines in file.
*/
int count_lines(char * data)
{
    assert (data);
    int n_lines = 1;

    int symbol = 0;
    char* data_save = data;
    while (true)
    {
        symbol = *data_save;
        data_save++;

        if (symbol == '\n')
            n_lines++;
        else if (symbol == 0)
         break;
    }
    return n_lines;
}

/**
@function
The function replaces '\ n' with
 '\ 0' in the array with file data,
@param text - Array with pointers to strings;
@param data - Array - a copy of the file;
@return 0 - if program the program was successful.
*/

int edit_data(struct Line * text, char * data)
{
    assert(text);
    assert(data);

    text[0].line_begin = data;
    int i = 0;

    char *s = 0;
    for(s = strchr(data, '\n'); s != NULL ; s = strchr(s + 1, '\n'))
    {
        ++i;
        *s = 0;
        text[i].line_begin = s + 1;
        text[i - 1].len = s - text[i-1].line_begin;
    }
    return 0;
}

/**
@function
The function sorts the lines in the file in alphabetical order,\n
ignoring punctuation marks. Uses standard "qsort" sorting.
@param text - Array with pointers to strings;
@param n_lines - Number of lines in file.
@return 0 - if program the program was successful.
*/

int sort_lines(struct Line * text, int n_lines, const int mode)
{
    assert (text != NULL);
    assert(n_lines >= 0);

    if (mode == 2)
        qsort(text, n_lines, sizeof(struct Line), reverse_lines_cmp);

    else if (mode == 1)
        qsort(text, n_lines, sizeof(struct Line), lines_cmp);

    else printf("FILE IS NOT SORTED! Invalid sort mode entered");

    return 0;
}

/**
@function
Comparison function for strings, ignoring punctuation.
@param string_1 - Pointer to the first line;
@param string_2 - Pointer to the second line;
@return returns a negative integer value if
the first argument is less than the second,\n
a positive integer value if the first
argument is greater than the second\n
and zero if the arguments are equal.
*/

int lines_cmp(const void * string_1, const void * string_2)
{
    assert(string_1 != NULL);
    assert(string_2 != NULL);

    char * line_1 = (*(struct Line *) string_1).line_begin;
    char * line_2 = (*(struct Line *) string_2).line_begin;


    int len_1 = (*(struct Line *) string_1).len;
    int len_2 = (*(struct Line *) string_2).len;

    int i_1 = 0;
    int i_2 = 0;

    while(line_1[i_1] != '\0' && line_2[i_2] != '\0')
    {
        if (isalpha(line_1[i_1]) && isalpha(line_2[i_2]))
            {
            if ((islower(line_1[i_1]) && islower(line_2[i_2])) || (isupper(line_1[i_1]) && isupper(line_2[i_2])))
            {
                if (line_1[i_1] != line_2[i_2])
                    return (line_1[i_1] - line_2[i_2]);

                else {i_1++; i_2++;}
            }
            else if (tolower(line_1[i_1]) != tolower(line_2[i_2]))
                return (tolower(line_1[i_1]) - tolower(line_2[i_2]));
            else
                return (line_1[i_1] - line_2[i_2]);
            }

        else if(!isalpha(line_1[i_1]) && isalpha(line_2[i_2]))
            i_1++;

        else if(!isalpha(line_2[i_2]) && isalpha(line_1[i_1]))
            i_2++;

        else {i_1++; i_2++;}
    }
    return (len_1 - len_2);
}

/**
@function
Comparison function for strings, ignoring punctuation.
!!!Ñompares strings from the end!!!
@param string_1 - Pointer to the first line;
@param string_2 - Pointer to the second line;
@return returns a negative integer value if
the first argument is less than the second,\n
a positive integer value if the first
argument is greater than the second\n
and zero if the arguments are equal.
*/

int reverse_lines_cmp(const void * string_1, const void * string_2)
{
    assert(string_1 != NULL);
    assert(string_2 != NULL);

    char * line_1 = (*(struct Line *) string_1).line_begin;
    char * line_2 = (*(struct Line *) string_2).line_begin;


    int len_1 = (*(struct Line *) string_1).len;
    int len_2 = (*(struct Line *) string_2).len;
    int i_1 = len_1 - 1;
    int i_2 = len_2 - 1;

    while(i_1 != -1 && i_2 != -1)
    {
        if (isalpha(line_1[i_1]) && isalpha(line_2[i_2]))
            {
            if ((islower(line_1[i_1]) && islower(line_2[i_2])) || (isupper(line_1[i_1]) && isupper(line_2[i_2])))
            {
                if (line_1[i_1] != line_2[i_2])
                    return (line_1[i_1] - line_2[i_2]);

                else {i_1--; i_2--;}
            }
            else if (tolower(line_1[i_1]) != tolower(line_2[i_2]))
                return (tolower(line_1[i_1]) - tolower(line_2[i_2]));
            else
                return (line_1[i_1] - line_2[i_2]);
            }

        else if(!isalpha(line_1[i_1]) && isalpha(line_2[i_2]))
            i_1--;

        else if(!isalpha(line_2[i_2]) && isalpha(line_1[i_1]))
            i_2--;

        else {i_1--; i_2--;}
    }
    return (len_1 - len_2);
}

/**
@function
Prints the sorted lines to the new file "Sorted_File.txt".
@param text - Array with pointers to strings;
@param n_lines - Number of lines in the file;
@param output_name - Name of output file.
@return 0 - if program the program was successful.
*/

int print_text(struct Line * text, int n_lines, const char * output_name)
{
    assert(text != NULL);
    assert(n_lines >= 0);

    FILE * onegin_output = fopen(output_name, "w");
    assert (onegin_output);


    int magic_number  = 20;

    for(int line = 0; line < n_lines; line++)
        if(text[line].line_begin[0] != 0 && !isdigit(text[line].line_begin[0]) && text[line].line_begin[0] != '\r')
            {

            fprintf(onegin_output, "%s\n", text[line]);
        }
    fclose(onegin_output);
    return 0;
}

/**
@function
@param file_name - pointer to file name.
@param mode - pointer to sorting mode;
@return 0 - if program the program was successful.
*/

int user_interface(int * mode)
{
    printf("Poem Dictionary.\n");
    printf("Select sorting mode\n");
    printf("To sort the file in alphabetical order, click '1'\n");
    printf("To sort the file in reverse alphabetical order (from the end), click '2'\n");
    scanf("%d", mode);
    return 0;
}

/**
@param text - Array with pointers to strings;
@param data - Array - a copy of the file;
@param file - Pointer to read file.
@return 0 - if program the program was successful.
*/

int free_memory(struct Line * text, char * data)
{
    free(text);
    free(data);

    return 0;
}
