/**
 * Nombre: Ancestro común más bajo
 * Autor: rcc
 * Descripción: Calcula el ancestro común de dos vértices a partir de haber precalculado un preorden aumentado o contorno.
 * Complejidad: $O(n)$ para el preprocesamiento y $O(\log n)$ para las queries.
 * Uso:
 *  lca_tree lca(tree_stats(raiz, adyacencia));      // usa segment\_tree
 *  lca_lazy_tree lca(tree_stats(raiz, adyacencia)); // usa lazy\_segment\_tree
 *  int ancestro = lca.query(i, j);
 */
#include "segment_tree.h"        /// keep-include
#include "lazy_segment_tree.h"   /// keep-include
#include <algorithm>
#include <type_traits>
#include <vector>

struct tree_stats {     // si no se usará en hld se puede quitar lo relacionado con pesos
   vector<int> alturas, pesos, contorno;

   tree_stats(int raiz, const vector<vector<int>>& adj)
   : alturas(adj.size( )), pesos(adj.size( )) {
      calcula(raiz, -1, adj);
   }

private:
   void calcula(int actual, int anterior, const vector<vector<int>>& adj) {
      int altura = 0, peso = 0;
      contorno.push_back(actual);
      for (auto v : adj[actual]) {
         if (v != anterior) {
            calcula(v, actual, adj);
            altura = max(altura, alturas[v]), peso += pesos[v];
            contorno.push_back(actual);
         }
      }
      alturas[actual] = altura + 1, pesos[actual] = peso + 1;
   }
};

template<typename T>
struct lca_base {
   lca_base(tree_stats&& s)
   : primera(s.alturas.size( )) {
      for (int i = s.contorno.size( ) - 1; i >= 0; --i) {
         primera[s.contorno[i]] = i;
      }
   }

   int query(int i, int j) const {
      return ((const T&)*this).st.query(min(primera[i], primera[j]), max(primera[i], primera[j]) + 1);
   }

protected:
   struct op {
      vector<int> alturas;

      op(vector<int>&& a)
      : alturas(move(a)) {
         alturas.push_back(-1);
      }
      int operator()(int i, int j) const {
         return (alturas[i] > alturas[j] ? i : j);
      }
   };

   vector<int> primera;
};

struct lca_tree : lca_base<lca_tree> {        // usa segment_tree; útil en general
   lca_tree(tree_stats&& s)
   : lca_base<lca_tree>(move(s)), st(move(s.contorno), primera.size( ), op(move(s.alturas))) {
   }

   decltype(segment_tree(vector<int>( ), int( ), declval<op>( ))) st;
};

struct lca_lazy_tree : lca_base<lca_tree> {   // usa lazy_segment_tree; útil si se usará hdl con lazy (para compartir implementación)
   struct dummy {
      auto operator<=>(const dummy&) const = default;

      bool operator()(int& v, int n, dummy) const {
         return true;
      }
      dummy operator()(dummy, dummy) const {
         return dummy( );
      }
   };

   lca_lazy_tree(tree_stats&& s)
   : lca_base<lca_tree>(move(s)), st(move(s.contorno), primera.size( ), dummy( ), op(move(s.alturas)), dummy( ), dummy( )) {
   }

   decltype(lazy_segment_tree(vector<int>( ), int( ), dummy( ), declval<op>( ), dummy( ), dummy( ))) st;
};
