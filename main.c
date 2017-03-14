#include "PSO.h"

int main()
{
    Ponto gb;
    float w, c1, c2;
    int n, maxItera;

    w = 0.5;
    c1 = 2.1;//cognitivo
    c2 = 2.1;//social
    n = 200;
    maxItera = 50;

    gb = pso(w, c1, c2, n, maxItera);
    printf("Algoritmo executado com sucesso!\nResultado: (%lf, %lf, %lf)\n\n", gb.x, gb.y, gb.fitness);

    return 0;
}
