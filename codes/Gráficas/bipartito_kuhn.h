/**
 * Nombre: Algoritmo de Kuhn
 * Autor: rcc
 * Descripción: Algoritmo simple de acoplamiento bipartito. Devuelve el tamaño del acoplamiento. \textit{match\_b[j]} será el vértice del lado izquierdo que quedó emparejado con el vértice \textit{j} del lado derecho, o \textit{-1} si no está emparejado.
 * Complejidad: $O(n m)$
 * Estado: probado en omegaup.com/arena/problem/Un-orden-para-todos
 * Uso:
 *   bipartito_kuhn bp(|A|, |B|);
 *   bp.agrega_arco(i, j); // por cada arista ($i \in A$, $j \in B$)
 *   int tam = bp.acoplamiento_maximo();
 *   if (int i = bp.match_b[j]; i != -1) {
 *      // i está emparejado con j
 *   }
 */
#include <algorithm>
#include <vector>

struct bipartito_kuhn {
   std::vector<std::vector<int>> adj;
   std::vector<int> match_b;

   bipartito_kuhn(int n, int m)
   : adj(n), match_b(m, -1) {
   }

   void agrega_arco(int i, int j) {
      adj[i].push_back(j);
   }

   int acoplamiento_maximo( ) {
      int res = 0;
      std::fill(match_b.begin( ), match_b.end( ), -1);
      for (int i = 0; i < adj.size( ); ++i) {
         bool visto_a[adj.size( )] = { };
         res += aumenta(i, visto_a);
      }
      return res;
   }

private:
   bool aumenta(int i, bool visto_a[]) {
      if (!visto_a[i]) {
         visto_a[i] = true;
         for (int j : adj[i]) {
            if (match_b[j] == -1 || aumenta(match_b[j], visto_a)) {
               match_b[j] = i;
               return true;
            }
         }
      }
      return false;
   }
};
