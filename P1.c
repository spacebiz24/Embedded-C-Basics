// Logical and Shift Operations

#include <stdio.h>

int main()
{
    int a, b, shift;

    printf("Enter two numbers: \n");
    scanf("%d %d", &a, &b);

    printf("\nLogical Operations:\n");
    printf("NOT a: %d NOT b: %d\n", ~a, ~b);
    printf("a AND b: %d\n", a & b);
    printf("a OR b: %d\n", a | b);
    printf("a XOR b: %d\n", a ^ b);

    printf("\nEnter shifting value:\n");
    scanf("%d", &shift);

    printf("a >> %d = %d\n", shift, a >> shift);
    printf("b << %d = %d\n", shift, b << shift);

    return 0;
}
