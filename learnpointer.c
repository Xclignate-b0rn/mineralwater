#include<stdio.h>

void swap(int *y, int *x) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int x = 10; 
    int y = 20; 
    printf("x = %d",x);
    printf("y = %d",y);
    swap(&x, &y);
    printf("x = %d",x);
    printf("y = %d",y);

    return 0;
}