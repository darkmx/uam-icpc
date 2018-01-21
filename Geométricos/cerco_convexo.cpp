#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template<typename T>
inline T producto_cruz(const std::pair<T, T>& a, const std::pair<T, T>& b, const std::pair<T, T>& c)
{
   return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

template<typename RI1, typename RI2>
inline RI2 cerco_parcial(RI1 ai, RI1 af, RI2 bi)
{
   auto bw = bi;
   for (; ai != af; *bw++ = *ai++) {
      while (bw - bi >= 2 && producto_cruz(*(bw - 2), *(bw - 1), *ai) <= 0) {
         --bw;
      }
   }

   return bw;
}

template<typename RI, typename OI>
inline OI cerco_convexo(RI ai, RI af, OI wi)
{
   std::vector<typename std::iterator_traits<RI>::value_type> temp(af - ai);
   wi = std::copy(temp.begin( ), cerco_parcial(ai, af, temp.begin( )) - 1, wi);
   wi = std::copy(temp.begin( ), cerco_parcial(std::make_reverse_iterator(af), std::make_reverse_iterator(ai), temp.begin( )) - 1, wi);

   return wi;
}

int main( )
{
   int n;
   std::cin >> n;

   std::vector<std::pair<double, double>> v(n);
   for (auto& p : v) {
      std::cin >> p.first >> p.second;
   }

   std::sort(v.begin( ), v.end( ));
   std::vector<std::pair<double, double>> cerco;
   cerco_convexo(v.begin( ), v.end( ), std::back_inserter(cerco));

   for (auto p : cerco) {
      std::cout << p.first << " " << p.second << "\n";
   }
}
