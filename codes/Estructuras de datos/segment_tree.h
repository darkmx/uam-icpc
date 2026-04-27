/**
 * Nombre: Árbol de segmentos
 * Autor: rcc
 * Descripción: Estructura de datos para monóides $(T, \cdot : T \times T \rightarrow T, n \in T)$, permite realizar actualizaciones
 *              de elementos y calcular el producto de los elementos en un intervalo.
 * Complejidad: $O(\log n)$, se asume que $f$ es de tiempo constante.
 * Uso:
 *  auto s = segment_tree(move(vector_inicial), 0, plus( ));
 *  int suma1 = s.query(5, 10);
 *  s.replace(i, rand( ));
 *  int suma2 = s.query(5, 10);
 */
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template<typename T, typename F = const T&(*)(const T&, const T&)>
class segment_tree {
public:
   segment_tree(vector<T>&& init, T v0, F f)
   : neutro(move(v0)), funcion(move(f)) {
      pisos.push_back(move(init));
      while (pisos.back( ).size( ) > 1) {
         pisos.emplace_back(pisos.back( ).size( ) / 2);
         for (int i = 0, t = pisos.size( ) - 2; i < pisos[t].size( ) / 2; ++i) {
            pisos.back( )[i] = funcion(pisos[t][2 * i], pisos[t][2 * i + 1]);
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
      for (int p = 0;; ++p, i /= 2) {
         pisos[p][i] = move(v);
         if (i + (i % 2 == 0) == pisos[p].size( )) {
            break;
         }
         v = funcion(pisos[p][i - i % 2], pisos[p][i - i % 2 + 1]);
      }
   }

   T query(int ini, int fin) const {
      T res = neutro;
      visit(ini, fin, [&](const T& valor) {
         res = funcion(res, valor);
      });
      return res;
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {   // callback sobre los nodos más representativos dentro de un rango específico
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
   vector<vector<T>> pisos;
   T neutro;
   F funcion;
};

// < C++17
/*template<typename T, typename F = const T&(*)(const T&, const T&)>
auto make_segment_tree(vector<T> inicial, T v0, F f) {
   return segment_tree<T, F>(move(inicial), move(v0), move(f));
}*/
