/*------------------------------------------------------
* Filename: file_operations.c
* Description: creating some methods for operating files
* Author: Niv Karasenty
-------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*------------------------------------------------------
* Function Name - open_file
*
* Function Purpose - trying to open a file in asked way, stoping the program if fails
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - returns an open file in the asked manner
*
* Author - Niv Karasenty
-------------------------------------------------------*/
FILE* open_file(char *file_name, char *mode) {
    FILE *fp = NULL;
    if ((fp = fopen(file_name, mode)) == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
}

/*------------------------------------------------------
* Function Name - file_to_std
*
* Function Purpose - printing file's text to the standard output
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - void
*
* Author - Niv Karasenty
-------------------------------------------------------*/
void file_to_std(char *filename) {
    FILE *fp = NULL;
    char c;

    // Opening the file for reading
    fp = open_file(filename, "r");

    // Reading from the file to the standard output
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    // Closing the files
    if (fclose(fp) != 0) printf("Error closing file\n");
}

/*------------------------------------------------------
* Function Name - file_to_file
*
* Function Purpose - copying the text from file a to file b
*
* Parameters –  char *src_name - the name of the file we want to read from
*               char *dst_name - the name of the file we want to write to
*
* Return Values - void
*
* Author - Niv Karasenty
-------------------------------------------------------*/
void file_to_file(char *src_name, char *dst_name) {
    FILE *src_file = NULL;
    FILE *dst_file = NULL;
    char c;

    // Opening the files
    src_file = open_file(src_name, "r");
    dst_file = open_file(dst_name, "w");

    while ((c = fgetc(src_file)) != EOF) {
        fputc(c, dst_file);
    }

    // Closing all files
    if (fclose(src_file) != 0) printf("Error closing file\n");
    if (fclose(dst_file) != 0) printf("Error closing file\n");
}

/*------------------------------------------------------
* Function Name - number_of_lines
*
* Function Purpose - calculating the number of lines in a file
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - returns the number of lines in a file
*
* Author - Niv Karasenty
-------------------------------------------------------*/
int number_of_lines(char *file_name) {
    FILE *fp = open_file(file_name, "r");
    int count = 0;
    char c;

    while (EOF != (c = fgetc(fp))) {
        if (c == '\n') count++;
    }

    if (fclose(fp) != 0) printf("Error closing file\n");
    return count;
}

/*------------------------------------------------------
* Function Name - number_of_words
*
* Function Purpose - calculating the number of words seperated by a space in a file
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - returns the number of words in a file
*
* Author - Niv Karasenty
-------------------------------------------------------*/
int number_of_words(char *file_name) {
    FILE *fp = open_file(file_name, "r");
    int count = 0;
    char c;

    while (EOF != (c = fgetc(fp))) {
        if (c == ' ') count ++;
    }

    if (fclose(fp) != 0) printf("Error closing file\n");
    return count;
}

/*------------------------------------------------------
* Function Name - number_of_chars
*
* Function Purpose - calculating the number of letters in a file
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - returns the number of letters in a file
*
* Author - Niv Karasenty
-------------------------------------------------------*/
int number_of_chars(char *file_name) {
    FILE *fp = open_file(file_name, "r");
    int count = 0;
    char c;

    while (EOF != (c = fgetc(fp))) {
        if (c >= 'A' && c <= 'Z') count++;
        else if (c >= 'a' && c <= 'z') count++;
    }

    if (fclose(fp) != 0) printf("Error closing file\n");
    return count;
}

/*------------------------------------------------------
* Function Name - print_file_properties
*
* Function Purpose - printing the number of lines, words and letters in a certain file
*
* Parameters –  char *file_name - the name of the file we want to open
*
* Return Values - none
*
* Author - Niv Karasenty
-------------------------------------------------------*/
void print_file_properties(char *file_name) {
    printf("\nNumber of lines: %d\nNumber of words: %d\nNumber of letters: %d\n", number_of_lines(file_name), number_of_words(file_name), number_of_chars(file_name));
}

// Deleting a certain row from a file
void delete_row(char *filename, int row) {
    char c;
    int delete = 0;
    FILE *fp = open_file(filename, "r");
    FILE *temp = open_file("temp.txt", "w");
    int current_line = 1;

    while ((c = fgetc(fp)) != EOF) {
        if (current_line == row) {
            delete = 1;
        }
        else {
            delete = 0;
        }
        if (delete == 0) {
            fputc(c, temp);
            if (current_line == row) {
                delete = 1;
            }
        }
        if (c == '\n') current_line++;
    }

    // Closing both files
    if (fclose(temp) != 0) printf("Error closing file\n");
    if (fclose(fp) != 0) printf("Error closing file\n");

    // Now removing the old file and renaming the new file
    remove(filename);
    rename("temp.txt", filename);
}

/*------------------------------------------------------
* Function Name - number_of_times_in_file
*
* Function Purpose - calculating the number of times a given string is in a file
*
* Parameters –  char *file_name - the name of the file we want to open
*               char *string - the string we ask to check
*               int length - the length of the string we ask to check
*
* Return Values - returns the number of times the string is present in the file
*
* Author - Niv Karasenty
-------------------------------------------------------*/
int number_of_times_in_file(char *file_name, char *string, int length) {
    FILE *fp = open_file(file_name, "r");
    char c;
    char *check = string;
    int count = 0;
    int number_of_times = 0;

    while (EOF != (c = fgetc(fp))) {
        if (count == length) {
            number_of_times++;
            check = string;
            fseek(fp, -(count - 1), SEEK_CUR);
            count = 0;
        }
        else if (c == *check) {
            check++;
            count++;
        }
        // If the strings do not match at a certain point we go back to the letter after the beginning of the string we have checked
        else {
            check = string;
            fseek(fp, -(count - 1), SEEK_CUR);
            count = 0;
        }
    }

    if (fclose(fp) != 0) printf("Error closing file\n");

    return number_of_times;
}

int main() {
    exit(EXIT_SUCCESS);
}