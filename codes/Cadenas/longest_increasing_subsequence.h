/**
 * Nombre: Subsecuencia creciente más larga
 * Autor: rcc
 * Descripción: La función \textit{lis\_size} devuelve el tamaño de la subsecuencia creciente más larga,
 *              mientras que la función \textit{lis} devuelve un vector de iteradores que componen dicha subsecuencia.
 * Complejidad: $O(n\log n)$
 * Uso:
 *  std::vector<int> arr = { 10, 22, 9, 33, 21, 50, 41, 60 }; 
 *  auto tam = lis_size(arr.begin( ), arr.end( ));
 */
#include <algorithm>
#include <iterator>
#include <vector>

template<typename FI>
std::size_t lis_size(FI ini, FI fin) {
   std::vector<typename std::iterator_traits<FI>::value_type> valores;
   for (auto i = ini; i != fin; ++i) {
      auto cambiar = std::upper_bound(valores.begin( ), valores.end( ), *i);     // upper_bound para creciente no estricta, lower_bound para creciente estricta
      if (cambiar == valores.end( )) {
         valores.push_back(*i);
      } else {
         *cambiar = *i;
      }
   }

   return valores.size( );
}

template<typename BI>
std::vector<BI> lis(BI ini, BI fin) {
   std::vector<BI> posiciones(1), atras;
   auto pred = [&](BI i, BI j) {
      return *i < *j;
   };

   for (auto i = ini; i != fin; ++i) {
      auto cambiar = std::upper_bound(posiciones.begin( ) + 1, posiciones.end( ), i, pred);  // lower_bound para creciente estricta
      if (cambiar == posiciones.end( )) {
         atras.push_back(posiciones.back( ));
         posiciones.push_back(i);
      } else if (pred(i, *cambiar)) {                                                        // tautología con upper_bound (creciente no estricta) pero no con lower_bound (creciente estricta)
         atras.push_back(*(cambiar - 1));
         *cambiar = i;
      } else {
         atras.emplace_back( );
      }
   }

   for (auto i = posiciones.end( ); i != posiciones.begin( ) + 1; --i) {
      *(i - 2) = atras[*(i - 1) - ini];
   }

   return std::vector<BI>(posiciones.begin( ) + 1, posiciones.end( ));
}
