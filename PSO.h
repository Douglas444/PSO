#include <stdio.h>
#include <stdlib.h>

struct ponto
{
    float x, y, fitness;
};
typedef struct ponto Ponto;

struct particula
{
    Ponto posicao, pb, velocidade;
};
typedef struct particula Particula;

Ponto pso(float w, float c1, float c2, int n, int maxItera);
