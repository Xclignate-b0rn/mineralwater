#include <stdio.h>

void tukar(int* for_x, int* for_y) {
    int z;
    z = *for_x;
    *for_x = *for_y;
    *for_y = z;
}

int main(){
    int x = 1;
    int y = 2;
    int* for_x = &x;
    int* for_y = &y;

    printf("X = %d\n", x);
    printf("Y = %d\n", y);

    tukar(&x, &y);

    printf("then X = %d\n", x);
    printf("then Y = %d\n", y);

    return 0;
}