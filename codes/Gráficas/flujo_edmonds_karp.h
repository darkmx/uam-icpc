/**
 * Nombre: Algoritmo de Edmonds-Karp
 * Autor: rcc
 * Descripción: Algoritmo de flujo máximo de una gráfica sin costos de $n$ vértices y $m$ aristas.
 * Complejidad: $O(n m^2)$
 * Estado: probado en omegaup.com/arena/problem/Un-orden-para-todos
 * Uso:
 *   edmonds_karp f(n, s, t);
 *   f.agrega_arco(i, j, c);
 *   int flujo = f.flujo_maximo( );
 *   if (f.cap[j][i] != 0) {
 *      // se enviaron f.cap[j][i] unidades de flujo de i a j
 *   }
 */
#include <algorithm>
#include <deque>
#include <limits>
#include <utility>
#include <vector>

template<typename T>
struct edmonds_karp {
   int fuente, sumidero;
   std::vector<std::vector<int>> adj;
   std::vector<std::vector<T>> cap;

   edmonds_karp(int n, int f, int s)
   : fuente(f), sumidero(s), adj(n), cap(n, std::vector<T>(n)) {
   }

   void agrega_arco(int i, int j, T c) {
      if (i != j && c != 0) {
         if (cap[i][j] == 0 && cap[j][i] == 0) {
            adj[i].push_back(j);
            adj[j].push_back(i);
         }
         cap[i][j] += c;
      }
   }

   T flujo_maximo( ) {
      T res = 0;
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
   std::pair<T, std::vector<std::pair<int, int>>> aumenta( ) {
      std::vector<int> anterior(adj.size( ), -1);
      anterior[fuente] = fuente;
      for (std::deque<int> cola = { fuente }; !cola.empty( ); cola.pop_front( )) {
         int i = cola.front( );
         if (i == sumidero) {
            T cuello = std::numeric_limits<T>::max( );
            std::vector<std::pair<int, int>> camino;
            do {
               camino.emplace_back(anterior[i], i);
               cuello = std::min(cuello, cap[anterior[i]][i]);
               i = anterior[i];
            } while (i != fuente);
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
