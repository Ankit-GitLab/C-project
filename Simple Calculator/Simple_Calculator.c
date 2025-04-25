#include <stdio.h>

int main() {
    char operator;
    double num1, num2, result;

    printf("\n    Welcome to Simple Calculator....\n\n");
    printf("Enter first numbers : ");
    scanf("%lf", &num1);
    printf("Choose one of the following operator (+, -, *, /) : ");
    scanf(" %c", &operator);
    printf("Enter second numbers : ");
    scanf("%lf", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("%.1lf + %.1lf = %.1lf\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.1lf - %.1lf = %.1lf\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.1lf * %.1lf = %.1lf\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.1lf / %.1lf = %.1lf\n", num1, num2, result);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error: Invalid operator. Please use +, -, *, or /.\n");
    }

    return 0;
}

