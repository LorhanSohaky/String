/*
The MIT License (MIT)
Copyright (c) 2017 Lorhan Sohaky
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <dstring.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 51// 50 for string + 1 for \0

void calloc_string(String *string, unsigned int capacity);
void realloc_string(String *string, unsigned int capacity);

String *string_new(){
    String *string=calloc(1,sizeof(String));
    if(string!=NULL){
        calloc_string(string,DEFAULT_LENGTH);
    }
    return string;
}

String *string_new_with_text(const char *text){
    String *string=string_new();
    if(string!=NULL){
        string_copy_text(string, text);
    }
    return string;
}

void string_copy_text(String *string, const char *text){
    if(strlen(text)<=string->capacity){
        strcpy(string->char_array, text);
    }else{
        realloc_string(string, strlen(text));
        if(string->capacity!=0){
            string_copy_text(string, text);
        }
    }
}

void calloc_string(String *string, unsigned int capacity){
    string->char_array=calloc(capacity,sizeof(char));

    if(string->char_array!=NULL){
        string->capacity=capacity;
    }else{
        string->capacity=0;
    }
}

void realloc_string(String *string, unsigned int capacity){
    char *tmp=calloc(capacity,sizeof(char));

    if(tmp!=NULL){
        string->char_array=tmp;
        string->capacity=capacity;
    }else{
        string->capacity=0;
    }
}

void string_free(String **string){
    if(*string!=NULL){
        if((*string)->char_array!=NULL){
            free((*string)->char_array);
            (*string)->char_array=NULL;
        }
        free(*string);
        *string=NULL;
    }
}
