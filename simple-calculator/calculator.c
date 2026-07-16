#include <stdio.h>

int main(void)
{

    int choice, num1, num2, result;

    printf("Simple Calculator\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("0. Exit\n");

    printf("Choose an option: ");
    scanf("%d", &choice);

    if (choice == 1)
{
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    result = num1 + num2;

    printf("Result = %d\n", result);

    
}
else if (choice == 2)
{
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    result = num1 - num2;

    printf("Result = %d\n", result);
}
else if (choice == 3)
{
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    result = num1 * num2;

    printf("Result = %d\n", result);
}
else if (choice == 4)
{
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    if (num2 == 0)
    {
        printf("Cannot divide by zero!\n");
    }
    else
    {
        result = num1 / num2;

        printf("Result = %d\n", result);
    }
}
else if (choice == 0)
{
    printf("Goodbye!\n");
}
else
{
    printf("Invalid choice!\n");
}

return (0);
}