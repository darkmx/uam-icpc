// Adjacency list implementation of Dinic's blocking flow algorithm.
// This is very fast in practice, and only loses to push-relabel flow.
//
// Running time:
//       O(|V|^2 |E|)
//
// INPUT:
//       - graph, constructed using AddEdge()
//       - source
//       - sink
//
// OUTPUT:
//       - maximum flow value
//       - To obtain the actual flow values, look at all edges with
//          capacity > 0 (zero capacity edges are residual edges).

#include <cmath>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct Edge {
   int u, v, cap, flow;

   Edge() {}
   Edge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
   int N;
   vector<Edge> E;
   vector<vector<int>> g;
   vector<int> d, pt;
   Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

   void AddEdge(int u, int v, int cap) {
      if (u != v) {
         E.emplace_back(Edge(u, v, cap));
         g[u].emplace_back(E.size() - 1);
         E.emplace_back(Edge(v, u, 0));
         g[v].emplace_back(E.size() - 1);
      }
   }
   bool BFS(int S, int T) {
      queue<int> q({S});
      fill(d.begin(), d.end(), N + 1);
      d[S] = 0;
      while(!q.empty()) {
         int u = q.front(); q.pop();
         if (u == T) break;
         for (int k: g[u]) {
            Edge &e = E[k];
            if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
               d[e.v] = d[e.u] + 1;
               q.emplace(e.v);
            }
         }
      }
      return d[T] != N + 1;
   }
   int DFS(int u, int T, int flow = -1) {
      if (u == T || flow == 0) return flow;
      for (int &i = pt[u]; i < g[u].size(); ++i) {
         Edge &e = E[g[u][i]];
         Edge &oe = E[g[u][i]^1];
         if (d[e.v] == d[e.u] + 1) {
            int amt = e.cap - e.flow;
            if (flow != -1 && amt > flow) amt = flow;
            if (int pushed = DFS(e.v, T, amt)) {
               e.flow += pushed;
               oe.flow -= pushed;
               return pushed;
            }
         }
      }
      return 0;
   }
   int MaxFlow(int S, int T) {
      int total = 0;
      while (BFS(S, T)) {
         fill(pt.begin(), pt.end(), 0);
         while (int flow = DFS(S, T))
            total += flow;
      }
      return total;
   }
};

int main( ) {
   int n, e;
   std::cin >> n >> e;
   Dinic dinic(n);

   for(int i = 0; i < e; i++) {
      int u, v, cap;
      std::cin >> u >> v >> cap;
      dinic.AddEdge(u, v, cap);
   }
   std::cout << dinic.MaxFlow(0, n - 1);
}
