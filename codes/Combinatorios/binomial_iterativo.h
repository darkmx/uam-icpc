/**
 * Nombre: Coeficiente binomial iterativo
 * Autor: rcc
 * Descripción: El número de subconjuntos de $k$ elementos de un conjunto de $n$ elementos,
 *              $\binom{n}{k} = \frac{n!}{k!(n-k)!}$.
 * Complejidad: $O(k)$
 */
#include <stdint.h>

uint64_t binomial(int n, int k) {
   __uint128_t res = 1;
   // uint64_t es más rápido pero falla en casos raros
   for (int i = 1; i <= k; ++i) {
      res *= n + 1 - i;
      res /= i;
   }
   return res;
}
