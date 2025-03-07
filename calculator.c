#include <stdio.h>
int main()
{
    char operator; 
    double a;
    double b;
    double result;

    printf("\nEnter an operator:(+ - * /) ");
    scanf("%c", &operator);

    printf("\nenter your first number: ");
    scanf("%lf", &a);

    printf("\nEnter your second number: ");
    scanf("%lf", &b);

    switch (operator)
    {
    case '+':
        result = a + b;
        printf("%.2lf\n", result);
        break;

    case '-':
        result = a - b;
        printf("%.2lf\n", result);
        break;

    case '*':
        result = a * b;
        printf("%.2lf\n", result);
        break;

    case '/':
        result = a / b;
        printf("%.2lf\n", result);
        break;
        
    default: printf("invalid operator\n");
        break;
    }
}