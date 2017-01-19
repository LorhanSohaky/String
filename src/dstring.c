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

#define DEFAULT_LENGTH 50

struct _String {
    char* char_array;
    int capacity; /* number of bytes allocated */
};

bool calloc_string(String *string, unsigned int capacity);
bool realloc_string(String *string, unsigned int capacity);

String *string_new(){
    String *string=calloc(1,sizeof(String));
    if(string!=NULL){
        calloc_string(string,DEFAULT_LENGTH);
    }
    return string;
}

String *string_new_with_text(const char *text){
    if(text==NULL){
        return NULL;
    }

    String *string=string_new();
    if(string!=NULL){
        if(!string_copy_char_array(string, text)){
            string_free(&string);
        }
    }
    return string;
}

bool string_copy_string(String *destination, const String *source){
    if(destination==NULL || source==NULL){
        return false;
    }
    return string_copy_char_array(destination,source->char_array);
}

bool string_copy_char_array(String *string, const char *text){
    if(string==NULL || text==NULL){
        return false;
    }

    if(strlen(text)<string->capacity){
        strcpy(string->char_array, text);
        return true;
    }else{
        if(!realloc_string(string, strlen(text))){
            return false;
        }else{
            return string_copy_char_array(string, text);
        }
    }
}

bool string_concat_string(String *destination, const String *source){
    if(source==NULL){
        return false;
    }

    return string_concat_char_array(destination,source->char_array);
}

bool string_concat_char_array(String *destination, const char *source){
    if(destination==NULL || source==NULL){
        return false;
    }

    if(strlen(destination->char_array)+strlen(source)<destination->capacity){
        strcat (destination->char_array,source);
        return true;
    }else{
        if(!realloc_string(destination,destination->capacity+strlen(source))){
            return false;
        }
        return string_concat_char_array(destination,source);
    }
}

char string_char_at(String *string, unsigned int index){
    if(string!=NULL && index<strlen(string->char_array)){
        return string->char_array[index];
    }
    return '\0';
}

char *string_get_text(String *string){
    if(string!=NULL){
        return string->char_array;
    }
    return NULL;
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

bool calloc_string(String *string, unsigned int capacity){
    string->char_array=calloc(capacity,sizeof(char));

    if(string->char_array!=NULL){
        string->capacity=capacity;
        return true;
    }else{
        return false;
    }
}

bool realloc_string(String *string, unsigned int capacity){
    char *tmp=realloc(string->char_array,(capacity+1) * sizeof(char));

    if(tmp!=NULL){
        string->char_array=tmp;
        string->capacity=capacity;
        return true;
    }else{
        return false;
    }
}
