#include "PSO.h"
#include <math.h>
#include <time.h>

#define LIMITE_INF_X 0
#define LIMITE_SUP_X 1

#define LIMITE_INF_Y 0
#define LIMITE_SUP_Y 1

const double PI = 3.141592653589793;

float fitness(Ponto p);
void inicializaPopulacao(Particula *particula, int n, Ponto *gb, float c1, float c2);

Ponto pso(float w, float c1, float c2, int n, int maxItera)
{
    srand((unsigned)time(NULL));

    int i, j;
    Ponto gb;
    Particula *particula;
    float r1, r2;

    particula = (Particula*) malloc(n * sizeof(Particula));
    if(particula == NULL)
    {
        exit(1);
    }
    inicializaPopulacao(particula, n, &gb, c1, c2);

    for(i = 0; i < maxItera; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            r1 = ((float) (rand()%1000))/1000;
            r2 = ((float) (rand()%1000))/1000;

            //Atualiza posição e fitness
            particula[j].posicao.x += particula[j].velocidade.x;
            particula[j].posicao.y += particula[j].velocidade.y;
            particula[j].posicao.fitness = fitness(particula[j].posicao);

            //Limita espaço
            if(particula[j].posicao.x < LIMITE_INF_X)
                particula[j].posicao.x = LIMITE_INF_X;
            if(particula[j].posicao.x > LIMITE_SUP_X)
                particula[j].posicao.x = LIMITE_SUP_X;
            if(particula[j].posicao.y < LIMITE_INF_Y)
                particula[j].posicao.y = LIMITE_INF_Y;
            if(particula[j].posicao.y > LIMITE_SUP_Y)
                particula[j].posicao.y = LIMITE_SUP_Y;

            //Atualiza pb se necessário
            if(particula[j].posicao.fitness > particula[j].pb.fitness)
                particula[j].pb = particula[j].posicao;

            //Atualiza gb se necessário
            if(particula[j].pb.fitness > gb.fitness)
                gb = particula[j].pb;

            //Atualiza velocidade
            particula[j].velocidade.x = w*particula[j].velocidade.x + c1*r1*(particula[j].pb.x - particula[j].posicao.x) + c2*r2*(gb.x - particula[j].posicao.x);
            particula[j].velocidade.y = w*particula[j].velocidade.y + c1*r1*(particula[j].pb.y - particula[j].posicao.y) + c2*r2*(gb.y - particula[j].posicao.y);


        }
    }
    return gb;
}

void inicializaPopulacao(Particula *particula, int n, Ponto *gb, float c1, float c2)
{

    float r1, r2;
    int i;

    gb->fitness = -9999;

    //Inicializa posição e pb de cada partícula e define o gb
    for(i = 0; i < n; ++i)
    {
        //Randomiza posição
        particula[i].posicao.x = LIMITE_INF_X + ((float) (rand()%1000))/1000;
        particula[i].posicao.y = LIMITE_INF_Y + ((float) (rand()%1000))/1000;

        //Define fitness da posição atual e atualiza pb
        particula[i].posicao.fitness = fitness(particula[i].posicao);
        particula[i].pb = particula[i].posicao;

        //Checa se pb da particula é o gb
        if(particula[i].pb.fitness > gb->fitness)
            *gb = particula[i].pb;
    }

    //Inicializa velocidade de cada partícula
    for(i = 0; i < n; ++i)
    {
        r1 = ((float) (rand()%1000))/1000;
        r2 = ((float) (rand()%1000))/1000;

        particula[i].velocidade.fitness = -1;
        particula[i].velocidade.x = c1*r1*(particula[i].pb.x - particula[i].posicao.x)
                                    + c2*r2*(gb->x - particula[i].posicao.x);
        particula[i].velocidade.y = c1*r1*(particula[i].pb.y - particula[i].posicao.y)
                                    + c2*r2*(gb->y - particula[i].posicao.y);
    }
}

float fitness(Ponto p)
{
    return 0.5 * (cos(16*PI*p.x) + cos(16*PI*p.y)) * exp((-3.5) * (pow(p.x-(0.5), 2) + pow(p.y-(0.5), 2)));
}
