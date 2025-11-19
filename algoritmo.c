//
// Created by gugav on 27/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "utils.h"


// Função para executar o trepa colinas e retornar o custo da solução otimizada
int run_trepa_colinas(int *sol, int *moedas, int n, float V, int num_iter) {
    int custo_atual, melhor_custo;
    int *nova_sol = malloc(sizeof(int) * n);
    int *melhor_sol = malloc(sizeof(int) * n);

    if (nova_sol == NULL || melhor_sol == NULL) {
        printf("Erro na alocação de memória para as soluções.\n");
        if (nova_sol) free(nova_sol);
        if (melhor_sol) free(melhor_sol);
        return -1;
    }

    // Inicializa a melhor solução como a solução inicial
    substitui(melhor_sol, sol, n);
    melhor_custo = calcula_custo(sol, moedas, n, V);

    for (int iter = 0; iter < num_iter; iter++) {
        // Gera uma solução vizinha com base na solução atual
        int prob = rand() % 100;  // Gera um número entre 0 e 100 (algoritmo hidrido)
        if(prob > 20)
        gera_vizinho(sol, nova_sol, n);

        // Calcula o custo da solução vizinha
        custo_atual = calcula_custo(nova_sol, moedas, n, V);

        // Atualiza a melhor solução caso a vizinha seja melhor
        if (custo_atual <= melhor_custo) {
            substitui(melhor_sol, nova_sol, n);
            melhor_custo = custo_atual;
        } else {
            substitui(nova_sol, sol, n);
        }

        // Atualiza a solução atual com a melhor até agora
        substitui(sol, melhor_sol, n);
    }

    free(nova_sol);
    free(melhor_sol);
    return melhor_custo;
}

void repair(int *sol, int *nova_sol, int n, float *moedas, float V) {
    // Copia a solução original
    for (int i = 0; i < n; i++) {
        nova_sol[i] = sol[i];
    }

    // Calcula a soma inicial
    float soma = calcula_soma(nova_sol, moedas, n);

    // Passo 1: Ajustar soma para que esta seja exatamente V
    int max_iter = 1000, iter = 0;

    while (fabs(soma - V) > 0.01 && iter < max_iter) {
        iter++;

        if (soma < V) {
            int idx = random_l_h(0, n - 1);
            nova_sol[idx]++;
        } else if (soma > V) {
            int idx;
            do {
                idx = random_l_h(0, n - 1);
            } while (nova_sol[idx] <= 0);
            nova_sol[idx]--;
        }

        soma = calcula_soma(nova_sol, moedas, n);
    }

    // Passo 2: Minimizar o numero de moedas
    for (int i = 0; i < n; i++) {
        while (nova_sol[i] > 0) {
            // Remove uma moeda e verifica se a solução ainda é válida
            nova_sol[i]--;
            soma = calcula_soma(nova_sol, moedas, n) ;

            if (soma < V - 0.01) {
                // Se a soma ficou inválida, restaura a moeda
                nova_sol[i]++;
                break;
            }
        }
    }

}

// Função para gerar um vizinho
void gera_vizinho(int* sol, int* nova_sol, int n) {
    substitui(nova_sol, sol, n);
    int p1, p2;

    // Encontra uma posição com valor maior que 0
    do {
        p1 = random_l_h(0, n - 1);
    } while (nova_sol[p1] <= 0);

    // Encontra uma posição diferente de p1
    do {
        p2 = random_l_h(0, n - 1);
    } while (p2 == p1);

    // Realiza a operação de troca
    nova_sol[p1] -= 1; // Remove uma unidade de p1
    nova_sol[p2] += 1; // Adiciona uma unidade em p2

    do {
        p1 = random_l_h(0, n - 1);
    } while (nova_sol[p1] <= 0);

    // Encontra uma posição diferente de p1
    do {
        p2 = random_l_h(0, n - 1);
    } while (p2 == p1);

    // Realiza a operação de troca
    nova_sol[p1] -= 1; // Remove uma unidade de p1
    nova_sol[p2] += 1; // Adiciona uma unidade em p2


}


// Calcula o custo de uma solução
int calcula_custo(int* sol, float* moedas, int n, float V) {
    double soma = calcula_soma(sol, moedas, n);
    int total_moedas = 0;

    for (int i = 0; i < n; i++) {
        total_moedas += sol[i];
    }

    if (fabs(soma - V) > 0.01) {
        return (int)fabs(soma - V) + 1000;  // Penalização para soluções inválidas
    }

    return total_moedas; // Retorna o número de moedas (custo)
}

    void genetic_operators(pchrom parents, struct info d, pchrom offspring) {
        // Recombinação
        if (d.crossover_type == 1) {  // Tipo 1: Crossover de 1 ponto
            crossover(parents, d, offspring);
        } else if (d.crossover_type == 2) {  // Tipo 2: Crossover uniforme
            crossover_uniforme(parents, d, offspring);
        }

        // Mutação
        if (d.mutation_type == 1) {  // Tipo 1: Mutação simples
            mutation(offspring, d);
        } else if (d.mutation_type == 2) {  // Tipo 2: Mutação por troca
            mutation_swap(offspring, d);
        }
        //printf("passei aqui");
    }

