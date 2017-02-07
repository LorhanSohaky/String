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
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 50

struct _String {
    char *char_array;
    int capacity; /* number of bytes allocated */
};

bool static calloc_string( String *string, unsigned int capacity );
bool static realloc_string( String *string, unsigned int capacity );
int static get_length_required( const char *format, va_list *list );
int static count_substring( const String *string, const char *substring );
void static concat_n_string( String *destination, const char *replacement );

String *string_new() {
    String *string = calloc( 1, sizeof( String ) );
    if( string != NULL ) {
        calloc_string( string, DEFAULT_CAPACITY );
    }
    return string;
}

String *string_new_with_text( const char *text ) {
    String *string = string_new_with_size( strlen( text ) );
    if( string != NULL ) {
        if( !string_copy_char_array( string, text ) ) {
            string_free( string );
        }
    }
    return string;
}

String *string_new_with_size( unsigned int size ) {
    String *string = calloc( 1, sizeof( String ) );
    if( string != NULL ) {
        calloc_string( string, size );
    }
    return string;
}

bool string_copy_string( String *destination, const String *source ) {
    return string_copy_char_array( destination, source->char_array );
}

bool string_copy_char_array( String *string, const char *text ) {
    if( strlen( text ) >= string->capacity && !realloc_string( string, strlen( text ) ) ) {
        return false;
    } else {
        strcpy( string->char_array, text );
        return true;
    }
}

String *string_substring( const String *string, int beginIndex, int endIndex ) {
    String *substring = string_new_with_size( endIndex - beginIndex );
    if( substring == NULL ) {
        return NULL;
    }
    memcpy( substring->char_array, &( string->char_array[beginIndex] ), endIndex );
    return substring;
}

bool string_sprint( String *string, const char *format, ... ) {
    int capacity_required;
    bool result;
    va_list args;

    va_start( args, format );
    capacity_required = get_length_required( format, &args );
    va_end( args );

    va_start( args, format );
    if( string->capacity <= capacity_required && !realloc_string( string, capacity_required ) ) {
        result = false;
    } else {
        vsprintf( string->char_array, format, args );
        result = true;
    }
    va_end( args );
    return result;
}

int static get_length_required( const char *format, va_list *list ) {
    return vsnprintf( NULL, 0, format, *list );
}

bool string_concat_string( String *destination, const String *source ) {
    return string_concat_char_array( destination, source->char_array );
}

bool string_concat_char_array( String *destination, const char *source ) {
    if( strlen( destination->char_array ) + strlen( source ) >= destination->capacity &&
        !realloc_string( destination, destination->capacity + strlen( source ) ) ) {
        return false;
    } else {
        strcat( destination->char_array, source );
        return true;
    }
}

bool string_equals( const String *string1, const String *string2 ) {
    return string_compare( string1, string2 ) == 0;
}

bool string_equals_by_locale( const String *string1, const String *string2 ) {
    return string_compare_by_locale( string1, string2 ) == 0;
}

int string_compare( const String *string1, const String *string2 ) {
    return strcmp( string1->char_array, string2->char_array );
}

int string_compare_by_locale( const String *string1, const String *string2 ) {
    return strcoll( string1->char_array, string2->char_array );
}

bool string_replace_first( String *string, const char *regex, const char *replacement ) {
    char *test = strstr( string->char_array, regex );
    int length_necessary = strlen( replacement ) - strlen( regex );
    String *new_string = string_new_with_size( strlen( string->char_array ) + length_necessary );

    if( test == NULL || new_string == NULL ) {
        return false;
    }
    char *tmp = string->char_array;
    int init_position;

    tmp = strstr( tmp, regex );
    init_position = tmp - string->char_array;
    strncpy( new_string->char_array, string->char_array, init_position );

    new_string->char_array[init_position] = '\0';
    concat_n_string( new_string, replacement );
    tmp += strlen( regex );
    concat_n_string( new_string, tmp );

    free( string->char_array );
    string->char_array = new_string->char_array;
    free( new_string );
    return true;
}

bool string_replace_all( String *string, const char *regex, const char *replacement ) {
    int total = count_substring( string, regex );
    int length_necessary = ( strlen( replacement ) - strlen( regex ) ) * total;
    String *new_string = string_new_with_size( strlen( string->char_array ) + length_necessary );
    if( total == 0 || new_string == NULL ) {
        return false;
    }
    char *tmp = string->char_array;
    char *next;
    int init_position;

    tmp = strstr( tmp, regex );
    init_position = tmp - string->char_array;
    strncpy( new_string->char_array, string->char_array, init_position );
    for( int i = 0; i < total; i++ ) {
        new_string->char_array[init_position] = '\0';
        concat_n_string( new_string, replacement );

        next = tmp + strlen( regex );
        next = strstr( next, regex );

        tmp += strlen( regex );
        if( next == NULL ) {
            next = &tmp[strlen( tmp ) + 1];
        }
        tmp[next - tmp] = '\0';
        concat_n_string( new_string, tmp );
        tmp = next;
        init_position = tmp - new_string->char_array;
    }

    free( string->char_array );
    string->char_array = new_string->char_array;
    free( new_string );
    return true;
}

void static concat_n_string( String *destination, const char *replacement ) {
    strncat( destination->char_array, replacement, strlen( replacement ) + 1 ); //+1 for '\0'
}

int static count_substring( const String *string, const char *substring ) {
    int count = 0;
    char *tmp_char_array = string->char_array;
    while( ( tmp_char_array = strstr( tmp_char_array, substring ) ) != NULL ) {
        count++;
        tmp_char_array += strlen( substring );
    }
    return count;
}

char string_char_at( const String *string, unsigned int index ) {
    if( index < strlen( string->char_array ) ) {
        return string->char_array[index];
    }
    return '\0';
}

bool string_set_text( String *string, const char *char_array ) {
    return string_copy_char_array( string, char_array );
}

char *string_get_text( const String *string ) {
    return string->char_array;
}

int string_get_length( const String *string ) {
    return strlen( string->char_array );
}

bool string_is_empty( const String *string ) {
    if( string->capacity == 0 || strlen( string->char_array ) == 0 ) {
        return true;
    } else {
        return false;
    }
}

void string_free( String *string ) {
    if( string != NULL ) {
        if( string->char_array != NULL ) {
            free( string->char_array );
            string->char_array = NULL;
        }
        free( string );
    }
}

bool string_shrink_to_fit( String *string ) {
    return realloc_string( string, strlen( string->char_array ) );
}

bool static calloc_string( String *string, unsigned int capacity ) {
    string->char_array = calloc( ++capacity, sizeof( char ) );

    if( string->char_array != NULL ) {
        string->capacity = capacity;
        return true;
    } else {
        return false;
    }
}

bool static realloc_string( String *string, unsigned int capacity ) {
    char *tmp = realloc( string->char_array, ++capacity * sizeof( char ) );

    if( tmp != NULL ) {
        string->char_array = tmp;
        string->capacity = capacity;
        return true;
    } else {
        return false;
    }
}
