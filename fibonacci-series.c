#include <stdio.h> 
int main()
{
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    long long int a = 0;
    long long int b = 1;    
    long long int i = 1;
    do{
        printf("\n%lld\n", a);
        long long int c = a+b;
        a = b;
        b = c;
        i = i + 1;
    }while (i <= n);
}