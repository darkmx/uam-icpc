/**
 * Nombre: Puentes de una gráfica
 * Autor: rcc
 * Descripción: Dado un grafo no dirigido. Un puente se define como una arista que, al ser removida, desconecta el grafo
 *              (o, más precisamente, aumenta el número de componentes conexos en el grafo).
 *              Devuelve todos los puentes en el grafo dado.
 * Complejidad: $O(n + m)$
 */
#include <algorithm>
#include <vector>

void dfs(int actual, int anterior, const std::vector<int> adyacencia[], std::vector<bool>& visitado, int& id, std::vector<int>& tin, std::vector<int>& low, std::vector<std::pair<int, int>>& res) {
   visitado[actual] = true, tin[actual] = low[actual] = id++;
   bool anterior_omitido = false;
   for (int vecino : adyacencia[actual]) {
      if (vecino == anterior && !anterior_omitido) {
         anterior_omitido = true;
         continue;
      }
      if (visitado[vecino]) {
         low[actual] = std::min(low[actual], tin[vecino]);
      } else {
         dfs(vecino, actual, adyacencia, visitado, id, tin, low, res);
         low[actual] = std::min(low[actual], low[vecino]);
         if (low[vecino] > tin[actual]) {
            res.emplace_back(std::min(actual, vecino), std::max(actual, vecino));
         }
      }
   }
}

std::vector<std::pair<int, int>> calcula_puentes(const std::vector<int> adyacencia[], int n) {
   std::vector<bool> visitado(n); int id;
   std::vector<int> tin(n, -1), low(n, -1);
   std::vector<std::pair<int, int>> res;
   for (int i = 0; i < n; ++i) {
      if (!visitado[i]) {
         dfs(i, -1, adyacencia, visitado, id, tin, low, res);
      }
   }
   return res;
}
