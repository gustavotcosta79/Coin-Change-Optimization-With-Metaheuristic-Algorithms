#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

#define CRT_SECURE_NO_WARNINGS 1

#define DEFAULT_RUNS 2

int main(int argc, char *argv[]) {
    char nome_fich[100];

    struct info EA_param;
    int gen_actual, r, runs, i, n, inv,*sol, *best, num_iter, custo, best_custo;
    float V, mbf = 0.0;
    float *moedas = NULL;
    chrom *pop = NULL, *parents = NULL, best_run, best_ever;

    // Leitura dos argumentos de entrada
    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }

    // Verifica se o número de execuções é válido
    if (runs <= 0)
        return 0;

    // Inicializa a geração de números aleatórios
    init_rand();

    // Lê os dados do problema
    moedas = init_dados(nome_fich, &n, &V);
    if (moedas == NULL) {
        printf("Erro ao ler o ficheiro.\n");
        return -1;
    }

   /* ///------------------------------------TREPA----------------------

    sol = malloc(sizeof(int) * n);
    best = malloc(sizeof(int) * n);
    if (sol == NULL || best == NULL) {
        printf("Erro na alocacao de memória.\n");
        free(moedas);
        return -1;
    }

    // Execução de múltiplas runs
    for (int k = 0; k < runs; k++) {
        printf("\nRun %d:", k + 1);
        // Geração de solução inicial
        gera_sol_inicial(sol, n);
        printf ("\nSolucao inicial");
        escreve_sol(sol, n, moedas);

        // Trepa-colinas para otimização
        num_iter = 10000;  // Número de iterações
        custo = trepa_colinas(sol, moedas, n, V, num_iter);

        // Atualização do melhor custo
        if (k == 0 || custo < best_custo) {
            best_custo = custo;
            substitui(best, sol, n);
        }

        // Acumulação do custo para cálculo da MBF
        mbf += custo;

        //printf("\nRun %d:", k + 1);
        printf("solucao");

        escreve_sol(sol, n, moedas);
        printf("Custo: %d\n", custo);
    }

    // Resultados finais
    printf("\nMelhor solucao encontrada");
    escreve_sol(best, n, moedas);
    printf("Custo: %d\n", best_custo);
    printf("MBF: %.2f\n", mbf / runs);

    // Liberação de memória
    free(sol);
    free(best);
    free(moedas);
    return 0;
}
*/
    ///-------------------------- ------------------------------------

    ///------------------------------------ALGORITMO EVOLUTIVO----------------------

    // Inicializa os parâmetros do algoritmo genético
    EA_param.popsize = 100;         // Tamanho da população
    EA_param.numGenerations = 2500; // Número de gerações
    EA_param.pr = 0.7;            // Probabilidade de recombinação
    EA_param.pm = 0.001;            // Probabilidade de mutação
    EA_param.numGenes = n;        // Número de genes (moedas)
    EA_param.crossover_type = 1;  // Tipo de crossover (1 ponto) / crossover uniforme
    EA_param.mutation_type = 1;   // Tipo de mutação (simples) / mutacao por troca
    EA_param.tsize = 2;           // Tamanho do torneio

    // Executa o algoritmo genético para o número de repetições especificado
    for (r = 0; r < runs; r++) {
        // Gera a população inicial
        pop = init_pop(EA_param);


        ///Abordagem 1

        for (int i = 0; i < EA_param.popsize; i++) {
            int custo = run_trepa_colinas(pop[i].p, moedas, EA_param.numGenes, V, num_iter);
            pop[i].fitness = custo; // Atualiza o fitness com o custo do trepa colinas
        }


        // Avalia a população inicial
        evaluate(pop, EA_param, moedas, V, n);

        gen_actual = 1;
        //best_run = pop[0]; // Inicializa a melhor solução com a primeira solução da população

        best_run.fitness = pop[0].fitness; // Inicializa com um valor muito alto
        best_run.p = pop[0].p;
        //best_run = get_best(pop, EA_param, best_run);

        // Reserva espaço para os pais
        parents = malloc(sizeof(chrom) * EA_param.popsize);
        if (parents == NULL) {
            printf("Erro na alocacao de memoria.\n");
            exit(1);
        }

        // Ciclo de otimização
        while (gen_actual <= EA_param.numGenerations) {
            printf("Geracao %d de %d\n", gen_actual, EA_param.numGenerations);

            // Seleção por torneio
            //tournament(pop,EA_param,parents);
            tournament_nElementos(pop, EA_param, parents);

            // Aplica operadores genéticos
            genetic_operators(parents, EA_param, pop);

            //Reparo dos descendentes gerados
            for ( int x = 0; x < EA_param.popsize; x++) {
                repair(parents[x].p, parents[x].p, EA_param.numGenes, moedas, V);
            }

            // Avalia a nova população
            evaluate(pop, EA_param, moedas, V, n);

            ///ABORDAGEM2
            //chrom best_ind = get_best(pop, EA_param, best_run);
            //run_trepa_colinas(best_ind.p, moedas, EA_param.numGenes, V, 100); // 100 iterações

            // Exibe informações sobre a população após a avaliação
            printf("Apos avaliacao da geracao %d:\n", gen_actual);
            for (int i = 0; i < EA_param.popsize; i++) {
                for (int j = 0; j < EA_param.numGenes; j++) {
                    if (j < EA_param.numGenes - 1) {
                    }
                }

            }

            // Atualiza a melhor solução encontrada
            best_run = get_best(pop, EA_param, best_run);

            // Exibe a melhor solução encontrada até agora
            printf("Melhor solucao apos a geracao %d: Fitness = %.2f ",
                   gen_actual, best_run.fitness);
            printf(" [");

            // Exibe os valores das moedas (genes) da melhor solução
            for ( i = 0; i < EA_param.numGenes; i++) {
                printf("%d ", best_run.p[i]); // Aqui mostra o valor de cada moeda na solução
            }

            printf("]\n"); // Fecha a exibição da solução
            gen_actual++;
        }

        // Contagem de soluções inválidas
        for (inv = 0, i = 0; i < EA_param.popsize; i++) {
            if (pop[i].valido == 0)
                inv++;
        }

        // Exibe os resultados da repetição
        printf("\nRepeticao %d:", r + 1);
        write_best(best_run, EA_param);
        //printf("Percentagem de Invalidos: %.2f%%\n", 100 * (float)inv / EA_param.popsize);
        mbf += best_run.fitness;

        // Atualiza a melhor solução global
        if (r == 0 || best_run.fitness < best_ever.fitness)
            best_ever = best_run;

        free(parents);
        free(pop);


    }

    // Exibe os resultados finais
    printf("\n\nMBF: %f", mbf / runs);
    printf("\nMelhor solucao encontrada:\n");
    write_best(best_ever, EA_param);

    // Libera a memória alocada para as moedas
    free_population(pop,EA_param.popsize);
    free_population(parents,EA_param.popsize);
    free(moedas);
    return 0;

}

