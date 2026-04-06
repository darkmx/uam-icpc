/**
 * Nombre: Búsqueda ternaria generalizada
 * Autor: rcc
 * Descripción: Devuelve el primer $x$ tal que $f(x)$ es el máximo de f,
 *              sobre una función f unimodal.
 * Complejidad: $O(\log(n))$
 * Uso:
 *  auto f = [](double x) { return -std::pow((x - 3), 2) + 9; };
 *  double i = busqueda_ternaria(-100.0, +100.0, f, 1e-6);
 *  // se puede usar un rango entero y omitir la tolerancia
 */
#include <numeric>

template<typename T, typename F>
T busqueda_ternaria(T ini, T fin, F funcion, T tol = 1) {      // busca el máximo de la función
   while (fin - ini >= 3 * tol) {
      T mitad1 = ini + 1 * (fin - ini) / 3;
      T mitad2 = ini + 2 * (fin - ini) / 3;
      auto v1 = funcion(mitad1), v2 = funcion(mitad2);
      if (v1 <= v2) {
         ini = mitad1 + tol;
      }
      if (v1 >= v2) {
         fin = mitad2;
      }
   }
   std::pair mejor = { ini, funcion(ini) };
   for (T i = ini + tol; i < fin; i += tol) {
      mejor = std::max(mejor, { i, funcion(i) });
   }
   return mejor.first;
}
