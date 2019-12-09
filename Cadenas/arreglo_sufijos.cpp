#include <algorithm>    // https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
#include <iostream>     // https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
#include <functional>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template<typename RI>
std::vector<int> suffix_ranking(RI si, RI sf) {
   std::vector<int> rank(si, sf), indices(sf - si);
   std::iota(indices.begin( ), indices.end( ), 0);
   for (int t = 1; t <= sf - si; t *= 2) {      // importante que se haga para sf - si == 1 pues se debe normalizar el rank inicial
      auto pred = [&, rank](int i1, int i2) {
         return std::make_pair(rank[i1], (i1 + t < sf - si ? rank[i1 + t] : -1)) < std::make_pair(rank[i2], (i2 + t < sf - si ? rank[i2 + t] : -1));
      };
      std::sort(indices.begin( ), indices.end( ), std::cref(pred));
      for (int i = 0, r = 0; i < indices.size( ); ++i) {
         rank[indices[i]] = r;
         r += (i + 1 != indices.size( ) && pred(indices[i], indices[i + 1]));
      }
   }
   return rank;
}

template<typename RI>
std::vector<RI> suffix_array(RI si, RI sf, const std::vector<int>& rank) {
   std::vector<RI> res(sf - si);
   for (int i = 0; i < rank.size( ); ++i) {
      res[rank[i]] = si + i;
   }
   return res;
}

template<typename RI>
std::vector<int> longest_prefix(RI si, RI sf, const std::vector<int>& rank, const std::vector<RI>& suffix) {
   std::vector<int> res(sf - si);
   for (int i = 0, t = 0; i < rank.size( ); ++i) {
      if (rank[i] + 1 != sf - si) {
         t += std::mismatch(si + i + t, sf, suffix[rank[i] + 1] + t/*, sf*/).first - (si + i + t);    // versión de 4 parámetros en C++14
         res[rank[i]] = t;                                                                            // la versión de 3 parámetros sólo es segura si la entrada no contiene nulos
         t -= (t > 0);                                                                                // y la cadena es nulo-terminada (std::string es nulo-terminada)
      } else {
         t = 0;
      }
   }
   return res;
}

template<typename RI1, typename RI2>
RI1 substring_search(RI1 si, RI1 sf, const std::vector<RI1>& rank, RI2 bi, RI2 bf) {
   struct comparador {
      const int pos;
      bool operator()(RI1 iter, char c) {
         return iter[pos] < c;
      }
      bool operator()(char c, RI1 iter) {
         return c < iter[pos];
      }
   };

   auto ri = rank.begin( ), rf = rank.end( );
   for (int i = 0; i < bf - bi; ++i) {
      auto temp = std::equal_range(ri, rf, bi[i], comparador{i});
      ri = temp.first, rf = temp.second;
   }
   return (ri == rf ? sf : *ri);
}

int main( ) {
   std::string s;
   std::cin >> s;

   auto rank = suffix_ranking(s.begin( ), s.end( ));
   auto suffix = suffix_array(s.begin( ), s.end( ), rank);
   auto lcp = longest_prefix(s.begin( ), s.end( ), rank, suffix);

   for (int i = 0; i < s.size( ); ++i) {
      std::cout << std::string(suffix[i], s.end( )) << ": " << lcp[i] << "\n";
   }

   std::string b;
   std::cin >> b;

   std::cout << (substring_search(s.begin( ), s.end( ), suffix, b.begin( ), b.end( )) != s.end( ) ? 'y' : 'n') << "\n";
}
