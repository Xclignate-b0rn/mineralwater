#include <stdio.h>

int main() {
    int nilai;
    printf("input number : ");
    scanf("%d", &nilai);


    if (nilai >= 80){
        printf("perfect\n");
    } else if (nilai >= 60) {
        printf("great\n");
    } else {
        printf("pulang sana\n");
    }
    return 0;
}