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

#include <assert.h>
#include <dstring.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void test_string_new();
void test_string_new_with_text();
void test_string_copy_string();
void test_string_copy_char_array();
void test_string_sprint();
void test_string_char_at();
void test_string_concat_string();
void test_string_concat_char_array();
void test_string_get_length();
void test_string_compare();
void test_string_compare_by_locale();
void test_string_equals();
void test_string_equals_by_locale();
void test_string_is_empty();
void test_string_shrink_to_fit();
void test_string_replace_all();
void test_string_replace_first();
void test_string_substring();
void test_string_set_text();
void test_string_tolower();
void test_string_toupper();

int main( int argc, char const *argv[] ) {
    setlocale( LC_ALL, "Portuguese" );

    test_string_new();
    test_string_new_with_text();
    test_string_copy_string();
    test_string_copy_char_array();
    test_string_sprint();
    test_string_char_at();
    test_string_concat_string();
    test_string_concat_char_array();
    test_string_get_length();
    test_string_compare();
    test_string_compare_by_locale();
    test_string_equals();
    test_string_equals_by_locale();
    test_string_is_empty();
    test_string_shrink_to_fit();
    test_string_replace_all();
    test_string_replace_first();
    test_string_substring();
    test_string_set_text();
    test_string_tolower();
    test_string_toupper();

    return 0;
}

void test_string_new() {
    printf( "String new\n" );
    String *string = string_new();

    assert( string != NULL );

    string_free( string );
}

void test_string_new_with_text() {
    printf( "String new with text\n" );
    static const char test_char[] = "Hello World!";
    String *string = string_new_with_text( test_char );

    assert( string != NULL );
    assert( strcmp( string_get_text( string ), test_char ) == 0 );

    string_free( string );
}

void test_string_copy_string() {
    printf( "String copy string\n" );
    String *destination = string_new();
    String *source = string_new_with_text( "Source test" );

    string_copy_string( destination, source );
    assert( strcmp( string_get_text( destination ), string_get_text( source ) ) == 0 );

    string_free( destination );
    string_free( source );
}

void test_string_copy_char_array() {
    printf( "String copy char array\n" );
    static const char test_char[] = "Char array";
    String *string = string_new();

    string_copy_char_array( string, test_char );
    assert( strcmp( string_get_text( string ), test_char ) == 0 );

    string_free( string );
}

void test_string_char_at() {
    printf( "String char at\n" );
    String *string = string_new_with_text( "Hello World!" );

    char char_at = string_char_at( string, 6 );
    assert( char_at == 'W' );

    string_free( string );
}

void test_string_concat_string() {
    printf( "String concat string\n" );
    String *destination = string_new_with_text( "Hello" );
    String *source = string_new_with_text( " World" );

    for( int i = 0; i < 3; i++ ) {
        string_concat_string( destination, source );
    }
    assert( strcmp( string_get_text( destination ), "Hello World World World" ) == 0 );

    string_free( destination );
    string_free( source );
}

void test_string_concat_char_array() {
    printf( "String concat char array\n" );
    String *destination = string_new_with_text( "Hello" );
    char source[] = " World";

    for( int i = 0; i < 3; i++ ) {
        string_concat_char_array( destination, source );
    }
    assert( strcmp( string_get_text( destination ), "Hello World World World" ) == 0 );

    string_free( destination );
}

void test_string_get_length() {
    printf( "String get length\n" );
    String *string = string_new_with_text( "1234F" );

    assert( string_get_length( string ) == 5 );

    string_free( string );
}

void test_string_sprint() {
    printf( "String sprint\n" );
    String *string = string_new();

    string_sprint( string, "%s %d", "Test", 3 );
    assert( strcmp( string_get_text( string ), "Test 3" ) == 0 );

    string_free( string );
}

void test_string_compare() {
    printf( "String compare\n" );
    String *string1 = string_new_with_text( "Hello World 1" );
    String *string2 = string_new_with_text( "Hello World 2" );

    int compare = string_compare( string1, string2 );
    assert( compare != 0 );

    string_free( string1 );
    string_free( string2 );
}

void test_string_compare_by_locale() {
    printf( "String compare by locale\n" );
    String *string1 = string_new_with_text( "Programação" );
    String *string2 = string_new_with_text( "Programação" );

    int compare = string_compare_by_locale( string1, string2 );
    assert( compare == 0 );

    string_free( string1 );
    string_free( string2 );
}

void test_string_equals() {
    printf( "String equals\n" );
    String *string1 = string_new_with_text( "Hello World 1" );
    String *string2 = string_new_with_text( "Hello World 2" );

    bool compare = string_equals( string1, string2 );
    assert( compare == false );

    string_free( string1 );
    string_free( string2 );
}

void test_string_equals_by_locale() {
    printf( "String equals by locale\n" );
    String *string1 = string_new_with_text( "Programação" );
    String *string2 = string_new_with_text( "Programação" );

    bool compare = string_equals_by_locale( string1, string2 );
    assert( compare == true );

    string_free( string1 );
    string_free( string2 );
}

void test_string_is_empty() {
    printf( "String is empty\n" );
    String *string = string_new();

    bool compare = string_is_empty( string );
    assert( compare == true );

    string_free( string );
}

void test_string_shrink_to_fit() {
    printf( "String shrink to fit\n" );
    String *string = string_new_with_text( "0123456789" );

    bool compare = string_shrink_to_fit( string );
    assert( compare == true );

    string_free( string );
}

void test_string_replace_all() {
    printf( "String replace all\n" );
    String *string = string_new_with_text( "Hello World World!" );
    char regex[] = " World";
    char replacement[] = "";

    string_replace_all( string, regex, replacement );
    assert( strcmp( string_get_text( string ), "Hello!" ) == 0 );

    string_free( string );
}

void test_string_replace_first() {
    printf( "String replace first\n" );
    String *string = string_new_with_text( "Hello World World!" );
    char regex[] = " World";
    char replacement[] = "";

    string_replace_first( string, regex, replacement );
    assert( strcmp( string_get_text( string ), "Hello World!" ) == 0 );

    string_free( string );
}

void test_string_substring() {
    printf( "String substring\n" );
    String *string = string_new_with_text( "Hello World!" );

    String *substring = string_substring( string, 0, 5 );
    assert( strcmp( string_get_text( substring ), "Hello" ) == 0 );

    string_free( string );
    string_free( substring );
}

void test_string_set_text() {
    printf( "String set text\n" );
    String *string = string_new();
    char text[] = "New String";

    string_set_text( string, text );
    assert( strcmp( string_get_text( string ), text ) == 0 );

    string_free( string );
}

void test_string_tolower() {
    printf( "String to lowercase\n" );
    String *string = string_new_with_text( "Olá moça" );

    String *result = string_new_with_text( "olá moça" );

    string_tolower( string );

    assert( string_equals( string, result ) == true );
}
void test_string_toupper() {
    printf( "String to uppercase\n" );
    String *string = string_new_with_text( "Olá moço" );
    String *result = string_new_with_text( "OLá MOçO" );

    string_toupper( string );

    assert( string_equals( string, result ) == true );
}
