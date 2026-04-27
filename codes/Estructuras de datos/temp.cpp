#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

template<typename T, typename F = const T&(*)(const T&, const T&)>
struct segment_tree {
   segment_tree(std::vector<T>&& init, T v0, F f)
   : neutro(std::move(v0)), funcion(std::move(f)) {
      pisos.push_back(std::move(init));
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
         pisos[p][i] = std::move(v);
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
   T neutro;
   F funcion;
};

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
         if (v == anterior) {
            continue;
         }
         calcula(v, actual, adj);
         altura = max(altura, alturas[v]), peso += pesos[v];
         contorno.push_back(actual);
      }
      alturas[actual] = altura + 1, pesos[actual] = peso + 1;
   }
};

template<typename T>
struct lca_tree_base {
   lca_tree_base(tree_stats&& s)
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

struct lca_tree : lca_tree_base<lca_tree> {        // usa segment_tree; útil en general
   lca_tree(tree_stats&& s)
   : lca_tree_base<lca_tree>(move(s)), st(move(s.contorno), primera.size( ), op(move(s.alturas))) {
   }

   decltype(segment_tree(vector<int>( ), int( ), declval<op>( ))) st;
};

struct hld_base {
   explicit hld_base(int n)
   : adj(n) {
      grupos.reserve(n);
   }

   void add_edge(int i, int j) {
      adj[i].push_back(j);
      adj[j].push_back(i);
   }

   void build( ) {
      tree_stats stats(0, adj);
      descomposicion(0, -1, stats.pesos, grupos[0]);
      arbol_lca = make_unique<lca_tree>(move(stats));
   }

private:
   void descomposicion(int actual, int anterior, const vector<int>& pesos, vector<int>& trabajo) {
      for (auto v : adj[actual]) {
         if (v == anterior) {
            continue;
         }
         if (2 * pesos[v] >= pesos[actual]) {
            trabajo.push_back(v);
            descomposicion(v, actual, pesos, trabajo);
         } else {
            vector<int> temp = { actual, v };
            descomposicion(v, actual, pesos, temp);
            grupos.push_back(move(temp));
         }
      }
   }

protected:
   vector<vector<int>> adj;
   vector<vector<int>> grupos = { { 0 } };
   unique_ptr<lca_tree> arbol_lca;
};

template<typename T, typename F>
struct hld_vertex : hld_base {
   explicit hld_vertex(int n, T v0, F f)
   : hld_base(n), costos(n), invertido(n, { -1, -1 }), neutro(move(v0)), funcion(move(f)) {
   }

   void initial_cost(int i, T c) {
      costos[i] = move(c);
   }

   void update_cost(int i, T c) {
      aristas[invertido[i].first].replace(invertido[i].second, move(c));
   }

   void build( ) {
      hld_base::build( );
      for (int i = 0; i < grupos.size( ); ++i) {
         vector<T> costos_local;
         for (int j = bool(i); j < grupos[i].size( ); ++j) {
            invertido[grupos[i][j]] = { i, costos_local.size( ) };
            costos_local.push_back(costos[grupos[i][j]]);
         }
         aristas.push_back(segment_tree(move(costos_local), neutro, funcion));
      }
   }

   auto query(int i, int j) {
      int ancestro = arbol_lca->query(i, j);
      auto res = aristas[invertido[ancestro].first][invertido[ancestro].second];
      for (int hijo : { i, j }) {
         do {
            auto [tope, pos_tope] = (invertido[hijo].first == invertido[ancestro].first ? pair(-1, invertido[ancestro].second + 1) : pair(grupos[invertido[hijo].first][0], 0));
            res = funcion(res, aristas[invertido[hijo].first].query(pos_tope, invertido[hijo].second + 1));
            hijo = tope;
         } while (hijo != -1);
      }
      return res;
   }

private:
   vector<T> costos;
   vector<pair<int, int>> invertido;
   vector<decltype(segment_tree(vector<T>( ), declval<T>( ), declval<F>( )))> aristas;
   const T neutro;
   const F funcion;
};

int main( ) {
   std::cin.tie(nullptr)->sync_with_stdio(false);

   int n, q;
   std::cin >> n >> q;

   hld_vertex hld(n, -1, [](int c1, int c2) {
      return std::max(c1, c2);
   });
   for (int i = 0; i < n; ++i) {
      int costo;
      std::cin >> costo;
      hld.initial_cost(i, costo);
   }

   for (int i = 0; i < n - 1; ++i) {
      int x, y;
      std::cin >> x >> y;
      x -= 1, y -= 1;
      hld.add_edge(x, y);
   }
   hld.build( );

   for (int i = 0; i < q; ++i) {
      int t, x, y;
      std::cin >> t >> x >> y;

      if (t == 1) {
         x -= 1;
         hld.update_cost(x, y);
      } else if (t == 2) {
         x -= 1, y -= 1;
         std::cout << hld.query(x, y) << "\n";
      }
   }
}
