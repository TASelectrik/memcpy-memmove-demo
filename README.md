# memcpy vs memmove — overlap corruption demo

A small, focused demo showing exactly why memcpy() breaks on overlapping
source and destination buffers — and why memmove() exists.

my_memcpy() copies forward, byte by byte. On overlapping regions this
silently overwrites source bytes before they're read, corrupting data
with no crash and no warning — because the C standard leaves this case
completely undefined.

my_memmove() checks the direction between src and dst first, and copies
backward when needed, guaranteeing every byte is read before it can be
overwritten.

Relevant beyond the toy example: this exact overlap condition shows up
in real embedded code — shifting bytes inside a DMA buffer, or handling
a ring buffer wraparound — where there's no MMU and no safety net.

## Files

- memcpy_naive.c — forward-only copy, breaks on overlap
- memmove_fix.c — direction-aware copy, safe on overlap

## Build

gcc -g -O0 -Wall -o memcpy_naive memcpy_naive.c
gcc -g -O0 -Wall -o memmove_fix memmove_fix.c

## Run

./memcpy_naive
./memmove_fix

## Example: shift "ABCDEFGHIJ" right by 2 (src=&buf[0], dst=&buf[2], n=7)

Naive memcpy (corrupted):
Before: ABCDEFGHIJ
After:  ABABABABAJ

memmove fix (correct):
Before: ABCDEFGHIJ
After:  ABABCDEFGJ
