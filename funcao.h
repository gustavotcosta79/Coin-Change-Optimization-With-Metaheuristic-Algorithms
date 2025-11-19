//
// Created by gugav on 27/11/2024.
//

#ifndef FUNCAO_H
#define FUNCAO_H
#include "algoritmo.h"
#include "utils.h"
#include <math.h>
double eval_individual(int sol[], struct info d, float *moedas, float V, int n, int *v);
void evaluate(pchrom pop, struct info d, float *moedas, float V, int n);


#endif // FUNCAO_H
