//
// Created by gugav on 27/11/2024.
//

#ifndef ALGORITMO_H
#define ALGORITMO_H

/*struct individual
{
    // Solução (objetos que estão dentro da mochila)
    int* p;
    // Valor da qualidade da solução
    float fitness;
    // 1 se for uma solução válida e 0 se não for
    int valido;
};

//typedef struct individual2 chrom, *pchrom;

 struct individual2{
    int* p;       // Cromossomo (solução)
    float fitness; // Avaliação da solução
};*/




typedef struct {
    int* p;       // Cromossomo (solução)
    float fitness; // Avaliação da solução
    int valido;
} chrom, *pchrom;

typedef chrom* pchrom; // Ponteiro para um vetor de cromossomos

struct info {
    int popsize;           // Tamanho da população
    int numGenerations;    // Número de gerações
    float pr;              // Probabilidade de recombinação (crossover)
    float pm;              // Probabilidade de mutação
    int numGenes;          // Número de genes
    int crossover_type;    // Tipo de crossover (1 = 1 ponto, 2 = uniforme)
    int mutation_type;     // Tipo de mutação (1 = simples, 2 = troca)
    int tsize;             // Tamanho do torneio
};


void gera_vizinho(int* sol, int* nova_sol, int n);
int calcula_custo(int* sol, float* moedas, int n, float V);
void repair(int* sol, int* nova_sol, int n, float* moedas , float V);
void crossover_uniforme(pchrom parents, struct info d, pchrom offspring);
void crossover(pchrom parents, struct info d, pchrom offspring);
void mutation(pchrom offspring, struct info d);
void mutation_swap(pchrom offspring, struct info d) ;
void free_population(pchrom pop, int popsize) ;
void tournament(pchrom pop, struct info d, pchrom offspring) ;
void tournament_nElementos(pchrom pop, struct info d, pchrom parents) ;
void genetic_operators(pchrom parents, struct info d, pchrom offspring);
int run_trepa_colinas(int *sol, int *moedas, int n, float V, int num_iter);

struct info1
{

    int popsize;     // Tamanho da população
    float pm;        // Probabilidade de mutação
    float pr;        // Probabilidade de recombinação
    int tsize;       // Tamanho do torneio para seleção do pai da próxima geração
    float ro;        // Constante para avaliação com penalização
    int numGenes;    // Número de genes (tamanho do cromossomo)
    int numGenerations;   // Número de gerações
    int crossover_type;   // Tipo de crossover (1 = 1 ponto, 2 = uniforme)
    int mutation_type;    // Tipo de mutação (1 = simples, 2 = troca)
};
//Individuo (solução)

//typedef struct individual chrom, *pchrom;


//typedef struct individual2 chrom, *pchrom;


#endif //ALGORITMO_H
