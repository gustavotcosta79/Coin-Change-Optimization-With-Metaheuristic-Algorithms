//
// Created by gugav on 27/11/2024.
//

#include "funcao.h"


double eval_individual(int sol[], struct info d, float *moedas, float V, int n, int *v) {
    double soma = calcula_soma(sol, moedas, n); // Calcula a soma total das moedas usadas
    int total_moedas = 0;

    // Soma a quantidade de moedas usadas
    for (int i = 0; i < n; i++) {
        total_moedas += sol[i];
    }
    // Verifica se a solução é válida
    if (fabs(soma - V) <= 0.01) {
        *v = 1; // Solução válida
        return total_moedas; // Retorna o número de moedas usadas (menor valor é melhor)
    } else {
        *v = 0; // Solução inválida
        double penalizacao = 1000 + fabs(soma - V) * 100; // Penalização não cega
        return total_moedas + penalizacao; // Fitness penalizado
    }
}

// Avaliação da população
// Parâmetros de entrada: populacao (pop), estrutura com parâmetros (d), vetor de moedas e o valor alvo (V)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, float *moedas, float V, int n) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        // Calcula o fitness e a validade do indivíduo
        pop[i].fitness = eval_individual(pop[i].p, d, moedas, V, n, &pop[i].valido);
    }
}
