/**
 * Nombre: Euclides extendido
 * Autor: rcc
 * Descripción: Encuentra dos enteros $x$ e $y$, tales que $ax+by=\gcd(a,b)$.
 * Complejidad: $O(\log(\min(a, b)))$
 */
#include <stdint.h>

int64_t euclides_extendido(int64_t a, int64_t b, int64_t& x, int64_t& y) {
   x = 1, y = 0;
   int64_t x1 = 0, y1 = 1, a1 = a, b1 = b;
   while (b1) {
      int64_t q = a1 / b1;
      std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
      std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
      std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
   }
   return a1;
}
