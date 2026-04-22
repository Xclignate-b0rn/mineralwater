#include <stdio.h>
#include <stdlib.h>
int main() {
int *arr = malloc(5 * sizeof(int));  // array di heap!

arr[0] = 10;
arr[1] = 20;
arr[2] = 40;

printf("%d %d %d\n", arr[0], arr[1], arr[2]);

free(arr);
}