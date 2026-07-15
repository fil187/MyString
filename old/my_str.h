#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef MY_STR_H
#define MY_STR_H

struct MyStr {
    size_t capacity;
    size_t size;
    
    char* str;
};

typedef struct MyStr* MyStr;

#define END_OF_STR '\0'
#define DEFAULT_CAPACITY 100
#define LARGE_CHUNK_SIZE 8

/*##########################################################
#                         functions                        #
##########################################################*/
MyStr new_str(const char* str);                        // constructor
void push_char(MyStr self, char ch);                   // add char to the end of the string
void push_str(MyStr self, const char* str);            // add str to the end of the string
const char* get_str(MyStr self);                       // gets the str from the struct returns NULL if self or self->str is NULL
char pop_back(MyStr self);                             // pops the last element of the string, returns the element that was removed
int clear(MyStr _self);                                // *empty the string (puts a null terminator at idx = 0) data is still present in memory returns 1 on success
int append(MyStr self, MyStr source);                  // append another my_str to the first argument: my_str
void destroy(MyStr self);                              // destroyer

#endif