void tournament(pchrom pop, struct info d, pchrom offspring) {
    int i, j, best, contender;

    for (i = 0; i < d.popsize; i++) {
        best = random_l_h(0, d.popsize - 1);  // Escolhe o primeiro indivíduo aleatoriamente

        // Realiza o torneio entre "tournament_size" indivíduos
        for (j = 1; j < d.tsize; j++) {
            contender = random_l_h(0, d.popsize - 1);  // Escolhe outro indivíduo aleatório
            // Escolhe o melhor entre o atual melhor e o contender com base no fitness
            if (pop[contender].fitness < pop[best].fitness) {  // Melhor fitness = menor custo
                best = contender;
            }
        }

        // Copia o vencedor do torneio para a próxima geração
        offspring[i] = pop[best];
    }
}

void tournament_nElementos(pchrom pop, struct info d, pchrom parents) {
    int i, new_x, contador, to_discard;
    int tournament_size = d.tsize; // Tamanho do torneio
    int x[tournament_size]; // Indivíduos no torneio
    float this_fitness, best_fitness;

    // Realiza um torneio para cada posição dos parents (pais)
    for (i = 0; i < d.popsize; i++) {
        contador = 1; // Contador de participantes no torneio
        x[0] = random_l_h(0, d.popsize - 1); // Primeiro indivíduo do torneio
        best_fitness = pop[x[0]].fitness;

        // Copia o primeiro indivíduo como o "melhor" por enquanto
        parents[i] = pop[x[0]];

        while (contador < tournament_size) {
            to_discard = 0; // Flag para descartar repetidos
            new_x = random_l_h(0, d.popsize - 1); // Novo participante do torneio

            // Verifica se o novo participante já está no torneio
            for (int j = 0; j < contador; j++) {
                if (x[j] == new_x) {
                    to_discard = 1;
                    break;
                }
            }

            // Se o participante não está no torneio, adiciona
            if (to_discard == 0) {
                x[contador] = new_x; // Adiciona o índice do novo participante
                this_fitness = pop[new_x].fitness;

                // Verifica se é uma solução válida e com melhor fitness (minimização)
                if (pop[new_x].valido == 1 && this_fitness < best_fitness) {
                    parents[i] = pop[new_x]; // Atualiza o melhor indivíduo
                    best_fitness = this_fitness;
                }

                contador++; // Incrementa o número de participantes do torneio
            }
        }
    }
}


void free_population(pchrom pop, int popsize) {
    for (int i = 0; i < popsize; i++) {
        free(pop[i].p); // Libera os genes de cada indivíduo
    }
    free(pop); // Libera a população
}


void crossover(pchrom parents, struct info d, pchrom offspring) {
    int i, j, point;

    for (i = 0; i < d.popsize; i += 2) {
        if (rand_01() < d.pr) {  // Probabilidade de recombinação
            point = random_l_h(0, d.numGenes - 1);  // Escolhe o ponto de corte
            for (j = 0; j < point; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for (j = point; j < d.numGenes; j++) {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        } else {  // Sem crossover, apenas copia os pais para os filhos
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void crossover_uniforme(pchrom parents, struct info d, pchrom offspring) {
    int i, j;

    for (i = 0; i < d.popsize; i += 2) {
        offspring[i] = parents[i];
        offspring[i + 1] = parents[i + 1];
        for (j = 0; j < d.numGenes; j++) {
            if (parents[i].p[j] != parents[i + 1].p[j] && rand_01() < d.pr) {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        }
    }
}


void mutation(pchrom offspring, struct info d) {
    int i, j;

    for (i = 0; i < d.popsize; i++) {
        for (j = 0; j < d.numGenes; j++) {
            if (rand_01() < d.pm) {  // Probabilidade de mutação
                offspring[i].p[j] = random_l_h(0, 10);
            }
        }
    }
}

void mutation_swap(pchrom offspring, struct info d) {
    int i, obj1, obj2;

    // Para cada indivíduo na população
    for (i = 0; i < d.popsize; i++) {
        // Decide se realiza mutação para este indivíduo
        if (rand_01() < d.pm) {  // Probabilidade de mutação
            // Encontra dois índices diferentes para realizar o swap
            do {
                obj1 = random_l_h(0, d.numGenes - 1);
                obj2 = random_l_h(0, d.numGenes - 1);
            } while (obj1 == obj2);  // Garante que os índices não sejam iguais

            // Realiza a troca (swap) entre os genes selecionados
            int temp = offspring[i].p[obj1];
            offspring[i].p[obj1] = offspring[i].p[obj2];
            offspring[i].p[obj2] = temp;
        }
    }
}






