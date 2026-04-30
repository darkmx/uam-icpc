/**
 * Nombre: Descomposición heavy-light
 * Autor: rcc
 * Descripción: Descomposición de un árbol con ejemplo de queries en el camino entre dos vértices
 * Complejidad: $O(n \log n)$ para procesar, $O(\log^2 n)$ por query
 * Estado: probado en https://cses.fi/problemset/task/2134 y https://codeforces.com/gym/106063/problem/L
 * Uso:
 *  auto hv = make_hld_vertex(std::move(vector_inicial), std::move(vector_costos), assoc_op o lazy_assoc_op);
 *  hv.replace(i, 7);
 *  int r1 = hv.query(i, j);
 *  auto he = make_hld_edge(std::move(vector_inicial), std::move(mapa_costos), assoc_op o lazy_assoc_op);
 *  he.update_with(i, j, 7);     // requiere lazy
 *  int r2 = he.query(i, j);
 */
#include "tree_stats.h"
#include <map>
#include <vector>

template<typename OP, typename F, bool VMODE>
struct hld_base {
   using T = decltype(OP::neutro);

   hld_base(std::vector<std::vector<int>> a, OP&& p, F&& f, std::bool_constant<VMODE>)
   : adj(std::move(a)), op(std::move(p)), funcion_costos(std::move(f)), invertido(adj.size( )) {
      tree_stats stats(0, adj);
      grupos.reserve(adj.size( ));
      alturas = std::move(stats.alturas);
      descomposicion(0, -1, stats.pesos, grupos[0]);
      for (int i = 0; i < grupos.size( ); ++i) {
         std::vector<T> costos_local;
         for (int j = (!VMODE || i != 0); j < grupos[i].size( ); ++j) {
            invertido[grupos[i][j]] = { i, costos_local.size( ) + !VMODE };
            costos_local.push_back(funcion_costos(grupos[i][j - 1], grupos[i][j]));
         }
         aristas.push_back(make_segment_tree(move(costos_local), op));
      }
   }

   int lowest_common_ancestor(int i, int j) const {      // con hld se puede implementar el lca de otra forma
      while (invertido[i].first != invertido[j].first) {
         int ri = grupos[invertido[i].first][0], rj = grupos[invertido[j].first][0];
         (std::pair(alturas[ri], alturas[i]) < std::pair(alturas[rj], alturas[j]) ? i = ri : j = rj);
      }
      return (alturas[i] >= alturas[j] ? i : j);
   }

   auto query(int i, int j) {
      T res = op.neutro;
      visit(i, j, [&](auto& st, int ini, int fin) {
         res = op.funcion(res, st.query(ini, fin));
      });
      return res;
   }

   void replace(int i, const T& c) {         // sólo si se usa segment_tree
      static_assert(VMODE);
      aristas[invertido[i].first].replace(invertido[i].second, c);
   }

   void update_with(int i, int j, auto u) {  // sólo si se usa lazy_segment_tree
      visit(i, j, [&](auto& st, int ini, int fin) {
         st.update_with(ini, fin, u);
      });
   }

protected:
   void descomposicion(int actual, int anterior, const std::vector<int>& pesos, std::vector<int>& trabajo) {
      for (auto v : adj[actual]) {
         if (v == anterior) {
            continue;
         }
         if (2 * pesos[v] >= pesos[actual]) {
            trabajo.push_back(v);
            descomposicion(v, actual, pesos, trabajo);
         } else {
            std::vector<int> temp = { actual, v };
            descomposicion(v, actual, pesos, temp);
            grupos.push_back(move(temp));
         }
      }
   }

   template<typename V>
   void visit(int i, int j, V&& vis) {
      int lca = lowest_common_ancestor(i, j);
      vis(aristas[invertido[lca].first], invertido[lca].second, invertido[lca].second + VMODE);
      for (int hijo : { i, j }) {
         do {
            auto [subir, pos_tope] = (invertido[hijo].first == invertido[lca].first ? std::pair(-1, invertido[lca].second + VMODE) : std::pair(grupos[invertido[hijo].first][0], 0));
            vis(aristas[invertido[hijo].first], pos_tope, invertido[hijo].second + VMODE);
            hijo = subir;
         } while (hijo != -1);
      }
   }

   std::vector<std::vector<int>> adj;
   F funcion_costos;
   OP op;
   std::vector<int> alturas;
   std::vector<std::vector<int>> grupos = { { 0 } };
   std::vector<std::pair<int, int>> invertido;
   std::vector<decltype(make_segment_tree(std::vector<T>( ), op))> aristas;
};

template<typename OP, typename T>
auto make_hld_vertex(std::vector<std::vector<int>>&& adj, std::vector<T>&& costos, OP&& op) {
   return hld_base(std::move(adj), std::move(op), [c = move(costos)](int i, int j) {
      return c[j];
   }, std::bool_constant<true>( ));
}

template<typename OP, typename T>
auto make_hld_edge(std::vector<std::vector<int>>&& adj, std::map<std::pair<int, int>, T>&& costos, OP&& op) {
   return hld_base(std::move(adj), std::move(op), [c = std::move(costos)](int i, int j) {
      return c.find({ i, j })->second;
   }, std::bool_constant<false>( ));
}
