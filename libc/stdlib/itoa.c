// #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    // Handle 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Only handle negatives in base 10
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    // Append '-' if negative
    if (isNegative) {
        str[i++] = '-';
    }

    // Null terminator
    str[i] = '\0';

    // Reverse
    str = strrev(str, i);
    return str;
}