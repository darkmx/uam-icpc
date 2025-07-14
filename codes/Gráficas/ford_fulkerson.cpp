/**
 * Nombre: Flujo máximo con costo mínimo
 * Autor: rcc
 * Descripción: .
 * Complejidad: $O()$
 * Uso:
 *   ford_fulkerson f(n, s, t);
 *   f.agrega_arco(u, v, c, d);
 *   auto [flujo, costo] = f.flujo_maximo( );
 */
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

struct ford_fulkerson {    /// (versión con costos)
   int vertices, fuente, sumidero;
   std::vector<std::vector<int>> capacidad;
   std::vector<std::vector<int>> costo;
   std::vector<std::vector<int>> vecinos;

   ford_fulkerson(int v, int s, int t)
   : vertices(v), fuente(s), sumidero(t), capacidad(v, std::vector<int>(v)), costo(v, std::vector<int>(v)), vecinos(v) {
   }

   void agrega_arco(int i, int j, int c, int d) {
      capacidad[i][j] = c;
      costo[i][j] = d;
      costo[j][i] = -d;
      vecinos[i].push_back(j);
      vecinos[j].push_back(i);
   }

   std::pair<int, std::vector<std::pair<int, int>>> camino_aumentante( ) {
      std::vector<int> anterior(vertices, -1);
      std::vector<int> costo_minimo(vertices, 1e9);
      costo_minimo[fuente] = 0;

      for (int k = 0; k < vertices - 1; ++k) {
         for (int i = 0; i < vertices; ++i) {
            for (int j : vecinos[i]) {
               if (capacidad[i][j] > 0 && costo_minimo[j] > costo_minimo[i] + costo[i][j]) {
                  costo_minimo[j] = costo_minimo[i] + costo[i][j];
                  anterior[j] = i;
               }
            }
         }
      }

      if (costo_minimo[sumidero] == 1e9) {
         return { 0, { } };
      }

      std::vector<std::pair<int, int>> camino;
      int cuello = 1e9, actual = sumidero;
      do {
         cuello = std::min(cuello, capacidad[anterior[actual]][actual]);
         camino.emplace_back(anterior[actual], actual);
         actual = anterior[actual];
      } while (actual != fuente);

      return { cuello, camino };
   }

   std::pair<int, int> flujo_maximo( ) {
      int flujo_total = 0, costo_total = 0;
      for (;;) {
         auto [aumento_flujo, camino] = camino_aumentante( );
         if (aumento_flujo == 0) {
            return { flujo_total, costo_total };
         }
         flujo_total += aumento_flujo;
         for (auto [i, j] : camino) {
            costo_total += aumento_flujo * costo[i][j];
            capacidad[i][j] -= aumento_flujo;
            capacidad[j][i] += aumento_flujo;
         }
      }
   }
};

int main( ) {
   int n, m;
   std::cin >> n >> m;

   int v = 2 * n + 2;
   int s = v - 2;
   int t = v - 1;
   ford_fulkerson f(v, s, t);
   for (int i = 0; i < n; ++i) {
      f.agrega_arco(s, i, 1, 0);
      f.agrega_arco(i + n, t, 1, 0);
   }

   for (int i = 0; i < m; ++i) {
      int x, y, d;
      std::cin >> x >> y >> d;
      f.agrega_arco(x, y + n, 1, d);
   }

   auto [flujo, costo] = f.flujo_maximo( );
   std::cout << flujo << " " << costo;
}
