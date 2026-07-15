#include <stdio.h>

void *my_memmove(void *dst, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    if (d < s) {
        for (size_t i = 0; i < n; i++)
            d[i] = s[i];
    } else if (d > s) {
        for (size_t i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }
    return dst;
}

int main(void) {
    char buf[10] = "ABCDEFGHIJ";
    printf("Before: %s\n", buf);
    my_memmove(buf + 2, buf, 7);
    printf("After:  %s\n", buf);
    return 0;
}

