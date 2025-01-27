/**
 * Nombre: Potencia rápida modular
 * Autor: rcc
 * Descripción: Calcula $a^b \mod c$.
 * Complejidad: $O(\log b)$
 */
#include <stdint.h>

int64_t potencia(int64_t b, int64_t e, int64_t mod) {
   int64_t res = 1; b %= mod;
   while (e != 0) {
      if (e % 2 == 1) {
         res = (__int128_t(res) * b) % mod;
      }
      b = (__int128_t(b) * b) % mod;
      e /= 2;
   }
   return res;
}
