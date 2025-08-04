/**
 * Nombre: Cerco convexo
 * Autor: rcc
 * Descripción:
\\\begin{minipage}{85mm}
Devuelve un vector de los puntos del cerco convexo en sentido antihorario.
Los puntos en el borde del cerco entre dos puntos no se consideran parte del cerco.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Complejidad: $O(n\log n)$
 * Uso:
 *  std::sort(puntos.begin( ), puntos.end( ));
 *  auto cerco = cerco_convexo(puntos.begin( ), puntos.end( ));
 */
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

struct punto {
   double x, y;      // si no necesitan doubles, pasarlos a int porque es más rápido
   bool operator<(const punto& p) const {
      return std::pair(x, y) < std::pair(p.x, p.y);
   }
};

auto producto_cruz(const auto& a, const auto& b, const auto& c) {
   return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

template<typename RI1, typename RI2>
auto cerco_parcial(RI1 ai, RI1 af, RI2 bi) {
   auto bw = bi;
   for (; ai != af; *bw++ = *ai++) {
      while (bw - bi >= 2 && producto_cruz(*(bw - 2), *(bw - 1), *ai) <= 0) {       // < 0 para permitir empates en línea recta
         --bw;
      }
   }
   return bw;
}

template<typename RI>
auto cerco_convexo(RI ai, RI af) {
   if (af - ai <= 2) {
      return std::vector<std::iter_value_t<RI>>(ai, af);
   } else {
      std::vector<std::iter_value_t<RI>> res(2 * (af - ai));
      auto it1 = cerco_parcial(ai, af, res.begin( )) - 1;
      auto it2 = cerco_parcial(std::reverse_iterator(af), std::reverse_iterator(ai), it1) - 1;
      res.resize(it2 - res.begin( ));
      return res;
   }
}
