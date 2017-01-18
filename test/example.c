#include <dstring.h>
#include <stdio.h>

void test_string_new(String *string);

int main(int argc, char const *argv[]) {
    String *string;

    test_string_new(string);
    
    return 0;
}


void test_string_new(String *string){
    string=string_new();
    printf("%p\n",string);
}
