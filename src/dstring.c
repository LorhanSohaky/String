#include <dstring.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 51// 50 for string + 1 for \0

String *string_new(){
    String *string=calloc(1,sizeof(String));
    if(string!=NULL){
        string->char_array=calloc(DEFAULT_LENGTH,sizeof(char));
        if(string->char_array!=NULL){
            string->capacity=DEFAULT_LENGTH;
        }else{
            string->capacity=0;
        }
    }
    return string;
}
