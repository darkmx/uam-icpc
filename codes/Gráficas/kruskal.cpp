/**
 * Nombre: Algoritmo de Kruskal
 * Autor: rcc
 * Descripción: Dado un grafo no dirigido y ponderado, se busca encontrar un árbol abarcador con el menor costo posible.
 * Complejidad: Complejidad: $O(m\log n)$
 */
#include <iostream>
#include <algorithm>
#include "union_pertenencia.h"

struct arista {
   int x, y, costo;
};

int main( ) { ///include-line
   int v, a;
   std::cin >> v >> a;

   std::vector<arista> aristas;
   for (int i = 0; i < a; ++i) {
      int x, y, costo;
      std::cin >> x >> y;
      aristas.push_back({ x, y, costo });
   }

   std::sort(aristas.begin( ), aristas.end( ), [](arista a, arista b) {
      return a.costo < b.costo;
   });

   union_find uf(v);

   for (int i = 0; i < aristas.size( ); ++i) {
      if (!uf.connected(aristas[i].x, aristas[i].y)) {
         uf.join(aristas[i].x, aristas[i].y);
      }
   }
}
