#include <stdio.h>
#include <string.h>

int main() {

    char item[71] = "";
    float price = 0.0f;
    char currency = '$';
    int quantity = 0;
    float total = 0.0f;

    printf("item would you buy?: ");
    fgets(item, 71, stdin);

    printf("price /item?: ");
    scanf("%f", &price);

    printf("much item you buy: ");
    scanf("%d", &quantity);

    total = price * quantity;

    printf("\ntotal is: %c%.2f\n", currency, total);

    return 0;
} 