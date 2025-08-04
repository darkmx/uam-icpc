/**
 * Nombre: Algoritmo de Edmonds-Karp con costos usando el algoritmo de Johnson
 * Autor: rcc
 * Descripción: Algoritmo de flujo máximo de costo mínimo de una gráfica de $n$ vértices y $m$ aristas.
 * Complejidad: $O(F n \log m)$
 * Estado: probado en omegaup.com/arena/problem/Cobertura-minima-de-filas-y-colu
 * Uso:
 *   edmonds_karp_bf<int, int> f(n, s, t);
 *   f.agrega_arco(i, j, c);
 *   auto [flujo, costo] = f.flujo_maximo( );
 *   int t = f.flujo_arco(i, j);
 */
#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

template<typename C, typename D>
struct edmonds_karp_j {
   int fuente, sumidero;
   std::vector<std::vector<int>> adj;
   std::vector<std::vector<C>> cap;
   std::vector<std::vector<D>> costo;

   edmonds_karp_j(int n, int f, int s)
   : fuente(f), sumidero(s), adj(n), cap(n, std::vector<C>(n)), costo(n, std::vector<C>(n)) {
   }

   void agrega_arco(int i, int j, C c, D d) {   // no se admiten arcos paralelos ni costos negativos
      if (i != j && c != 0) {
         adj[i].push_back(j);
         adj[j].push_back(i);
         cap[i][j] = c;
         costo[i][j] = d;
         costo[j][i] = -d;
      }
   }

   C flujo_arco(int i, int j) {
      return cap[j][i];    // sí, así
   }

   std::pair<C, D> flujo_maximo( ) {
      C flujo_total = 0; D costo_total = 0;
      std::vector<D> potencial(adj.size( ), 0);
      for (;;) {
         auto [delta, camino] = aumenta(potencial);
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
   std::pair<C, std::vector<std::pair<int, int>>> aumenta(std::vector<int>& potencial) {
      std::vector<int> anterior(adj.size( ), -1);
      std::priority_queue<std::tuple<D, int, int>, std::vector<std::tuple<D, int, int>>, std::greater<>> cp;
      std::vector<D> min(adj.size( ), std::numeric_limits<D>::max( ));
      cp.emplace(0, fuente, fuente);
      do {
         auto [d, i, a] = cp.top( );
         cp.pop( );
         if (anterior[i] == -1) {
            anterior[i] = a, min[i] = d;
            for (int j : adj[i]) {
               if (cap[i][j] > 0) {
                  cp.emplace(d + costo[i][j] + potencial[i] - potencial[j], j, i);
               }
            }
         }
      } while (!cp.empty( ));
      if (anterior[sumidero] == -1) {
         return { 0, { } };
      }

      C cuello = std::numeric_limits<C>::max( );
      std::vector<std::pair<int, int>> camino;
      for (int i = sumidero; i != fuente; i = anterior[i]) {
         camino.emplace_back(anterior[i], i);
         cuello = std::min(cuello, cap[anterior[i]][i]);
      }
      for (int i = 0; i < adj.size( ); ++i) {
         min[i] += potencial[i] - potencial[fuente];
      }
      std::swap(potencial, min);
      return { cuello, camino };
   }
};
