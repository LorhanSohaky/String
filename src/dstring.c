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

// TODO substring(int beginIndex, int endIndex),  replaceAll(String regex, String replacement),
// replaceFirst

#include <dstring.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 50

struct _String {
    char *char_array;
    int capacity; /* number of bytes allocated */
};

bool calloc_string( String *string, unsigned int capacity );
bool realloc_string( String *string, unsigned int capacity );
int get_length_required( const char *format, va_list *list );

String *string_new() {
    String *string = calloc( 1, sizeof( String ) );
    if( string != NULL ) {
        calloc_string( string, DEFAULT_CAPACITY );
    }
    return string;
}

String *string_new_with_text( const char *text ) {
    if( text == NULL ) {
        return NULL;
    }

    String *string = string_new_with_size( strlen( text ) );
    if( string != NULL ) {
        if( !string_copy_char_array( string, text ) ) {
            string_free( &string );
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
    if( destination == NULL || source == NULL ) {
        return false;
    }
    return string_copy_char_array( destination, source->char_array );
}

bool string_copy_char_array( String *string, const char *text ) {
    if( string == NULL || text == NULL ) {
        return false;
    }

    if( strlen( text ) < string->capacity ) {
        strcpy( string->char_array, text );
        return true;
    } else {
        if( !realloc_string( string, strlen( text ) ) ) {
            return false;
        } else {
            return string_copy_char_array( string, text );
        }
    }
}

bool string_sprint( String *string, const char *format, ... ) {
    int capacity_required;
    bool result;
    va_list args;
    va_start( args, format );
    capacity_required = get_length_required( format, &args );
    va_end( args );

    va_start( args, format );
    if( string->capacity > capacity_required ) {
        vsprintf( string->char_array, format, args );
        result = true;
    } else {
        if( realloc_string( string, capacity_required ) ) {
            vsprintf( string->char_array, format, args );
            result = true;
        } else {
            result = false;
        }
    }
    va_end( args );
    return result;
}

int get_length_required( const char *format, va_list *list ) {
    return vsnprintf( NULL, 0, format, *list );
}

bool string_concat_string( String *destination, const String *source ) {
    if( source == NULL ) {
        return false;
    }

    return string_concat_char_array( destination, source->char_array );
}

bool string_concat_char_array( String *destination, const char *source ) {
    if( destination == NULL || source == NULL ) {
        return false;
    }

    if( strlen( destination->char_array ) + strlen( source ) < destination->capacity ) {
        strcat( destination->char_array, source );
        return true;
    } else {
        if( !realloc_string( destination, destination->capacity + strlen( source ) ) ) {
            return false;
        }
        return string_concat_char_array( destination, source );
    }
}

bool string_is_equals( const String *string1, const String *string2 ) {
    if( string_compare( string1, string2 ) == 0 ) {
        return true;
    } else {
        return false;
    }
}

bool string_is_equals_by_locale( const String *string1, const String *string2 ) {
    if( string_compare_by_locale( string1, string2 ) == 0 ) {
        return true;
    } else {
        return false;
    }
}

int string_compare( const String *string1, const String *string2 ) {
    return strcmp( string1->char_array, string2->char_array );
}

int string_compare_by_locale( const String *string1, const String *string2 ) {
    return strcoll( string1->char_array, string2->char_array );
}

char string_char_at( String *string, unsigned int index ) {
    if( string != NULL && index < strlen( string->char_array ) ) {
        return string->char_array[index];
    }
    return '\0';
}

char *string_get_text( const String *string ) {
    if( string != NULL ) {
        return string->char_array;
    }
    return NULL;
}

int string_get_length( const String *string ) {
    if( string != NULL ) {
        return strlen( string->char_array );
    } else {
        return -1;
    }
}

bool string_is_empty( const String *string ) {
    if( string == NULL || string->capacity == 0 || strlen( string->char_array ) == 0 ) {
        return true;
    } else {
        return false;
    }
}

void string_free( String **string ) {
    if( *string != NULL ) {
        if( ( *string )->char_array != NULL ) {
            free( ( *string )->char_array );
            ( *string )->char_array = NULL;
        }
        free( *string );
        *string = NULL;
    }
}

bool string_resize( String *string ) {
    return realloc( string, strlen( string->char_array ) );
}

bool calloc_string( String *string, unsigned int capacity ) {
    string->char_array = calloc( capacity + 1, sizeof( char ) );

    if( string->char_array != NULL ) {
        string->capacity = capacity + 1;
        return true;
    } else {
        return false;
    }
}

bool realloc_string( String *string, unsigned int capacity ) {
    char *tmp = realloc( string->char_array, ( capacity + 1 ) * sizeof( char ) );

    if( tmp != NULL ) {
        string->char_array = tmp;
        string->capacity = capacity;
        return true;
    } else {
        return false;
    }
}
