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

void test_string_new( String **string );
void test_string_new_with_text( String **string, const char *text );
void test_string_copy_string( String *destination, const String *source );
void test_string_copy_char_array( String *string, char *text );
void test_string_sprint( String *string );
void test_string_free( String *string );
void test_string_char_at( String *string, unsigned int index );
void test_string_concat_string( String *destination, const String *source );
void test_string_concat_char_array( String *destination, const char *source );
void test_string_get_length( String *string );
void test_string_compare( String *string1, String *string2 );
void test_string_compare_by_locale( String *string1, String *string2 );
void test_string_equals( String *string1, String *string2 );
void test_string_equals_by_locale( String *string1, String *string2 );
void test_string_is_empty( String *string );
void test_string_shrink_to_fit( String *string );
void test_string_replace_all( String *string, const char *regex, const char *replacement );
void test_string_replace_first( String *string, const char *regex, const char *replacement );
void test_string_substring( String *string );
void test_string_set_text( String *string, const char *char_array );

int main( int argc, char const *argv[] ) {
    String *string1;
    String *string2;

    test_string_new( &string1 );
    test_string_copy_char_array( string1, "Stringtest1" );
    test_string_char_at( string1, 1 );

    test_string_new_with_text( &string2, "Stringtest2" );

    test_string_concat_string( string1, string2 );

    test_string_copy_char_array( string1, "String" );
    test_string_concat_char_array( string1, " TEST " );

    test_string_replace_all( string1, "TEST", "h" );
    test_string_replace_all( string1, "h", "Lorhan Sohaky" );
    test_string_replace_first( string1, "Lorhan Sohaky", "First" );
    test_string_substring( string1 );

    test_string_copy_string( string1, string2 );

    test_string_shrink_to_fit( string1 );

    test_string_copy_char_array( string1, "" );
    test_string_get_length( string1 );

    test_string_sprint( string1 );

    test_string_compare( string1, string2 );
    test_string_compare_by_locale( string1, string2 );

    test_string_copy_string( string1, string2 );
    test_string_equals( string1, string2 );
    test_string_equals_by_locale( string1, string2 );

    test_string_is_empty( string1 );

    test_string_set_text( string1, "New String" );

    test_string_free( string1 );
    test_string_free( string2 );

    return 0;
}

void test_string_new( String **string ) {
    *string = string_new();
    printf( "String new:%p\n", *string );
    printf( "\n" );
}

void test_string_new_with_text( String **string, const char *text ) {
    *string = string_new_with_text( text );
    printf( "String new with text:%s\n", string_get_text( *string ) );
    printf( "\n" );
}

void test_string_copy_string( String *destination, const String *source ) {
    string_copy_string( destination, source );
    printf( "String copy string:%s\n", string_get_text( destination ) );
    printf( "\n" );
}

void test_string_copy_char_array( String *string, char *text ) {
    string_copy_char_array( string, text );
    printf( "String copy char array:%s\n", string_get_text( string ) );
    printf( "\n" );
}

void test_string_free( String *string ) {
    string_free( string );
    printf( "String free:%p\n", string );
    printf( "\n" );
}

void test_string_char_at( String *string, unsigned int index ) {
    printf( "String char at:%c\n", string_char_at( string, index ) );
    printf( "\n" );
}

void test_string_concat_string( String *destination, const String *source ) {
    for( int i = 0; i < 5; i++ ) {
        string_concat_string( destination, source );
        printf( "String concat string:%s\n", string_get_text( destination ) );
    }
    printf( "\n" );
}

void test_string_concat_char_array( String *destination, const char *source ) {
    for( int i = 0; i < 5; i++ ) {
        string_concat_char_array( destination, source );
        printf( "String concat char array:%s\n", string_get_text( destination ) );
    }
    printf( "\n" );
}

void test_string_get_length( String *string ) {
    printf( "String get length:%d\n", string_get_length( string ) );
    printf( "\n" );
}

void test_string_sprint( String *string ) {
    string_sprint( string, "%s %d", "Test", 3 );
    printf( "String sprint:%s\n", string_get_text( string ) );
    printf( "\n" );
}

void test_string_compare( String *string1, String *string2 ) {
    printf( "String compare:%d\n", string_compare( string1, string2 ) );
    printf( "\n" );
}

void test_string_compare_by_locale( String *string1, String *string2 ) {
    printf( "String compare by locale:%d\n", string_compare_by_locale( string1, string2 ) );
    printf( "\n" );
}

void test_string_equals( String *string1, String *string2 ) {
    printf( "String equals:%d\n", string_equals( string1, string2 ) );
    printf( "\n" );
}

void test_string_equals_by_locale( String *string1, String *string2 ) {
    printf( "String equals by locale:%d\n", string_equals_by_locale( string1, string2 ) );
    printf( "\n" );
}

void test_string_is_empty( String *string ) {
    printf( "String is empty:%d\n", string_is_empty( string ) );
    printf( "\n" );
}

void test_string_shrink_to_fit( String *string ) {
    printf( "String shrink to fit:%d\n", string_shrink_to_fit( string ) );
    printf( "\n" );
}

void test_string_replace_all( String *string, const char *regex, const char *replacement ) {
    string_replace_all( string, regex, replacement );
    printf( "String replace all:%s\n", string_get_text( string ) );
    printf( "\n" );
}

void test_string_replace_first( String *string, const char *regex, const char *replacement ) {
    string_replace_first( string, regex, replacement );
    printf( "String replace first:%s\n", string_get_text( string ) );
    printf( "\n" );
}

void test_string_substring( String *string ) {
    String *substring = string_substring( string, 1, 4 );
    printf( "String substring:%s\n", string_get_text( substring ) );
    printf( "\n" );
}

void test_string_set_text( String *string, const char *char_array ) {
    string_set_text( string, char_array );
    printf( "String set text:%s\n", string_get_text( string ) );
    printf( "\n" );
}
