/* Assignment name: filter
Expected files: filter.c
Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
realloc, free, printf, fprintf, stdout, stderr, perror
--------------------------------------------------------------------------------

Write a program that will take one and only one argument.

Your program will then read from stdin and write all the content read in stdout
except that every occurrence of s must be replaced by '*' (as many as the length
of s). Your program will be tested with random buffer sizes, using a custom read
function. Therefore the buffer being set in your program will be filled with a
different number of chars each new call. */