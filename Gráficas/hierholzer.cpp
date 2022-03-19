#include <algorithm>
#include <iomanip>
#include <iostream>
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

int main(int argc, const char* argv[]) {
   // lectura de la entrada

   int n;
   std::cin >> n;

   punto arr[n + 1];
   for (int i = 0; i < n + 1; ++i) {
      std::cin >> arr[i].x >> arr[i].y;
   }

   std::vector<std::pair<int, int>> requeridas(n - 1);
   for (int i = 0; i < n - 1; ++i) {
      std::cin >> requeridas[i].first >> requeridas[i].second;
   }

   int grado[n + 1] = { };
   for (auto [x, y] : requeridas) {
      ++grado[x], ++grado[y];
   }

   // modificación de la gráfica

   for (int i = 1; i < n + 1; ++i) {
      if (grado[i] % 2 == 1) {
         requeridas.emplace_back(0, i);
      }
   }
   n += 1;

   // hierholzer

   std::vector<std::set<arco, por_costo>> adyacencia(n, std::set<arco, por_costo>(por_costo(arr)));
   for (auto [x, y] : requeridas) {
      adyacencia[x].insert(arco(x, y));
      adyacencia[y].insert(arco(y, x));
   }
   std::vector<int> recorrido = hierholzer(0, adyacencia);

   double costo = 0;
   for (int i = 1; i < recorrido.size( ); ++i) {
      costo += distancia_windy(arr[recorrido[i - 1]], arr[recorrido[i]]);
   }
   std::cout << std::setprecision(9) << std::fixed << costo << "\n";
   for (int actual : recorrido) {
      std::cout << actual << " ";
   }
   std::cout << "\n";
}
