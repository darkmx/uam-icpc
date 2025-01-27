/**
 * Nombre: Coeficiente binomial modular
 * Autor: rcc
 * Descripción: Calcula $\binom{n}{k} \mod m$.
 * Complejidad: $O(\log(m))$
 */
#include "../Aritmética y primalidad/inverso_modular.h"

int64_t factorial[N + 1]; // N dado por el problema

int64_t binomial(int n, int k, int64_t m) {
   return factorial[n] * inverso(factorial[k] * factorial[n - k] % m, m) % m;
}
