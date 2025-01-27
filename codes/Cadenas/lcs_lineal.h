/**
 * Nombre: LCS con memoria lineal
 * Autor: rcc
 * Descripción: Regresa la longitud de la subsecuencia común más larga usando memoria lineal.
 * Complejidad: $O(nm)$
 */
#include <algorithm>
#include <string>

int lcs(const std::string& a, const std::string& b) {
   int mem[2][b.size( ) + 1];
   int *actual = mem[0], *previo = mem[1];
   for (int i = a.size( ); i >= 0; --i, std::swap(actual, previo)) {
      for (int j = b.size( ); j >= 0; --j) {
         if (i == a.size( ) || j == b.size( )) {
            actual[j] = 0;
         } else if (a[i] == b[j]) {
            actual[j] = 1 + previo[j + 1];
         } else {
            actual[j] = std::max(actual[j + 1], previo[j]);
         }
      }
   }
   return previo[0];
}
