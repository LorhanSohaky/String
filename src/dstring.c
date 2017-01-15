#include <dstring.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 51// 50 for string + 1 for \0


String *calloc_string(String *string, unsigned capacity);

String *string_new(){
    String *string=calloc(1,sizeof(String));
    if(string!=NULL){
        string=calloc_string(string,DEFAULT_LENGTH);
    }
    return string;
}

String *calloc_string(String *string, unsigned int capacity){
    string->char_array=calloc(capacity,sizeof(char));
    if(string->char_array!=NULL){
        string->capacity=capacity;
    }else{
        string->capacity=0;
    }
    return string;
}
