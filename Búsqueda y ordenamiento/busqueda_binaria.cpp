#include <algorithm>
#include <iostream>
#include <vector>

template<typename T, typename F>
T busqueda_binaria(T ini, T fin, F pred) {
   auto res = fin;
   while (ini != fin) {
      auto mitad = ini + (fin - ini) / 2;
      if (pred(mitad)) {
         res = mitad, fin = mitad;
      } else {
         ini = mitad + 1;
      }
   }
   return res;
}

template<typename T, typename F>
T salto_exponencial(T ini, T fin, F pred) {
   auto probar = ini;
   while (probar != fin && !pred(probar)) {
      probar += std::min(fin - probar, probar - ini + 1);
   }

   return (probar == fin ? fin : busqueda_binaria(probar - (probar - ini) / 2, probar, pred));
}

int main( ) {
   busqueda_binaria: {
      std::vector<int> v = { 0, 2, 4, 6, 8 };
      std::cout << *busqueda_binaria(v.begin( ), v.end( ), [](auto iter) {
         return *iter >= 3;
      }) << "\n";

      std::cout << busqueda_binaria(0, 1000, [](auto valor) {
         return valor / 500 != 0;
      }) << "\n";
   }

   salto_exponencial: {
      std::vector<int> v = { 0, 2, 4, 6, 8 };
      std::cout << *salto_exponencial(v.begin( ), v.end( ), [](auto iter) {
         return *iter >= 3;
      }) << "\n";

      std::cout << salto_exponencial(0, 1000, [](auto valor) {
         return valor / 500 != 0;
      }) << "\n";
   }
}
