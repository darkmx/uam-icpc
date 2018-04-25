#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template<typename FI>
std::vector<FI> longest_increasing_subsequence(FI ini, FI fin) {
   std::vector<FI> posiciones;
   auto pred = [&](FI i, FI j) {
      return *i < *j;
   };

   for (auto i = ini; i != fin; ++i) {
      auto cambiar = std::lower_bound(posiciones.begin( ), posiciones.end( ), i, pred);
      if (cambiar == posiciones.end( )) {
         posiciones.push_back(i);
      } else {
         *cambiar = std::min(*cambiar, i, pred);
      }
   }

   return posiciones;
}

int main( ) {
   std::string s;
   std::cin >> s;

   auto res = longest_increasing_subsequence(s.begin( ), s.end( ));
   for (auto i : res) {
      std::cout << i - s.begin( ) << ": " << *i << "\n";
   }
}
