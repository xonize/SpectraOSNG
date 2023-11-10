#include <string.h>

char* strrev(char* str, int len) {
	int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
    return str;
}