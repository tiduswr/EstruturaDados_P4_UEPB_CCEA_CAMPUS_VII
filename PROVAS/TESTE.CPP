#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int tempo = time(0);
    srand(tempo);
    double valor = ((double) rand() * 10) / ( double ) RAND_MAX;
    printf("%f", valor);
}