/**
 * Nombre: Código Lehmer
 * Autor: rcc
 * Descripción: Permutaciones a/desde enteros. La biyección preserva el orden lexicográfico.
 * Complejidad: $O(n^2)$
 */
#include <algorithm>
#include <numeric>

constexpr std::size_t factorial(std::size_t n) {
   return (n == 0 ? 1 : n * factorial(n - 1));
}

template<typename T>
std::size_t indice(T ini, T fin) {
   std::size_t n = fin - ini, r = factorial(n - 1), res = 0;
   for (T i = ini; i != fin; ++i) {
      res += r * std::count_if(i + 1, fin, [&](std::size_t v) { return v < *i; });
      if (fin - i - 1 != 0) {
         r /= fin - i - 1;
      }
   }

   return res;
}

template<typename T>
void permutacion(T ini, T fin, std::size_t indice) {
   std::iota(ini, fin, std::size_t(0));
   std::size_t n = fin - ini, r = factorial(n - 1);
   for (T i = ini; i != fin; ++i) {
      std::size_t d = indice / r; indice %= r;
      std::rotate(i, i + d, i + d + 1);
      if (fin - i - 1 != 0) {
         r /= fin - i - 1;
      }
   }
}
