#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template<typename FI, typename RI, typename P>
void rankea(FI ai, FI af, RI wi, const P& p)
{
   for (std::size_t r = 0; ai != af; ++ai) {
      wi[*ai] = r;
      r += (std::next(ai) != af && p(*ai, *std::next(ai)));
   }
}

template<typename RI>
std::vector<RI> sufijos(RI ai, RI af)
{
   std::vector<std::size_t> trabajo(af - ai), rank(ai, af);
   std::iota(trabajo.begin( ), trabajo.end( ), std::size_t(0));
   for (std::size_t t = 1; t <= af - ai; t *= 2) {
      auto p = [&, rank](std::size_t i1, std::size_t i2) {
         return std::make_pair(rank[i1], (i1 + t - 1 < af - ai ? rank[i1 + t - 1] + 1 : 0)) < std::make_pair(rank[i2], (i2 + t - 1 < af - ai ? rank[i2 + t - 1] + 1 : 0));
      };
      std::sort(trabajo.begin( ), trabajo.end( ), p);
      rankea(trabajo.begin( ), trabajo.end( ), rank.begin( ), p);
   }

   std::vector<RI> res(af - ai);
   for (std::size_t i = 0; i < af - ai; ++i) {
      res[rank[i]] = ai + i;
   }

   return res;
}

int main( )
{
   std::string s;
   std::cin >> s;

   auto res = sufijos(s.begin( ), s.end( ));
   for (std::size_t i = 0; i < s.size( ); ++i) {
      std::cout << std::string(res[i], s.end( )) << '\n';
   }
}
