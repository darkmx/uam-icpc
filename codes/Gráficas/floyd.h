/**
 * Nombre: Algoritmo de Floyd
 * Autor: rcc
 * Descripción: Calcula el camino más corto entre cualquier pareja de vértices en un grafo dirigido.
 * Complejidad: $O(n^3)$
 */

// adyacencia[i][j] es la matriz original
// la siguiente implementación la modifica
for (int k = 0; k < n; ++k) {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         adyacencia[i][j] = std::min(adyacencia[i][j], adyacencia[i][k] + adyacencia[k][j]);
      }
   }
}
