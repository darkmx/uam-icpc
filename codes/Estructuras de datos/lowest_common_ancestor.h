/**
 * Nombre: Ancestro común más bajo
 * Autor: rcc
 * Descripción: Calcula el ancestro común de dos vértices a partir de haber precalculado un preorden aumentado o contorno.
 * Complejidad: $O(n \log n)$ para el preprocesamiento y $O(1)$ para las queries.
 * Uso:
 *  lowest_common_ancestor lca(tree_stats(raiz, adyacencia));
 *  int ancestro = lca.query(i, j);
 */
#include "tree_stats.h"
#include <algorithm>
#include <bit>
#include <vector>

struct lowest_common_ancestor {
   lowest_common_ancestor(tree_stats&& s)
   : primera(s.alturas.size( )), alturas(std::move(s.alturas)) {
      int tam = tabla.emplace_back(move(s.contorno)).size( );
      for (int i = tam - 1; i >= 0; --i) {
         primera[tabla[0][i]] = i;
      }
      for (int k = 2; k <= tam; k *= 2) {
         std::vector<int>& fila = tabla.emplace_back(tabla.back( ));
         for (int i = 0; i < tam; ++i) {
            fila[i] = selector(fila[i], fila[std::min(i + k / 2, tam - 1)]);
         }
      }
   }

   int query(int i, int j) const {
      int ini = std::min(primera[i], primera[j]), fin = std::max(primera[i], primera[j]) + 1;
      int t = std::bit_floor(unsigned(fin - ini)), x = std::countr_zero(unsigned(t));
      return selector(tabla[x][ini], tabla[x][ini + (fin - ini - t)]);
   }

   int selector(int i, int j) const {
      return (alturas[i] > alturas[j] ? i : j);
   }

private:
   std::vector<int> primera, alturas;
   std::vector<std::vector<int>> tabla;
};
