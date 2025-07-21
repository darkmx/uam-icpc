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
   : neutro(std::move(v0)), neutro_update(std::move(u0)), funcion(std::move(fq)), funcion_update(std::move(fu)), funcion_propagar(std::move(fp)) {
      pisos.emplace_back(init.size( ));
      for (int i = 0; i < init.size( ); ++i) {
         pisos.back( )[i] = { std::move(init[i]), neutro_update };
      }
      while (pisos.back( ).size( ) > 1) {
         pisos.emplace_back(pisos.back( ).size( ) / 2);
         for (int i = 0, t = pisos.size( ) - 2; i < pisos[t].size( ) / 2; ++i) {
            pisos.back( )[i] = { funcion(pisos[t][2 * i].first, pisos[t][2 * i + 1].first), neutro_update };
         }
      }
   }

   int size( ) const {
      return pisos[0].size( );
   }

   T operator[](int i) const {
      return query(i, i + 1);
   }

   T query(int ini, int fin) const {
      T res = neutro;
      visit(pisos.size( ) - 1, 0, ini, fin, [&](const std::pair<T, U>& nodo, int tam) {
         res = funcion(res, nodo.first);
      });
      return res;
   }

   void update_with(int ini, int fin, const U& cambio) {
      visit(pisos.size( ) - 1, 0, ini, fin, [&](std::pair<T, U>& nodo, int cubiertos) {
         actualiza(nodo, cubiertos, cambio);
      });
   }

private:
   template<typename V>
   void visit(int p, int i, int ini, int fin, V&& vis) const {
      while (i >= pisos[p].size( )) {
         p -= 1, i *= 2;
      }

      int ini_actual = i * (1 << p), fin_actual = ini_actual + (1 << p);
      if (fin > fin_actual) {
         visit(p - 1, 2 * i + 2, std::max(fin_actual, ini), fin, vis);
         fin = fin_actual;
      }
      if (ini == ini_actual && fin == fin_actual) {;
         return vis(pisos[p][i], 1 << p);
      } else if (ini >= fin) {
         return;
      }

      actualiza(pisos[p - 1][2 * i + 0], 1 << (p - 1), pisos[p][i].second);
      actualiza(pisos[p - 1][2 * i + 1], 1 << (p - 1), pisos[p][i].second);
      visit(p - 1, 2 * i + 0, ini, std::min(fin, ini_actual + (1 << (p - 1))), vis);
      visit(p - 1, 2 * i + 1, std::max(ini, fin_actual - (1 << (p - 1))), fin, vis);
      pisos[p][i] = { funcion(pisos[p - 1][2 * i].first, pisos[p - 1][2 * i + 1].first), neutro_update };
   }

   void actualiza(std::pair<T, U>& actual, int cubiertos, const U& cambio) const {
      if (cambio != neutro_update && funcion_update(actual.first, cubiertos, cambio)) {
         actual.second = (actual.second != neutro_update ? funcion_propagar(actual.second, cambio) : cambio);
      }
   }

   mutable std::vector<std::vector<std::pair<T, U>>> pisos;
   T neutro;
   U neutro_update;
   FQ funcion;
   FU funcion_update;
   FP funcion_propagar;
};

// < C++17 checar segment_tree
