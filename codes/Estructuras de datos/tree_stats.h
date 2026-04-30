/**
 * Nombre: Preprocesamiento de árboles
 * Autor: rcc
 * Descripción: DFS estándar que preprocesa un árbol para calcular algunos datos útiles.
 * Complejidad: $O(n)$.
 * Uso:
 *  tree_stats stats(raiz, adyacencia);
 */
#include <algorithm>
#include <vector>

struct tree_stats {
   std::vector<int> alturas, pesos, contorno;   // alturas siempre, pesos para hld, contorno para lca
   tree_stats(int raiz, const std::vector<std::vector<int>>& adj)
   : alturas(adj.size( )), pesos(adj.size( )) {
      calcula(raiz, -1, adj);
   }

private:
   void calcula(int actual, int anterior, const std::vector<std::vector<int>>& adj) {
      int altura = 0, peso = 0;
      contorno.push_back(actual);
      for (auto v : adj[actual]) {
         if (v != anterior) {
            calcula(v, actual, adj);
            altura = std::max(altura, alturas[v]), peso += pesos[v];
            contorno.push_back(actual);
         }
      }
      alturas[actual] = altura + 1, pesos[actual] = peso + 1;
   }
};
