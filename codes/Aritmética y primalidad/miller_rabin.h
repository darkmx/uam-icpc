/**
 * Nombre: Primalidad Miller Rabin
 * Autor: kactl
 * Descripción: Prueba de primalidad determinista de Miller-Rabin.
 * Complejidad: $O(\log p)$.
 */
#include <stdint.h>
#include "potencia_mod.h"

bool es_primo(int64_t n) {
   if (n < 2) {
      return false;
   }

   int64_t d = n - 1, s = 0;
   while (d % 2 == 0) {
      d /= 2, s += 1;
   }
   auto compuesto_con = [&](int64_t a) {
      int64_t x = potencia(a, d, n);
      if (x == 1 || x == n - 1) {
         return false;
      }
      for (int64_t r = 1; r < s; ++r) {
         x = (__int128_t(x) * x) % n;
         if (x == n - 1) {
            return false;
         }
      }
      return true;
   };

   for (int64_t a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
      if (n == a) {
         return true;
      } else if (compuesto_con(a)) {
         return false;
      }
   }
   return true;
}
