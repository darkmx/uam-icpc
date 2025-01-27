/**
 * Nombre: Salto exponencial
 * Autor: rcc
 * Descripción: Similar a la búsqueda binaria, pero ofrece un mejor rendimiento
 *              asintótico cuando el elemento buscado está cerca del inicio de la lista.
 * Complejidad: $O(\log(i))$, donde $i$ es la posición del elemento buscado o donde debería estar.
 */
#include <algorithm>
#include "busqueda_binaria.h"

template<typename T, typename F>
T salto_exponencial(T ini, T fin, F pred) {
   auto probar = ini;
   while (probar != fin && !pred(probar)) {
      probar += std::min(fin - probar, probar - ini + 1);
   }

   return (probar == fin ? fin : busqueda_binaria(probar - (probar - ini) / 2, probar, pred));
}
