/**
 * Nombre: Árbol de segmentos perezoso
 * Autor: rcc
 * Descripción: Árbol de segmentos con capacidad para modificar valores de
 *              intervalos grandes y calcular consultas de intervalos.
 * Complejidad: $O(\log n)$
 * Estado: probado en https://codeforces.com/gym/106063/problem/L
 * Uso:
 * auto s = lazy_segment_tree(std::move(vector_inicial), lazy_assoc_op(
 *  0,
 *  0,
 *  std::plus( ),
 *  [](int& valor, int cubiertos, int cambio) {
 *     valor += cambio * cubiertos;
 *     return true;
 *  },
 *  [](int cambio1, int cambio2) {
 *     return cambio1 + cambio2;
 *  }));
 * int suma1 = s.query(5, 10);
 * s.update_with(2, 8, +1);
 * int suma2 = s.query(5, 10);
 */
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template<typename T, typename U, typename FQ = const T&(*)(const T&, const T&), typename FU = bool(*)(T&, int, const U&), typename FP = const U&(*)(const U&, const U&)>
struct lazy_assoc_op {
   T neutro;
   U neutro_update;
   FQ funcion;
   FU funcion_update;
   FP funcion_propagar;
};

template<typename OP>
struct lazy_segment_tree {
   using T = decltype(OP::neutro);
   using U = decltype(OP::neutro_update);

   lazy_segment_tree(std::vector<T>&& init, OP p)
   : op(std::move(p)), mem(init.size( ) * 2) {
      if (auto p = init.data( ); !init.empty( )) {
         construye(0, 0, size( ), p);
      }
   }

   int size( ) const {
      return mem.size( ) / 2;
   }

   T operator[](int i) const {
      return query(i, i + 1);
   }

   T query(int ini, int fin) const {
      T res = op.neutro;
      visit(0, ini, fin, 0, size( ), [&](const std::pair<T, U>& actual, int cubiertos) {
         res = op.funcion(res, actual.first);
      });
      return res;
   }

   void update_with(int ini, int fin, const U& u) {
      visit(0, ini, fin, 0, size( ), [&](std::pair<T, U>& actual, int cubiertos) {
         actualiza(actual, cubiertos, u);
      });
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      visit(0, ini, fin, 0, size( ), [&](const std::pair<T, U>& actual, int cubiertos) {
         vis(actual.first, cubiertos);
      });
   }

private:
   const std::pair<T, U>& construye(int i, int ini, int fin, T*& p) {
      if (fin - ini == 1) {
         return mem[i] = { std::move(*p++), op.neutro_update };
      } else {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         auto t1 = construye(izq, ini, mitad, p).first, t2 = construye(der, mitad, fin, p).first;
         return mem[i] = { op.funcion(t1, t2), op.neutro_update };
      }
   }

   template<typename V>
   void visit(int i, int qi, int qf, int ini, int fin, V&& vis) const {
      if (qi == ini && qf == fin && ini != fin) {
         vis(mem[i], fin - ini);
      } else if (qi < qf) {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         actualiza(mem[izq], tam / 2, mem[i].second);
         actualiza(mem[der], tam - tam / 2, mem[i].second);
         visit(izq, qi, std::min(qf, mitad), ini, mitad, vis);
         visit(der, std::max(qi, mitad), qf, mitad, fin, vis);
         mem[i] = { op.funcion(mem[izq].first, mem[der].first), op.neutro_update };
      }
   }

   void actualiza(std::pair<T, U>& actual, int cubiertos, const U& cambio) const {
      if (cambio != op.neutro_update && op.funcion_update(actual.first, cubiertos, cambio)) {
         actual.second = (actual.second != op.neutro_update ? op.funcion_propagar(actual.second, cambio) : cambio);
      }
   }

   OP op;
   mutable std::vector<std::pair<T, U>> mem;
};

template<typename T, typename... P>    // función sólo necesaria para hld
auto make_segment_tree(std::vector<T>&& v, lazy_assoc_op<P...> a) {
   return lazy_segment_tree(std::move(v), a);
}
