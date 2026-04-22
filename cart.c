#include <stdio.h>

int main(){


    char item[50] = "";
    float price = 0.0f;
    char currency = '$';
    int quantitiy = 0;
    float total = 0.0f;

    printf("would you like to buy?: ");
    fgets(item, sizeof(item), stdin);

    printf("what is the price for each item?: ");
    scanf("%f", &price);

    printf("what currency?:");
    scanf(" %c", &currency);

    printf("how much?: ");
    scanf("%d", &quantitiy);

    total = price * quantitiy;
    printf("total is : %4f%c", total, currency);


}