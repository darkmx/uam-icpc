/**
 * Nombre: Circuito euleriano
 * Autor: rcc
 * Descripción: .
 * Complejidad: .
 * Uso:
 *  int res = exampleFunction1(mice, cats, catsCount);
 *  int random = exampleFunction2();
 */
#include <algorithm>
#include <iomanip>
#include <list>
#include <queue>
#include <set>
#include <vector>
#include <math.h>

struct punto {
   double x, y;
};

struct arco {
   int x, y;
};

double factor_windy(punto p1, punto p2) {
   return (p1.x <= p2.x ? 1 / 1.5 : 2);
}

double distancia_windy(punto p1, punto p2) {
   return hypot(factor_windy(p1, p2) * (p1.x - p2.x), p1.y - p2.y);
}

struct por_costo {
   const punto* arr;
   bool operator()(const arco& a, const arco& b) const {
      return std::tuple(distancia_windy(arr[a.x], arr[a.y]), a.x, a.y) < std::tuple(distancia_windy(arr[b.x], arr[b.y]), b.x, b.y);
   }
};

std::vector<int> hierholzer(int inicial, std::vector<std::set<arco, por_costo>>& adyacencia) {
   std::vector<int> pila = { inicial }, res;
   do {
      int actual = pila.back( );
      if (!adyacencia[actual].empty( )) {
         auto [origen, destino] = *adyacencia[actual].begin( );
         adyacencia[actual].erase(adyacencia[actual].begin( ));
         adyacencia[destino].erase(arco(destino, actual));
         pila.push_back(destino);
      } else {
         res.push_back(actual);
         pila.pop_back( );
      }
   } while (!pila.empty( ));
   std::reverse(res.begin( ), res.end( ));
   return res;
}
