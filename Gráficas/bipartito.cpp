#include <algorithm>

template<typename V>
bool aumenta(const V& vecindad, int* regreso, int i, int m, bool* visto) {
   for (int j = 0; j < m; ++j) {
      if (vecindad(i, j) && !visto[j]) {
         visto[j] = true;
         if (regreso[j] == -1 || aumenta(vecindad, regreso, regreso[j], m, visto)) {
            regreso[j] = i;
            return true;
         }
      }
   }
   return false;
}

template<typename V>
int acoplamiento(const V& vecindad, int* regreso, int n, int m) {
   std::fill(regreso, regreso + m, -1);
   for (int i = 0; i < n; ++i) {
      bool visto[m] = { };
      aumenta(vecindad, regreso, i, m, visto);
   }
   return m - std::count(regreso, regreso + m, -1);
}

int main( ) {
   // acoplamiento bipartito: |A| = n, |B| = m
   // vecindad es una lambda, función u objeto función que toma dos identificadores de vértices (0 -> n-1 en A, 0 -> m-1 en B) y devuelve verdadero si existe una arista entre ellos
   // regreso debe tener tamaño m; regreso[j] es el identificador del vértice A con el que está conectado el j de B
}
