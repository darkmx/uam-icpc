/**
 * Nombre: Algoritmo Knuth-Morris-Pratt
 * Autor: rcc
 * Descripción: La función \textit{tabla\_kmp[i]} calcula la longitud del prefijo más largo de la
 *              cadena \textit{s} que termina en \textit{i}, excluyendo la subcadena \textit{s[0...i]}
 *              en sí misma (por ejemplo, para \textit{abacaba} $\rightarrow$ \textit{0010123}).
 *              Puede usarse para encontrar todas las ocurrencias de una cadena.
 * Complejidad: $O(n)$
 * Uso:
 *  auto tabla = tabla_kmp(patron);
 *  auto ocurrencias = busca(patron, texto, tabla);
 */
#include <string>
#include <vector>
#include <stddef.h>

std::vector<size_t> tabla_kmp(const std::string& s) {
   std::vector<size_t> b = { size_t(-1) };
   for (size_t i = 0, j = -1; i < s.size( ); ++i) {
      while (j != -1 && s[i] != s[j]) {
         j = b[j];
      }
      b.push_back(++j);
   }
   return b;
}

std::vector<size_t> busca(const std::string& s, const std::string& t, const std::vector<size_t>& b) {
   std::vector<size_t> res;
   for (size_t i = 0, j = 0; i < t.size( ); ++i) {
      while (j != -1 && t[i] != s[j]) {
         j = b[j];
      }
      if (++j == s.size( )) {
         res.push_back(i + 1 - s.size( ));
         j = b[j];
      }
   }
   return res;
}
