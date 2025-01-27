/**
 * Nombre: Algoritmos de Dijkstra y Prim
 * Autor: rcc
 * Descripción: El algoritmo de Dijkstra encuentra los caminos más cortos desde un vértice inicial $s$ hacia todos los
 *              demás vértices del grafo con costos no negativos. El árbol abarcador de costo mínimo, que se obtiene usando
 *              el algoritmo de Prim, es un conjunto de aristas que conecta todos los vértices con el menor costo total posible.
 * Complejidad: $O(m\log n)$
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct tupla {
   int origen, destino, costo;
};

bool operator<(tupla a, tupla b) {
   return a.costo > b.costo;
}

int main( ) { ///include-line
   int n, m;
   std::cin >> n >> m;

   std::vector<tupla> adyacencia[n];
   for (int i = 0; i < m; ++i) {
      int x, y, c;
      std::cin >> x >> y >> c;
      adyacencia[x].push_back({ x, y, c });
      adyacencia[y].push_back({ y, x, c });
   }

   std::priority_queue<tupla> cp;
   cp.push({0, 0, 0});
   int costo[n], previo[n];
   std::fill(&costo[0], &costo[n], -1);
   do {
      tupla t = cp.top( );
      cp.pop( );
      if (costo[t.destino] == -1) {
         costo[t.destino] = t.costo;
         previo[t.destino] = t.origen;
         for (tupla vecino : adyacencia[t.destino]) {
            vecino.costo += t.costo;  // quitar para Prim
            cp.push(vecino);
         }
      }
   } while (!cp.empty( ));

   for (int i = 0; i < n; ++i) {
      std::cout << i << ": " << costo[i] << " " << previo[i] << "\n";
   }
}
