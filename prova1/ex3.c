#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(char* string1, char* string2);

int main() {
    char string1[100], string2[100] = {};
    gets(string1);
    gets(string2);
    int result = compare_strings(string1, string2);
    printf("%d\n", result);

    return 0;
}

int compare_strings(char* string1, char* string2) {
    int length;
    if(strlen(string1) < strlen(string2)) length = strlen(string1);
    else length = strlen(string2);

    int i;
    for(i = 0; i < length; i++) {
        if(string1[i] < string2[i]) return -1;
        if(string2[i] < string1[i]) return 1;
    }
    return 0;
}