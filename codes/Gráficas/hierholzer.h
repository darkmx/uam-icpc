/**
 * Nombre: Circuito euleriano
 * Autor: rcc
 * Descripción: Un circuito euleriano es un camino que recorre cada arista de un
 *              grafo exactamente una vez, y el camino termina en el vértice \textit{inicial}.
 * Complejidad: $O(n + m)$
 */
#include <algorithm>
#include <utility>
#include <set>
#include <vector>

std::vector<int> hierholzer(int inicial, std::vector<std::set<std::pair<int, int>>>& adyacencia) {
   std::vector<int> pila = { inicial }, res;
   do {
      int actual = pila.back( );
      if (!adyacencia[actual].empty( )) {
         auto [origen, destino] = *adyacencia[actual].begin( );
         adyacencia[actual].erase(adyacencia[actual].begin( ));
         adyacencia[destino].erase(std::pair(destino, actual));
         pila.push_back(destino);
      } else {
         res.push_back(actual);
         pila.pop_back( );
      }
   } while (!pila.empty( ));
   std::reverse(res.begin( ), res.end( ));
   return res;
}
