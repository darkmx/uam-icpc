#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

// O(v^2.5)
namespace bipartito {      // https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
   bool aumenta(int a, std::vector<int> adyacencia_a[], std::vector<int>& nivel_a, std::vector<int>& pareja_a, std::vector<int>& pareja_b, bool visto_a[]) {
      visto_a[a] = true;
      for (int b : adyacencia_a[a]) {
         if (pareja_b[b] == -1 || !visto_a[pareja_b[b]] && nivel_a[a] < nivel_a[pareja_b[b]] && aumenta(pareja_b[b], adyacencia_a, nivel_a, pareja_a, pareja_b, visto_a)) {
            pareja_a[a] = b;
            pareja_b[b] = a;
            return true;
         }
      }
      return false;
   }

   auto calcula(std::vector<int> adyacencia_a[], int n, int m) {
      std::vector<int> nivel_a(n), pareja_a(n, -1), pareja_b(m, -1);
      for (;;) {
         std::queue<int> cola;
         for (int a = 0; a < n; ++a) {
            if (pareja_a[a] == -1) {
               nivel_a[a] = 0, cola.push(a);
            } else {
               nivel_a[a] = -1;
            }
         }

         for (; !cola.empty( ); cola.pop( )) {
            int a = cola.front( );
            for (int b : adyacencia_a[a]) {
               if (pareja_b[b] != -1 && nivel_a[pareja_b[b]] < 0) {
                  nivel_a[pareja_b[b]] = nivel_a[a] + 1;
                  cola.push(pareja_b[b]);
               }
            }
         }

         bool mejora = false, visto_a[n] = { };
         for (int a = 0; a < n; ++a) {
            mejora |= (pareja_a[a] == -1 && aumenta(a, adyacencia_a, nivel_a, pareja_a, pareja_b, visto_a));
         }
         if (!mejora) {
            int cardinalidad = n - std::count(pareja_a.begin( ), pareja_a.end( ), -1);
            return std::tuple(std::move(pareja_a), std::move(pareja_b), cardinalidad);
         }
      }
   }
};

int main( ) {
   // acoplamiento bipartito: |A| = tam_a, |B| = tam_b
   // Los identificadores de vértices van de 0 -> tam_a - 1 en A y 0 -> tam_b - 1 en B.
   // auto [pa, pb, tam] = bipartito(lista_adyacencia_a, tam_a, tam_b);
   // pa es un arreglo de enteros que indica quién es la pareja de cada vértice de a
   // pb es un arreglo de enteros que indica quién es la pareja de cada vértice de b
}
