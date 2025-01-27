/**
 * Nombre: Aritmética modular
 * Autor: rcc
 * Descripción: Operadores para aritmética modular. Supone que \textit{MOD} es primo.
 */
#include <stdint.h>
#include "inverso_modular.h"

template<int MOD>
struct modular_int {
   int v;

   modular_int(int64_t u = 0)
   : v(u % MOD) {
      v += (v < 0) * MOD;
   }
   modular_int& operator+=(modular_int o) {
      if ((v += o.v) >= MOD) v -= MOD; 
      return *this;
   }
   modular_int& operator-=(modular_int o) { 
      if ((v -= o.v) < 0) v += MOD; 
      return *this;
   }
   modular_int& operator*=(modular_int o) { 
      v = (int64_t)v * o.v % MOD;
      return *this;
   }
   modular_int& operator/=(modular_int o) {
      return (*this) *= modular_int(inverso(o.v, MOD));
   }
   auto operator<=>(const modular_int& o) const = default;
   explicit operator int( ) const { return v; }
   friend modular_int operator+(modular_int a, modular_int b) { return a += b; }
   friend modular_int operator-(modular_int a, modular_int b) { return a -= b; }
   friend modular_int operator*(modular_int a, modular_int b) { return a *= b; }
   friend modular_int operator/(modular_int a, modular_int b) { return a /= b; }
};
//using gf = modular_int<1e9+7>;
