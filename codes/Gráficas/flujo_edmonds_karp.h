/**
 * Nombre: Algoritmo de Edmonds-Karp
 * Autor: rcc
 * Descripción: Algoritmo de flujo máximo de una gráfica sin costos de $n$ vértices y $m$ aristas.
 * Complejidad: $O(n m^2)$
 * Estado: probado en omegaup.com/arena/problem/Un-orden-para-todos
 * Uso:
 *   edmonds_karp<int> f(n, s, t);
 *   f.agrega_arco(i, j, c);
 *   int flujo = f.flujo_maximo( );
 *   int t = f.flujo_arco(i, j);
 */
#include <algorithm>
#include <deque>
#include <limits>
#include <utility>
#include <vector>

template<typename C>
struct edmonds_karp {
   int fuente, sumidero;
   std::vector<std::vector<int>> adj;
   std::vector<std::vector<C>> cap;

   edmonds_karp(int n, int f, int s)
   : fuente(f), sumidero(s), adj(n), cap(n, std::vector<C>(n)) {
   }

   void agrega_arco(int i, int j, C c) {
      if (i != j && c != 0) {
         if (cap[i][j] == 0 && cap[j][i] == 0) {
            adj[i].push_back(j);
            adj[j].push_back(i);
         }
         cap[i][j] += c;
      }
   }

   C flujo_arco(int i, int j) {
      return cap[j][i];    // sí, así
   }

   C flujo_maximo( ) {
      C res = 0;
      for (;;) {
         auto [delta, camino] = aumenta( );
         if (delta == 0) {
            return res;
         }
         res += delta;
         for (auto [i, j] : camino) {
            cap[i][j] -= delta;
            cap[j][i] += delta;
         }
      }
   }

private:
   std::pair<C, std::vector<std::pair<int, int>>> aumenta( ) {
      std::vector<int> anterior(adj.size( ), -1);
      anterior[fuente] = fuente;
      for (std::deque<int> cola = { fuente }; !cola.empty( ); cola.pop_front( )) {
         int i = cola.front( );
         if (i == sumidero) {
            C cuello = std::numeric_limits<C>::max( );
            std::vector<std::pair<int, int>> camino;
            for (int i = sumidero; i != fuente; i = anterior[i]) {
               camino.emplace_back(anterior[i], i);
               cuello = std::min(cuello, cap[anterior[i]][i]);
            }
            return { cuello, camino };
         }
         for (int j : adj[i]) {
            if (anterior[j] == -1 && cap[i][j] > 0) {
               cola.push_back(j);
               anterior[j] = i;
            }
         }
      }

      return { 0, { } };
   }
};
