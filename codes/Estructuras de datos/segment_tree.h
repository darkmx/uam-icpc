/**
 * Nombre: Árbol de segmentos
 * Autor: rcc
 * Descripción: Estructura de datos para monoides $(T, \cdot : T \times T \rightarrow T, n \in T)$, permite realizar actualizaciones
 *              de elementos y calcular el producto de los elementos en un intervalo.
 * Complejidad: $O(\log n)$, se asume que $f$ es de tiempo constante.
 * Estado: probado en https://cses.fi/problemset/task/2134
 * Uso:
 *  auto s = segment_tree(std::move(vector_inicial), assoc_op(0, std::plus( )));
 *  int suma1 = s.query(5, 10);
 *  s.replace(2, rand( ));
 *  int suma2 = s.query(5, 10);
 */
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template<typename T, typename F = const T&(*)(const T&, const T&)>
struct assoc_op {
   T neutro;
   F funcion;
};

template<typename OP>
struct segment_tree {
   const OP op;
   using T = decltype(OP::neutro);

   segment_tree(std::vector<T>&& v, OP p)
   : op(std::move(p)) {
      for (pisos.push_back(std::move(v)); pisos.back( ).size( ) > 1; ) {
         pisos.emplace_back(pisos.back( ).size( ) / 2);
         for (int i = 0, k = pisos.size( ) - 2; i < pisos[k].size( ) / 2; ++i) {
            pisos.back( )[i] = op.funcion(pisos[k][2 * i], pisos[k][2 * i + 1]);
         }
      }
   }

   int size( ) const {
      return pisos[0].size( );
   }

   const T& operator[](int i) const {
      return pisos[0][i];
   }

   void replace(int i, T v) {
      pisos[0][i] = std::move(v);
      for (int p = 0; i - i % 2 + 1 != pisos[p].size( ); ++p, i /= 2) {
         pisos[p + 1][i / 2] = op.funcion(pisos[p][i - i % 2], pisos[p][i - i % 2 + 1]);
      }
   }

   T query(int ini, int fin) const {
      T res = op.neutro;
      visit(ini, fin, [&](const T& valor) {
         res = op.funcion(res, valor);
      });
      return res;
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      const T* derecha[64], **w = &derecha[0];
      for (int p = 0; ini != fin; ++p, ini /= 2, fin /= 2) {
         if (ini % 2 == 1) {
            vis(pisos[p][ini++]);
         }
         if (fin % 2 == 1) {
            *w++ = &pisos[p][--fin];
         }
      }
      while (w != &derecha[0]) {
         vis(**--w);
      }
   }

private:
   std::vector<std::vector<T>> pisos;
};

template<typename T, typename... P>    // función sólo necesaria para hld
auto make_segment_tree(std::vector<T>&& v, assoc_op<P...> a) {
   return segment_tree(std::move(v), a);
}
