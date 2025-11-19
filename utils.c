//
// Created by gugav on 27/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "algoritmo.h"
#include <time.h>


float* init_dados(char* nome, int* n, float* V) {
    FILE* f = fopen(nome, "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }

    fscanf(f, "%d %f", n, V);

    float* moedas = malloc((*n) * sizeof(float));
    if (moedas == NULL) {
        printf("Erro na alocacao de memoria.\n");
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *n; i++) {
        fscanf(f, "%f", &moedas[i]);
    }

    fclose(f);
    return moedas;
}

// Gera uma solução inicial aleatória
void gera_sol_inicial(int* sol, int n) {
    // Inicializa cada elemento da solução com um valor aleatório
    for (int i = 0; i < n; i++) {
        sol[i] = random_l_h(0,10); // Escolhe um número aleatório entre 0 e 10 moedas
    }
}

// Escreve uma solução no terminal (só usamos no trepa colinas)
void escreve_sol(int* sol, int n, float* moedas) {
    printf(" : ");
    for (int i = 0; i < n; i++) {
        printf("[%d] x %.2f ", sol[i], moedas[i]);
    }
    printf(" = %.2f euros", calcula_soma(sol, moedas,n));

    printf("\n");
}

// Calcula a soma de uma solução em relação ao valor total
float calcula_soma(int *sol, float *moedas, int n) {
    float soma = 0;
    for (int i = 0; i < n; i++) {
        soma += (float)sol[i] * moedas[i];
    }
    return soma;
}

// Substitui um vetor pelo outro
void substitui(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}
// Inicializa o gerador de numeros aleatorios
void init_rand()
{
    srand((unsigned)time(NULL));
}

pchrom init_pop(struct info d) {
    int i, j;
    pchrom indiv;

    // Aloca espaço para a população
    indiv = malloc(sizeof(chrom) * d.popsize);
    if (indiv == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    // Gera cada indivíduo da população inicial
    for (i = 0; i < d.popsize; i++) {
        // Aloca espaço para o cromossomo (genes)
        indiv[i].p = malloc(sizeof(int) * d.numGenes);
        if (indiv[i].p == NULL) {
            printf("Erro na alocacao de memoria para os genes\n");
            exit(1);
        }

        // Inicializa cada gene com um número aleatório de moedas (entre 0 e 10, por exemplo)
        for (j = 0; j < d.numGenes; j++) {
            indiv[i].p[j] = random_l_h(0, 10);
        }
        indiv[i].fitness = 0; // Inicializa o fitness como 0
    }
    return indiv;
}

// Actualiza a melhor solucao encontrada
// Parametro de entrada: populacao actual (pop), estrutura com parametros (EA_param) e a melhor solucao encontrada ate a geracao imediatamente anterior (best)
// Parametro de saida: a melhor solucao encontrada ate a geracao actual
chrom get_best(chrom *pop, struct info EA_param, chrom best) {
    for (int i = 0; i < EA_param.popsize; i++) {
        if (pop[i].valido == 1 && pop[i].fitness < best.fitness) {
            // Atualiza o fitness e os genes do melhor indivíduo
            best.fitness = pop[i].fitness;
            best.valido = pop[i].valido;

            // Copia os genes da solução
            for (int j = 0; j < EA_param.numGenes; j++) {
                best.p[j] = pop[i].p[j];
            }
        }
    }
    return best;
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
    return ((float)rand())/RAND_MAX;
}

// Escreve a melhor solução encontrada
// Parâmetros de entrada: melhor indivíduo (x) e estrutura com parâmetros do problema (d)
void write_best(chrom x, struct info d) {
    int i;

    // Exibe o fitness da solução (menor é melhor)
    printf("\nMelhor solucao: %.2f\n", x.fitness);
    printf("Solucao: [");

    // Exibe os genes da solução
    for (i = 0; i < d.numGenes; i++) {
        printf(" %d ", x.p[i]); // Mostra as moedas ou elementos da solução
    }

    printf("]");
    putchar('\n');
}










