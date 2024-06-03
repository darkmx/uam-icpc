#include <algorithm>
#include <vector>

// O(v^3)   Hopcroftn Karp es más rápido pero más largo
bool aumenta(int a, const std::vector<int> adyacencia_a[], std::vector<int>& arista_b, std::vector<bool>& visto_b) {
   for (int b : adyacencia_a[a]) {
      if (!visto_b[b]) {
         visto_b[b] = true;
         if (arista_b[b] == -1 || aumenta(arista_b[b], adyacencia_a, arista_b, visto_b)) {
            arista_b[b] = a;
            return true;
         }
      }
   }
   return false;
}

std::pair<std::vector<int>, int> acoplamiento(const std::vector<int> adyacencia_a[], int tam_a, int tam_b) {
   std::vector<int> arista_b(tam_b, -1);
   for (int a = 0; a < tam_a; ++a) {
      std::vector<bool> visto_b(tam_b, false);
      aumenta(a, adyacencia_a, arista_b, visto_b);
   }
   int cardinalidad = tam_b - std::count(arista_b.begin( ), arista_b.end( ), -1);
   return { std::move(arista_b), cardinalidad };
}

int main( ) {
   // acoplamiento bipartito: |A| = tam_a, |B| = tam_b
   // Los identificadores de vértices van de 0 -> tam_a - 1 en A y 0 -> tam_b - 1 en B.
   // La función regresa un arreglo de tam_b enteros que contienen los vértices de A con los que se conectan los vértices de B (-1 si un vértice de B no tiene pareja). También regresa la cardinalidad del emparejamiento
}
