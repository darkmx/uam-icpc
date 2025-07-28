/**
 * Nombre: Flujo máximo
 * Autor: rcc
 * Descripción: Algoritmo rápido de flujo máximo de una gráfica sin costos de $n$ vértices y $m$ aristas.
 * Complejidad: $O(n^2 \sqrt{m})$
 * Estado: probado en spoj.com/problems/FASTFLOW
 * Uso:
 *   push_relabel f(n, s, t);
 *   f.agrega_arco(i, j, c);
 *   int flujo = f.flujo_maximo( );
 *   if (f.cap[j][i] != 0) {
 *      // se enviaron f.cap[j][i] unidades de flujo de i a j
 *   }
 */
#include <algorithm>
#include <limits>
#include <vector>

template<typename T>
struct push_relabel {
   int fuente, sumidero;
   std::vector<std::vector<int>> adj;
   std::vector<std::vector<T>> cap;
   std::vector<T> exceso;
   std::vector<int> altura;

   push_relabel(int n, int f, int s)
   : fuente(f), sumidero(s), adj(n), cap(n, std::vector<T>(n, 0)),
     exceso(n, 0), altura(n, 0) {
      exceso[fuente] = std::numeric_limits<T>::max( );
      altura[fuente] = n;
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
      std::vector<int> por_altura[2 * adj.size( ) + 1];
      for (int j : adj[fuente]) {
         push(fuente, j, por_altura);
      }

      int max_altura = 0;
      while (busca_alto(por_altura, max_altura)) {
         int i = por_altura[max_altura].back( );
         por_altura[max_altura].pop_back( );
         for (int x = 0; x < adj[i].size( ) && exceso[i] != 0; ++x) {
            if (altura[i] - 1 == altura[adj[i][x]]) {
               push(i, adj[i][x], por_altura);
            }
         }
         if (exceso[i] != 0) {
            relabel(i, por_altura, max_altura);
         }
      }
      return exceso[sumidero];
   }

private:
   bool busca_alto(std::vector<int> por_altura[], int& max_altura) {
      while (max_altura >= 0 && por_altura[max_altura].empty( )) {
         max_altura -= 1;
      }
      return max_altura >= 0;
   }

   void push(int i, int j, std::vector<int> por_altura[]) {
      T flujo = std::min(exceso[i], cap[i][j]);
      if (flujo != 0) {
         if (exceso[j] == 0 && j != fuente && j != sumidero) {
            por_altura[altura[j]].push_back(j);
         }
         exceso[i] -= flujo;
         exceso[j] += flujo;
         cap[i][j] -= flujo;
         cap[j][i] += flujo;
      }
   }

   void relabel(int i, std::vector<int> por_altura[], int& max_altura) {
      int altura_min = 1e9;
      for (int j : adj[i]) {
         if (cap[i][j] != 0) {
            altura_min = std::min(altura_min, altura[j]);
         }
      }
      altura[i] = max_altura = altura_min + 1;
      por_altura[altura[i]].push_back(i);
   }
};
