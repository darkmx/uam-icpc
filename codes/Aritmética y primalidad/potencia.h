/**
 * Nombre: Potencia rápida generalizada
 * Autor: rcc
 * Descripción: Calcula $a^b$ para cualquier $a$ que pertenezca a un monoide.
 * Complejidad: $O(\log b)$.
 */

template<typename T>
T potencia(T a, int b) {
   T res(1);
   for (; b != 0; b /= 2, a *= a) {
      if (b % 2 == 1) {
         res *= a;
      }
   }
   return res;
}
