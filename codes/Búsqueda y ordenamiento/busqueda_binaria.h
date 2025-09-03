/**
 * Nombre: Búsqueda binaria generalizada
 * Autor: rcc
 * Descripción: Devuelve el primer $x$ tal que $pred(x)$ es verdadero,
 *              y para todo $x$, $pred(x)$ debe ser una función monótona.
 * Complejidad: $O(\log(n))$
 * Uso:
 *  auto elemento = busqueda_binaria(0, 1000, [](auto valor) {
 *  \t return valor / 500 != 0;
 *  };
 */
#include <numeric>

template<typename T, typename F>
T busqueda_binaria(T ini, T fin, F pred) {
   while (ini != fin) {
      auto mitad = std::midpoint(ini, fin);
      if (pred(mitad)) {
         fin = mitad;
      } else {
         ini = mitad + 1;
      }
   }
   return fin;
}
