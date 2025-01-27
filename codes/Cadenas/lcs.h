/**
 * Nombre: LCS con programación dinámica
 * Autor: rcc
 * Descripción: Devuelve un vector de pares de enteros $(i, j)$ que indican, respectivamente,
 *              las posiciones de las coincidencias en $a$ y $b$.
 * Complejidad: $O(n\cdot m)$
 */
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

auto lcs(const std::string& a, const std::string& b) {
   int mem[a.size( ) + 1][b.size( ) + 1];
   for (int i = a.size( ); i >= 0; --i) {
      for (int j = b.size( ); j >= 0; --j) {
       if (i == a.size( ) || j == b.size( )) {
            mem[i][j] = 0;
         } else if (a[i] == b[j]) {
            mem[i][j] = 1 + mem[i + 1][j + 1];
         } else {
            mem[i][j] = std::max(mem[i][j + 1], mem[i + 1][j]);
         }
      }
   }

   std::vector<std::pair<int, int>> res;
   int i = 0, j = 0;
   while (i < a.size( ) && j < b.size( )) {
      if (a[i] == b[j]) {
         res.emplace_back(i++, j++);
      } else if (mem[i][j] == mem[i][j + 1]) {
         ++j;
      } else {
         ++i;
      }
   }
   return res;
}
