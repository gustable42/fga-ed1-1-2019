#include <stdio.h>
#include <stdlib.h>

int somaDig(int num);

int main()  {
    int number;
    scanf("%d", &number);
    int dig = somaDig(number);
    printf("%d\n", dig);

    return 0;
}

int somaDig(int num) {
    int resto = num % 10;
    num /= 10;
    if(num == 0)
        return resto;    
    return somaDig(num) + resto;
}