/**
 * Nombre: Árbol de segmentos perezoso
 * Autor: rcc
 * Descripción: Árbol de segmentos con capacidad para modificar valores de
 *              intervalos grandes y calcular consultas de intervalos.
 * Complejidad: $O(\log n)$
 * Uso:
 *  auto s = lazy_segment_tree(std::move(vector_inicial), 0, 0, std::plus( ),
 *   [](int& valor, int cubiertos, int cambio) {
 *      valor += cambio * cubiertos;
 *      return true;
 *   },
 *   [](int cambio1, int cambio2) {
 *      return cambio1 + cambio2;
 *   });
 *  int suma1 = s.query(5, 10);
 *  s.arbol.update_with(2, 8, +1);
 *  int suma2 = s.query(5, 10);
 */
#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

template<typename T, typename U, typename FQ = const T&(*)(const T&, const T&), typename FU = bool(*)(T&, int, const U&), typename FP = const U&(*)(const U&, const U&)>
class lazy_segment_tree {
public:
   lazy_segment_tree(std::vector<T>&& init, T v0, U u0, FQ fq, FU fu, FP fp)
   : mem(init.size( ) * 2), neutro(std::move(v0)), neutro_update(std::move(u0)), funcion(std::move(fq)), funcion_update(std::move(fu)), funcion_propagar(std::move(fp)) {
      auto p = init.data( );
      construye(0, 0, size( ), p);
   }

   int size( ) const {
      return mem.size( ) / 2;
   }

   T operator[](int i) const {
      return query(i, i + 1);
   }

   T query(int ini, int fin) const {
      T res = neutro;
      visit(0, ini, fin, 0, size( ), [&](const std::pair<T, U>& actual, int cubiertos) {
         res = funcion(res, actual.first);
      });
      return res;
   }

   void update_with(int ini, int fin, const U& v) {
      visit(0, ini, fin, 0, size( ), [&](std::pair<T, U>& actual, int cubiertos) {
         actualiza(actual, cubiertos, v);
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
         return mem[i] = { std::move(*p++), neutro_update };
      } else {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         return mem[i] = { funcion(construye(izq, ini, mitad, p).first, construye(der, mitad, fin, p).first), neutro_update };
      }
   }

   template<typename V>
   void visit(int i, int qi, int qf, int ini, int fin, V&& vis) const {
      if (qi == ini && qf == fin) {
         vis(mem[i], fin - ini);
      } else if (qi < qf) {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         actualiza(mem[izq], tam / 2, mem[i].second);
         actualiza(mem[der], tam - tam / 2, mem[i].second);
         visit(izq, qi, std::min(qf, mitad), ini, mitad, vis);
         visit(der, std::max(qi, mitad), qf, mitad, fin, vis);
         mem[i] = { funcion(mem[izq].first, mem[der].first), neutro_update };
      }
   }

   void actualiza(std::pair<T, U>& actual, int cubiertos, const U& cambio) const {
      if (cambio != neutro_update && funcion_update(actual.first, cubiertos, cambio)) {
         actual.second = (actual.second != neutro_update ? funcion_propagar(actual.second, cambio) : cambio);
      }
   }

   mutable std::vector<std::pair<T, U>> mem;
   T neutro;
   U neutro_update;
   FQ funcion;
   FU funcion_update;
   FP funcion_propagar;
};

// < C++17 checar segment_tree
