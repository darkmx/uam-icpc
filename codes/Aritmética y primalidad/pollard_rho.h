/**
 * Nombre: Factorización de números grandes
 * Autor: kactl
 * Descripción: Algoritmo de Pollard Rho. $factoriza$ toma un número entero $n \ge 2$ y devuelve
 * un vector con los factores primos de $n$ en orden arbitrario. Por ejemplo, para $n = 2299$, puede devolver $\{11, 19, 11\}$.
 * Complejidad: $O(n^{1/4})$
 */
#include <numeric>
#include <vector>
#include <stdint.h>
#include "miller_rabin.h"

int64_t factor_pollard_rho(int64_t n, int64_t c) {
   int64_t x = 2, y = 2, k = 2;
   for (int64_t i = 2; ; ++i) {
      x = ((__int128_t(x) * x) % n) + c;
      if (x >= n)	{
         x -= n;
      }
      int64_t d = std::gcd(x - y, n);
      if (d != 1) {
         return d;
      }
      if (i == k) {
         y = x, k *= 2;
      }
   }
}

std::vector<int64_t> factoriza(int64_t n) { // suposición: n >= 2
   std::vector<int64_t> factores;
   if (primalidad_miller_rabin(n)) {
      factores.push_back(n);
   } else {
      for (int64_t i = 2; ; i++) {
         auto checar = factor_pollard_rho(n, i);
         if (checar != n) {
            std::vector<int64_t> factores1 = factoriza(checar);
            std::vector<int64_t> factores2 = factoriza(n / checar);
            factores.insert(factores.end( ), factores1.begin( ), factores1.end( ));
            factores.insert(factores.end( ), factores2.begin( ), factores2.end( ));
            break;
         }
      }
   }
   return factores;
}
