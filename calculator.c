#include <stdio.h>

int main() {

    char operator;
    double numb1, numb2, result;
    char choice;

    do {
        printf("\n==== Simple Calculator ====");

        printf("Enter the first number: ");
        scanf("%lf", &numb1);

        printf("Enter operator (+, -, *, /, %): ");
        scanf(" %c", &operator);

        printf("Enter the second number: ");
        scanf("%lf", &numb2);

        switch(operator) {
            case '+':
                result = numb1 + numb2;
                printf("Result: %.4lf\n", result);
                break;

            case '-':
                result = numb1 - numb2;
                printf("Result: %.4lf\n", result);
                break;

            case '*':
                result = numb1 * numb2;
                printf("Result: %.4lf\n", result);
                break;

            case '/':
                if(numb2 != 0) {
                    result = numb1 / numb2;
                    printf("Result: %.4lf\n", result);
                } else {
                    printf("Error: Division by zero!\n");
                }
                break;

            case '%':
                if((int)numb2 != 0) {
                    printf("Result: %d\n", (int)numb1 % (int)numb2);
                } else {
                    printf("Error: Modulo by zero!\n");
                }
                break;

            default:
                printf("Error: Invalid operator!\n");
        }

        printf("\nDo you want to calculate again? (y/n): ");
        scanf(" %c", &choice);

    } while(choice == 'y' || choice == 'Y');

    printf("Calculator closed.\n");

    return 0;
}



