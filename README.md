# Dynamic String
This C library provides easier manipulation of dynamic C-strings.

### LICENSE
**MIT**
[Read the license](LICENSE)

### COMPILER USED
***gcc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0***

### HOW TO USE
Read the [Wiki](https://github.com/LorhanSohaky/String/wiki) to see all details


### EXAMPLE

```C
#include <stdio.h>
#include <dstring.h>

int main (void){
    String *string=string_new_with_text("Hello World");
    printf("%s\n",string_get_text(string));
    string_free(string);
    return 0;
}
```
