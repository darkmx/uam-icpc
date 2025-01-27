/**
 * Nombre: Inverso modular
 * Autor: rcc
 * Descripción: Encuentra $x$ en $[0,m)$ tal que $ax \equiv 1 \mod m$.
 * Complejidad: $O(\log(m))$
 */
#include <stdint.h>

constexpr int64_t inverso(int64_t a, int64_t m) {
   return a <= 1 ? a : m - (m/a) * inverso(m % a, m) % m;
}
