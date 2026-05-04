/**
 * Nombre: Descomposición heavy-light
 * Autor: rcc
 * Descripción: Descomposición de un árbol con ejemplo de queries en el camino entre dos vértices
 * Complejidad: $O(n \log n)$ para procesar, $O(\log^2 n)$ por query
 * Estado: probado en https://cses.fi/problemset/task/1137, https://cses.fi/problemset/task/2134 y https://codeforces.com/gym/106063/problem/L
 * Uso:
 *  auto hv = make_hld_vertex(raiz, std::move(adyacencia), std::move(vector_costos), assoc_op o lazy_assoc_op);
 *  hv.replace(i, 7);
 *  int r1 = hv.query(i, j);
 *  auto he = make_hld_edge(raiz, std::move(vector_inicial), std::move(mapa_costos), assoc_op o lazy_assoc_op);
 *  he.update_with(i, j, 7);     // requiere lazy
 *  int r2 = he.query(i, j);
 */
#include "tree_stats.h"
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

template<typename OP, typename F, bool VMODE>
struct hld_base {
   using T = decltype(OP::neutro);

   hld_base(int raiz, std::vector<std::vector<int>>&& adj, OP&& op, F&& fc, std::bool_constant<VMODE>)
   : subarbol(adj.size( )), invertido(adj.size( )) {
      tree_stats stats(0, adj);
      alturas = std::move(stats.alturas), pesos = std::move(stats.pesos);
      std::vector<int> grupo = { raiz }; std::vector<T> costos;
      descomposicion(raiz, -1, adj, grupo, costos, fc);
      st.emplace(std::move(costos), std::move(op));
   }

   auto& segment_tree( ) const {                // sólo se se usará visit explicitamente
      return *st;
   }

   int lowest_common_ancestor(int i, int j) const {   // con hld se puede implementar el lca de otra forma
      while (invertido[i].first != invertido[j].first) {
         int ri = grupos[invertido[i].first].first, rj = grupos[invertido[j].first].first;
         (std::pair(alturas[ri], alturas[i]) < std::pair(alturas[rj], alturas[j]) ? i = ri : j = rj);
      }
      return (alturas[i] >= alturas[j] ? i : j);
   }

   void replace(int i, const T& c) {            // sólo si se usa hld_vertex y segment_tree
      static_assert(VMODE);
      st->replace(invertido[i].second, c);
   }

   T subtree_query(int i) const {
      return st->query(invertido[i].second, invertido[i].second + pesos[i] - !VMODE);
   }

   void subtree_update_with(int i, auto u) {    // sólo si se usa lazy_segment_tree
      return st->update_with(invertido[i].second, invertido[i].second + pesos[i] - !VMODE, u);
   }

   template<typename V>
   void subtree_visit(int i, V&& vis) {
      return st->visit(invertido[i].second, invertido[i].second + pesos[i] - !VMODE, vis);
   }

   T path_query(int i, int j) const {
      T res = st->op.neutro;
      path_visit(i, j, [&](int v, int ini, int fin) {
         res = st->op.funcion(res, st->query(ini, fin));
      });
      return res;
   }

   void path_update_with(int i, int j, auto u) {   // sólo si se usa lazy_segment_tree
      path_visit(i, j, [&](int v, int ini, int fin) {
         st->update_with(ini, fin, u);
      });
   }

   template<typename V>
   void path_visit(int i, int j, V&& vis) const {
      int lca = lowest_common_ancestor(i, j);
      vis(lca, invertido[lca].second, invertido[lca].second + VMODE);
      for (int hijo : { i, j }) {
         while (hijo != lca) {
            auto [subir, pos_tope] = (invertido[hijo].first == invertido[lca].first ? std::pair(lca, invertido[lca].second + VMODE) : grupos[invertido[hijo].first]);
            vis(hijo, pos_tope, invertido[hijo].second + VMODE);
            hijo = subir;
         }
      }
   }

private:
   void descomposicion(int actual, int anterior, std::vector<std::vector<int>>& adj, std::vector<int>& grupo, std::vector<T>& costos, F& fc) {
      std::erase(adj[actual], anterior);
      std::sort(adj[actual].begin( ), adj[actual].end( ), [&](int i, int j) {
         return pesos[i] < pesos[j];
      });

      if (!adj[actual].empty( ) && 2 * pesos[adj[actual].back( )] >= pesos[actual]) {
         grupo.push_back(adj[actual].back( ));
         descomposicion(adj[actual].back( ), actual, adj, grupo, costos, fc);
         adj[actual].pop_back( );
      } else {
         grupos.emplace_back(grupo[0], costos.size( ));
         for (int i = (!VMODE || costos.size( ) != 0); i < grupo.size( ); ++i) {
            invertido[grupo[i]] = { grupos.size( ) - 1, costos.size( ) + !VMODE };
            costos.push_back(fc(grupo[i - 1], grupo[i]));
         }
      }
      for (int v : adj[actual]) {
         grupo = { actual, v };
         descomposicion(v, actual, adj, grupo, costos, fc);
      }
   }

   std::vector<int> alturas, pesos;
   std::vector<std::pair<int, int>> subarbol;
   std::vector<std::pair<int, int>> invertido, grupos;   // (id_grupo, pos) y (repr, pos_ini)
   std::optional<decltype(make_segment_tree(std::vector<T>( ), std::declval<OP>( )))> st;
};

template<typename OP, typename T>
auto make_hld_vertex(int raiz, std::vector<std::vector<int>>&& adj, std::vector<T>&& costos, OP&& op) {
   return hld_base(raiz, std::move(adj), std::move(op), [c = std::move(costos)](int i, int j) {
      return c[j];
   }, std::bool_constant<true>( ));
}

template<typename OP, typename T>
auto make_hld_edge(int raiz, std::vector<std::vector<int>>&& adj, std::map<std::pair<int, int>, T>&& costos, OP&& op) {
   return hld_base(raiz, std::move(adj), std::move(op), [c = std::move(costos)](int i, int j) {
      return c.find({ i, j })->second;
   }, std::bool_constant<false>( ));
}
