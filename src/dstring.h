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

#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

#include <stdarg.h>
#include <stdbool.h>

typedef struct _String String;

String *string_new();
String *string_new_with_text( const char *text );
String *string_new_with_size( unsigned int size );

bool string_copy_string( String *destination, const String *source );
bool string_copy_char_array( String *string, const char *text );
String *string_substring( const String *string, int beginIndex, int endIndex );
bool string_sprint( String *string, const char *format, ... );

bool string_concat_string( String *destination, const String *source );
bool string_concat_char_array( String *destination, const char *source );

bool string_replace_first( String *string, const char *regex, const char *replacement );
bool string_replace_all( String *string, const char *regex, const char *replacement );

bool string_equals( const String *string1, const String *string2 );
bool string_equals_by_locale( const String *string1, const String *string2 );

int string_compare( const String *string1, const String *string2 );
int string_compare_by_locale( const String *string1, const String *string2 );

char string_char_at( const String *string, unsigned int index );
bool string_set_text( String *string, const char *char_array );
char *string_get_text( const String *string );
int string_get_length( const String *string );
bool string_is_empty( const String *string );

void string_free( String *string );
bool string_shrink_to_fit( String *string );

#endif
