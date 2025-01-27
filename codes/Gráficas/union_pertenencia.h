/**
 * Nombre: Unión-pertenencia
 * Autor: rcc
 * Descripción: Dado un grafo no dirigido, procesa la adición de aristas, verificar si dos vértices
 *              están en el mismo componente conexo y obtener el tamaño del componente de un elemento.
 * Complejidad: $O(\alpha(n))$ (amortizado).
 */
#include <vector>
#include <utility>

struct union_find {
   std::vector<int> data;

   union_find(int n)
   : data(n, -1) {
   }

   int leader(int i) {
      return (data[i] < 0 ? i : data[i] = leader(data[i]));
   }

   int size(int i) {
      return -data[leader(i)];
   }

   bool connected(int i, int j) {
      return leader(i) == leader(j);
   }

   void join(int i, int j) {
      int ri = leader(i), rj = leader(j);
      if (ri != rj) {
        if (-data[ri] < -data[rj]) {
          std::swap(ri, rj);
        }
        data[ri] += data[rj];
        data[rj] = ri;
      }
   }
};
