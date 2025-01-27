/**
 * Nombre: Distancia entre dos puntos
 * Autor: rcc
 * Descripción: Calcula la distancia euclidiana entre dos puntos en un plano.
 * Uso:
 *  double dis = distancia<int>({ 0, 0 }, { 1, 1 });
 */
#include <cmath>
#include <utility>

template<typename T>
double distancia(const std::pair<T, T>& a, const std::pair<T, T>& b) {
   auto dx = a.first - b.first;
   auto dy = a.second - b.second;
   return std::sqrt(dx * dx + dy * dy);
}
