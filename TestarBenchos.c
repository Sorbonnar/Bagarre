#include <stdlib.h>
#include <stdio.h>




void main() {

    srand(time(NULL));

    int w, m, n, y = 13, x = 10;

    w = rand() % 4;
    m = (rand() % ((y+1)/2)) * 2 + 1;
    n = (rand() % ((x+1)/2)) * 2 + 1;

    printf(" %d  %d  %d", w, m, n);

}