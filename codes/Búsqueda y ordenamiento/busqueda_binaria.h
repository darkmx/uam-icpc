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

template<typename T, typename F>
T busqueda_binaria(T ini, T fin, F pred) {
   auto res = fin;
   while (ini != fin) {
      auto mitad = ini + (fin - ini) / 2;
      if (pred(mitad)) {
         res = mitad, fin = mitad;
      } else {
         ini = mitad + 1;
      }
   }
   return res;
}
