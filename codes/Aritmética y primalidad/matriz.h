/**
 * Nombre: Matriz como clase
 * Autor: rcc
 * Descripción: Operaciones básicas con matrices.
 * Complejidad: $O(n^3)$
 * Uso:
 *  matriz<2, 2>({{ { 0, 1 }, { 1, 1 } }})
 */
#include <array>

template<class T, int F, int C>
struct matriz : std::array<std::array<T, C>, F> {
   explicit matriz(bool identidad = false) {
      for (int i = 0; i < F; ++i) {
         for (int j = 0; j < C; ++j) {
            (*this)[i][j] = (i == j && identidad);
         }
      }
   }
   explicit matriz(const std::array<std::array<T, C>, F>& m)
   : std::array<std::array<T, C>, F>(m) {
   }

   template<int D>
   matriz<T, F, D> operator*(const matriz<T, C, D>& m) {
      matriz<T, F, D> res;
      for (int i = 0; i < F; ++i) {
         for (int j = 0; j < D; ++j) {
            for (int k = 0; k < C; ++k) {
               res[i][j] += (*this)[i][k] * m[k][j];
            }
         }
      }
      return res;
   }
   void operator*=(const matriz<T, F, C>& m) {
      *this = *this * m;
   }
};
