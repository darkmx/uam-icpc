/**
 * Nombre: Arreglo de sufijos
 * Autor: rcc
 * Descripción: Construye el arreglo de sufijos para una cadena. \textit{suffix[i]} es el iterador del inicio del sufijo que ocupa la
 *              posición $i$ en el arreglo de sufijos ordenado. La función \textit{longest\_prefix} calcula los prefijos comunes más
 *              largos para las cadenas vecinas en el arreglo de sufijos: \textit{lcp[i] = lcp(suffix[i], suffix[i+1])}, y \textit{lcp[n-1] = 0}.
 *              La función \textit{substring\_search} devuelve una pareja de iteradores sobre \textit{suffix} que denotan el inicio y el fin de
 *              todos los sufijos donde la subcadena es prefijo.
 * Complejidad: $O(n\log^2(n))$ donde $n$ es la longitud de la cadena, y $O(k\log(n))$ para \textit{substring\_search} donde $k$ es la longitud
 *              del patrón.
 * Uso:
 *  suffix_array sa(s.begin( ), s.end( ));
 *  auto [ini, fin] = sa.substring_search(b.begin( ), b.end( ));
 */
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

template<typename RI>
struct suffix_array {
   RI si, sf;
   std::vector<int> rank;
   std::vector<RI> suffix;

   suffix_array(RI ri, RI rf)
   : si(ri), sf(rf), rank(si, sf), suffix(sf - si) {
      std::vector<int> indices(sf - si);
      std::iota(indices.begin( ), indices.end( ), 0);
      for (int t = 1; t <= sf - si; t *= 2) {      // importante que se haga para sf - si == 1 pues se debe normalizar el rank inicial
         auto pred = [&, rank = this->rank](int i1, int i2) {
            return std::make_pair(rank[i1], (i1 + t < sf - si ? rank[i1 + t] : -1)) < std::make_pair(rank[i2], (i2 + t < sf - si ? rank[i2 + t] : -1));
         };
         std::sort(indices.begin( ), indices.end( ), std::cref(pred));
         for (int i = 0, r = 0; i < indices.size( ); ++i) {
            rank[indices[i]] = r;
            r += (i + 1 != indices.size( ) && pred(indices[i], indices[i + 1]));
         }
      }

      for (int i = 0; i < suffix.size( ); ++i) {
         suffix[rank[i]] = si + i;
      }
   }

   std::vector<int> longest_prefix() {
      std::vector<int> res(sf - si);
      for (int i = 0, t = 0; i < rank.size( ); ++i) {
         if (rank[i] + 1 != sf - si) {
            t += std::mismatch(si + i + t, sf, suffix[rank[i] + 1] + t, sf).first - (si + i + t);
            res[rank[i]] = t;
            t -= (t > 0);
         } else {
            t = 0;
         }
      }
      return res;
   }

   auto substring_search(auto bi, auto bf) {
      struct comparador {
         const int pos;
         bool operator()(RI iter, char c) {
            return iter[pos] < c;
         }
         bool operator()(char c, RI iter) {
            return c < iter[pos];
         }
      };

      auto xi = suffix.begin( ), xf = suffix.end( );
      for (int i = 0; i < bf - bi; ++i) {
         auto temp = std::equal_range(xi, xf, bi[i], comparador{i});
         xi = temp.first, xf = temp.second;
      }
      return std::pair(xi, xf);
   }
};
