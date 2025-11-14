/**
 * Nombre: Inverso modular
 * Autor: rcc
 * Descripción: Encuentra $x$ en $[0,m)$ tal que $ax \equiv 1 \mod m$ (Usa \textit{inverso\_compuesto} si $m$ no es primo).
 * Complejidad: $O(\log(m))$
 */
#include <stdint.h>
#include "euclides.h"

constexpr int64_t inverso(int64_t a, int64_t m) {
   return a <= 1 ? a : m - (m/a) * inverso(m % a, m) % m;
}

int64_t inverso_compuesto(int64_t a, int64_t m) {
   int64_t x, y;
   int64_t g = euclides_extendido(a, m, x, y);
   x %= m;
   if (x < 0) {
      x += m;
   }
   return x;
}
