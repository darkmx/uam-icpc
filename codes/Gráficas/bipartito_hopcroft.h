/**
 * Nombre: Algoritmo de Hopcroft-Karp
 * Autor: rcc
 * Descripción: Algoritmo rápido de acoplamiento bipartito. Devuelve el tamaño del acoplamiento. \textit{match\_b[j]} será el vértice del lado izquierdo que quedó emparejado con el vértice \textit{j} del lado derecho, o \textit{-1} si no está emparejado.
 * Complejidad: $O(\sqrt{n} m)$
 * Estado: probado en spoj.com/problems/MATCHING
 * Uso:
 *   bipartito_hopcroft bp(|A|, |B|);
 *   bp.agrega_arco(i, j); // por cada arista ($i \in A$, $j \in B$)
 *   int tam = bp.acoplamiento_maximo();
 *   if (int i = bp.match_b[j]; i != -1) {
 *      // i está emparejado con j
 *   }
 */
#include <algorithm>
#include <deque>
#include <numeric>
#include <vector>

struct bipartito_hopcroft {
   std::vector<std::vector<int>> adj;
   std::vector<int> match_b;

   bipartito_hopcroft(int n, int m)
   : adj(n), match_b(m, -1) {
   }

   void agrega_arco(int i, int j) {
      adj[i].push_back(j);
   }

   int acoplamiento_maximo( ) {
      for (;;) {
         std::vector<int> capas = calcula_capas( );
         bool mejora = false, visto_a[adj.size( )] = { };
         for (int i = 0; i < adj.size( ); ++i) {
            mejora |= (capas[i] == 0 && aumenta(i, visto_a, capas));
         }
         if (!mejora) {
            return match_b.size( ) - std::count(match_b.begin( ), match_b.end( ), -1);
         }
      }
   }

private:
   std::vector<int> calcula_capas( ) {
      std::vector<int> capas(adj.size( ), 0);
      std::deque<int> cola(adj.size( ));
      std::iota(cola.begin( ), cola.end( ), 0);
      for (int j = 0; j < match_b.size( ); ++j) {
         int i = match_b[j];
         if (i != -1) {
            cola[i] = capas[i] = -1;
         }
      }

      cola.erase(std::remove(cola.begin( ), cola.end( ), -1), cola.end( ));
      for (; !cola.empty( ); cola.pop_front( )) {
         int i = cola.front( );
         for (int j : adj[i]) {
            if (match_b[j] != -1 && capas[match_b[j]] == -1) {
               capas[match_b[j]] = capas[i] + 1;
               cola.push_back(match_b[j]);
            }
         }
      }
      return capas;
   }

   bool aumenta(int i, bool visto_a[], const std::vector<int>& capas) {
      if (!visto_a[i]) {
         visto_a[i] = true;
         for (int j : adj[i]) {
            if (match_b[j] == -1 || capas[i] + 1 == capas[match_b[j]] && aumenta(match_b[j], visto_a, capas)) {
               match_b[j] = i;
               return true;
            }
         }
      }
      return false;
   }
};
