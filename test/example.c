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
#include <stdio.h>

void test_string_new(String **string);
void test_string_new_with_text(String **string, const char *text);
void test_string_copy_string(String *destination, const String *source);
void test_string_copy_char_array(String *string, char *text);
void test_string_free(String **string);
void test_string_char_at(String *string, unsigned int index);
void test_string_concat_string(String *destination, const String *source);
void test_string_concat_char_array(String *destination,const char *source);

int main(int argc, char const *argv[]) {
    String *string1;
    String *string2;

    test_string_new(&string1);
    test_string_copy_char_array(string1, "Stringtest1");
    test_string_char_at(string1, 1);

    test_string_new_with_text(&string2,"Stringtest2");

    test_string_concat_string(string1,string2);
    test_string_concat_char_array(string1," TEST ");

    test_string_copy_string(string1,string2);

    test_string_free(&string1);
    test_string_free(&string2);

    return 0;
}


void test_string_new(String **string){
    *string=string_new();
    printf("%p\n",*string);
}

void test_string_new_with_text(String **string, const char *text){
    *string=string_new_with_text(text);
    printf("%s\n",string_get_text(*string));
}

void test_string_copy_string(String *destination, const String *source){
    string_copy_string(destination,source);
    printf("%s\n",string_get_text(destination));
}

void test_string_copy_char_array(String *string, char *text){
    string_copy_char_array(string,text);
    printf("%s\n",string_get_text(string));
}

void test_string_free(String **string){
    string_free(string);
    printf("%p\n",*string);
}

void test_string_char_at(String *string, unsigned int index){
    printf("%c\n",string_char_at(string,index));
}

void test_string_concat_string(String *destination, const String *source){
    for (int i=0;i<5;i++){
        string_concat_string(destination,source);
        printf("%s\n",string_get_text(destination));
    }
}

void test_string_concat_char_array(String *destination,const char *source){
    for (int i=0;i<5;i++){
        string_concat_char_array(destination,source);
        printf("%s\n",string_get_text(destination));
    }
}
