//
// Created by gugav on 27/11/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include "algoritmo.h"

float* init_dados(char* nome, int* n, float* V);
void gera_sol_inicial(int* sol, int n);
void escreve_sol(int* sol, int n, float* moedas);
float calcula_soma(int* sol, float* moedas, int n);
void substitui(int* dest, int* src, int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01() ;
pchrom init_pop(struct info d);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d) ;

#endif //UTILS_H
