/**
 * Nombre: Algoritmo de Bellman-Ford
 * Autor: rcc
 * Descripción: El algoritmo de Bellman-Ford encuentra los caminos más cortos desde un vértice inicial $s$ hacia todos los
 *              demás vértices de una gráfica dirigida con costos negativos (pero sin ciclos negativos).
 * Complejidad: $O(nm)$
 */
#include <iostream>
#include <vector>
#include <algorithm>

struct tupla {
   int origen, destino, costo;
};

int main( ) { ///include-line
   int n, m;
   std::cin >> n >> m;

   std::vector<std::vector<tupla>> adyacencia(n);
   for (int i = 0; i < m; ++i) {
      int x, y, c;
      std::cin >> x >> y >> c;
      adyacencia[x].push_back({ x, y, c });     // sólo en un sentido: deben ser arcos
   }

   std::vector<int> distancias(n, 1e9);
   distancias[0] = 0;
   for (int k = 0; k < n - 1; ++k) {
      for (int i = 0; i < n; ++i) {
         if (distancias[i] != 1e9) {
            for (tupla t : adyacencia[i]) {
               distancias[t.destino] = std::min(distancias[t.destino], distancias[i] + t.costo);
            }
         }
      }
   }

   for (int i = 0; i < n; ++i) {
      std::cout << i << ": " << distancias[i] << "\n";
   }
}
