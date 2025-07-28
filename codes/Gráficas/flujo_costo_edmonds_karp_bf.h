/**
 * Nombre: Algoritmo de Edmonds-Karp con costos usando Bellman-Ford
 * Autor: rcc
 * Descripción: Algoritmo de flujo máximo de costo mínimo de una gráfica de $n$ vértices y $m$ aristas.
 * Complejidad: $O(n m^2)$
 * Estado: probado en omegaup.com/arena/problem/El-problema-de-asignacion
 * Uso:
 *   edmonds_karp_bf<int> f(n, s, t);
 *   f.agrega_arco(i, j, c);
 *   auto [flujo, costo] = f.flujo_maximo( );
 *   if (f.cap[j][i] != 0) {
 *   	// se enviaron f.cap[j][i] unidades de flujo de i a j
 *   }
 */
#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

template<typename T, typename D = T>
struct edmonds_karp_bf {
   int fuente, sumidero;
   std::vector<std::vector<int>> adj;
   std::vector<std::vector<T>> cap;
   std::vector<std::vector<D>> costo;

   edmonds_karp_bf(int n, int f, int s)
   : fuente(f), sumidero(s), adj(n), cap(n, std::vector<T>(n)), costo(n, std::vector<T>(n)) {
   }

   void agrega_arco(int i, int j, T c, D d) {   // no se admiten arcos paralelos
      if (i != j && c != 0) {
         adj[i].push_back(j);
         adj[j].push_back(i);
         cap[i][j] = c;
         costo[i][j] = d;
         costo[j][i] = -d;
      }
   }

   std::pair<T, T> flujo_maximo( ) {
      T flujo_total = 0; D costo_total = 0;
      for (;;) {
         auto [delta, camino] = aumenta( );
         if (delta == 0) {
            return { flujo_total, costo_total };
         }
         flujo_total += delta;
         for (auto [i, j] : camino) {
            costo_total += delta * costo[i][j];
            cap[i][j] -= delta;
            cap[j][i] += delta;
         }
      }
   }

private:
   std::pair<T, std::vector<std::pair<int, int>>> aumenta( ) {
      D inf = std::numeric_limits<D>::max( ) / 2;
      std::vector<int> anterior(adj.size( ), -1);
      std::vector<D> min(adj.size( ), inf);
      min[fuente] = 0;
      for (int k = 0; k < adj.size( ) - 1; ++k) {
         for (int i = 0; i < adj.size( ); ++i) {
            for (int j : adj[i]) {
               if (cap[i][j] > 0 && min[j] > min[i] + costo[i][j]) {
                  min[j] = min[i] + costo[i][j];
                  anterior[j] = i;
               }
            }
         }
      }
      if (min[sumidero] == inf) {
         return { 0, { } };
      }

      T cuello = inf; int i = sumidero;
      std::vector<std::pair<int, int>> camino;
      do {
         camino.emplace_back(anterior[i], i);
         cuello = std::min(cuello, cap[anterior[i]][i]);
         i = anterior[i];
      } while (i != fuente);
      return { cuello, camino };
   }
};
