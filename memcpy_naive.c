#include <stdio.h>

void *my_memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dst;
}

int main(void) {
    char buf[10] = "ABCDEFGHIJ";
    printf("Before: %s\n", buf);
    my_memcpy(buf + 2, buf, 7);
    printf("After:  %s\n", buf);
    return 0;
}
