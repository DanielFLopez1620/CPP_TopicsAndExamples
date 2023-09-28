// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * C11 introduced support for UTF-8, UTF-16 and UTF-32. This meant that we could start using new
 * character while programming in C. Now the limit is not 1 word (byte), it can go beyond.
 * 
 * - https://unicodebook.readthedocs.io/unicode_encodings.html
 * - https://javarevisited.blogspot.com/2015/02/difference-between-utf-8-utf-16-and-utf.html
 * 
 * Now let's use them...
*/

#include <stdlib.h>
#include <string.h>

typedef struct 
{
    long num_chars;
    long num_bytes;
} unicode_len_t;

/**
 * Return the lenght of a character in a struct form.
 * 
 * @param str String or char array with the data...
 * @author Kamran Amini
*/
unicode_len_t strlen_u8(char* str) 
{
    unicode_len_t res;
    res.num_chars = 0;
    res.num_bytes = 0;
    if (!str) 
    {
        return res;
    }
    // Last null character
    res.num_chars = 1;
    res.num_bytes = 1;
    while (*str) 
    {
        if ((*str | 0x7f) == 0x7f) 
        { // 0x7f = 0b01111111
            res.num_chars++;
            res.num_bytes++;
            str++;
        } 
        else if ((*str & 0xc0) == 0xc0) 
        { // 0xc0 = 0b11000000
            res.num_chars++;
            res.num_bytes += 2;
            str += 2;
        } 
        else if ((*str & 0xe0) == 0xe0) 
        { // 0xe0 = 0b11100000
            res.num_chars++;
            res.num_bytes += 3;
            str += 3;
        } 
        else if ((*str & 0xf0) == 0xf0) 
        { // 0xf0 = 0b11110000
            res.num_chars++;
            res.num_bytes += 4;
            str += 4;
        } 
        else 
        {
            fprintf(stderr, "UTF-8 string is not valid!\n");
            exit(1);
        }
    }
    return res;
}

int main(int argc, char** argv)
{
    unicode_len_t len;

    printf("Let's play with anothers character...\n");
    char utf8_string_2[32] = u8"!ایند دورد"; // Persian characters.

    len = strlen_u8(utf8_string_2);
    printf("Length of UTF-8 persian string:\t %ld chars, %ld bytes\n",
        len.num_chars, len.num_bytes);
    return 0;
}