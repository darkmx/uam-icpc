/**
 * Nombre: Árbol de Fenwick multidimensional
 * Autor: rcc
 * Descripción: Realiza actualizaciones y consultas de rango en múltiples dimensiones.
 * Complejidad: $O(4^d\log n_1\cdot \log n_2\cdots \log n_d)$. Es eficiente para dimensiones bajas (hasta 4 o 5).
 * Uso:
 *  fenwick_tree<int, 2> arbol_2d(3, 3);
 *  int suma = arbol_2d.query(1, 1, 3, 3); // $\sum_{i=1}^2\sum_{j=1}^2 a[i][j]$
 */
#include <array>
#include <bit>
#include <tuple>
#include <vector>

template<typename T, int D>
class fenwick_tree {
public:
   template<typename... P>
   fenwick_tree(int n, const P&... s)
   : mem_(n + 1, fenwick_tree<T, D - 1>(s...)) {
   }

   template<typename... P>
   void modify_add(int i, const P&... s) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i].modify_add(s...);
      }
   }

   /*template<typename... P>
   T operator[](const P&... x) {             // C++23
      return query(x..., (x + 1)...);
   }*/

   template<typename... P>
   T operator()(const P&... x) {             // C++20 o menor
      return query(x..., (x + 1)...);
   }

   template<typename... P>
   T query(const P&... x) {
      static_assert(sizeof...(P) == 2 * D);
      return query(std::make_index_sequence<D>( ), std::array<int, 2 * D>{ x... });
   }

   template<typename... P>
   T query_until(int f, const P&... s) const {
      T res = 0;
      for (; f != 0; f -= (f & -f)) {
         res += mem_[f].query_until(s...);
      }
      return res;
   }

private:
   template<std::size_t... I, typename... P>
   T query(std::index_sequence<I...> i, const std::array<int, 2 * D>& indices) {
      T res = 0;
      for (unsigned i = 0; i < (1 << D); ++i) {
         res += (std::popcount(i) % 2 == D % 2 ? +1 : -1) * query_until(indices[bool(i & (1 << I)) * D + I]...);
      }
      return res;
   }

   std::vector<fenwick_tree<T, D - 1>> mem_;
};

template<typename T>
class fenwick_tree<T, 0> {
public:
   void modify_add(const T& d) {
      v_ += d;
   }

   T query_until( ) const {
      return v_;
   }

private:
   T v_ = 0;
};
