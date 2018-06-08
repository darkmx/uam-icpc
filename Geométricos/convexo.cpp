#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template<typename T>
T producto_cruz(const std::pair<T, T>& a, const std::pair<T, T>& b, const std::pair<T, T>& c) {
   return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

template<typename RI1, typename RI2>
RI2 cerco_parcial(RI1 ai, RI1 af, RI2 bi) {
   auto bw = bi;
   for (; ai != af; *bw++ = *ai++) {
      while (bw - bi >= 2 && producto_cruz(*(bw - 2), *(bw - 1), *ai) <= 0) {
         --bw;
      }
   }

   return bw;
}

template<typename RI>
auto cerco_convexo(RI ai, RI af) {
   std::vector<typename std::iterator_traits<RI>::value_type> res(af - ai + 2);
   auto iter1 = cerco_parcial(ai, af, res.begin( )) - 1;
   auto iter2 = cerco_parcial(std::make_reverse_iterator(af), std::make_reverse_iterator(ai), iter1) - 1;
   res.resize(iter2 - res.begin( ));

   return res;
}

template<typename RI>
auto area_convexo(RI ai, RI af) {
   typename std::iterator_traits<RI>::value_type res(0);
   for (std::size_t i = 0; i < af - ai; ++i) {
      res += ai[i].first * ai[(i + 1) % (af - ai)].second - ai[i].second * ai[(i + 1) % (af - ai)].first;
   }
   return res / 2;
}

int main( ) {
   int n;
   std::cin >> n;

   std::vector<std::pair<double, double>> v(n);
   for (auto& p : v) {
      std::cin >> p.first >> p.second;
   }

   std::sort(v.begin( ), v.end( ));
   std::vector<std::pair<double, double>> cerco = cerco_convexo(v.begin( ), v.end( ));

   for (auto p : cerco) {
      std::cout << p.first << " " << p.second << "\n";
   }
}
