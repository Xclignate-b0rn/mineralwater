#include <stdio.h>

int asking_age() {
    int age;
    printf("your age is? : ");
    scanf("%d", &age);
    return age;
}


int main() {
        
    int age = asking_age();
    printf("your age is: %d\n", age);
    
    if (age > 13) {
        printf("approve\n");
    } else {
        printf("rejected\n");
    }
    return 0;
}