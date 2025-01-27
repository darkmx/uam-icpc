/**
 * Nombre: Factorización básica
 * Autor: rcc
 * Descripción: Devuelve un vector ordenado con los factores primos de $n$.
 * Complejidad: $O(\sqrt{n})$
 */
#include <vector>
#include <math.h>
#include <stdint.h>

std::vector<int64_t> factoriza(int64_t n) {
   std::vector<int64_t> factores;
   int64_t raiz = std::round(std::sqrt(n));
   for (int64_t x = 2; x <= raiz; ++x) {
      while (n % x == 0) {
         factores.push_back(x);
         n /= x;
      }
   }
   if (n > 1) {
      factores.push_back(n);
   }
   return factores;
}
