#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template<typename FI>
std::size_t longest_increasing_subsequence_size(FI ini, FI fin) {
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
std::vector<BI> longest_increasing_subsequence(BI ini, BI fin) {
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

int main( ) {
   std::string s;
   std::cin >> s;

   auto tam = longest_increasing_subsequence_size(s.begin( ), s.end( ));
   auto res = longest_increasing_subsequence(s.begin( ), s.end( ));

   std::cout << tam << " " << res.size( ) << "\n";
   std::cout << (tam == res.size( )) << " " << std::is_sorted(res.begin( ), res.end( )) << " " << std::is_sorted(res.begin( ), res.end( ), [](auto i1, auto i2) {
      return *i1 < *i2;
   }) << "\n";
   for (auto i : res) {
      std::cout << i - s.begin( ) << ": " << *i << "\n";
   }
}
