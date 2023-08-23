#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

auto producto_cruz(const auto& a, const auto& b, const auto& c) {
   return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

template<typename RI1, typename RI2>
auto cerco_parcial(RI1 ai, RI1 af, RI2 bi) {
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
   if (af - ai <= 2) {
      return std::vector<typename std::iterator_traits<RI>::value_type>(ai, af);
   }
   std::vector<typename std::iterator_traits<RI>::value_type> res(af - ai + 2);
   auto iter1 = cerco_parcial(ai, af, res.begin( )) - 1;
   auto iter2 = cerco_parcial(std::make_reverse_iterator(af), std::make_reverse_iterator(ai), iter1) - 1;
   res.resize(iter2 - res.begin( ));
   return res;
}

auto distancia(const auto& a, const auto& b) {
   return std::hypot(a.x - b.x, a.y - b.y);  // std::hypot puede ser más lento que hacerlo manualmente con std::sqrt
}

template<typename T>
auto perimetro(const std::vector<T>& puntos) {
   double res = 0;
   for (int i = 0; i < puntos.size( ); ++i) {
      res += distancia(puntos[i], puntos[(i + 1) % puntos.size( )]);
   }
   return res;
}

struct punto {
   double x, y;
   bool operator<(const punto& p) const {
      return std::pair(x, y) < std::pair(p.x, p.y);
   }
};

int main( ) {
   int n;
   std::cin >> n;

   std::vector<punto> v(n);
   for (auto& p : v) {
      std::cin >> p.x >> p.y;
   }

   std::sort(v.begin( ), v.end( ));   // importante
   std::vector<punto> cerco = cerco_convexo(v.begin( ), v.end( ));

   for (auto p : cerco) {
      std::cout << p.x << " " << p.y << "\n";
   }
}
