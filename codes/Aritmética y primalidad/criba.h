/**
 * Nombre: Criba de Eratóstenes
 * Autor: rcc
 * Descripción: Criba de Eratóstenes para encontrar todos los números primos hasta un límite dado.
 *              Los números primos se almacenan en $primos$, y $factor$ guarda el guarda el mayor factor primo de cada número.
 * Complejidad: $O(n\log\log n)$
 */
#include <vector>
#include <stdint.h>

struct criba {
   int tope;
   std::vector<bool> es_primo;
   std::vector<int> menor_factor;

   criba(int t)
   : tope(t), es_primo(t + 1, true), menor_factor(t + 1) {
      es_primo[0] = es_primo[1] = false;
      for (int i = 2; i <= tope; i++) {
         if (es_primo[i]) {
            menor_factor[i] = i;
            for (auto j = (std::size_t)i * i; j <= tope; j += i) {
               es_primo[j] = false;
               if (menor_factor[j] == 0) {
                  menor_factor[j] = i;
               }
            }
         }
      }
   }
};
