#include <algorithm>
#include <iostream>
#include <vector>

void dfs(int actual, int anterior, const std::vector<int> adyacencia[], std::vector<bool>& visitado, int& id, std::vector<int>& tin, std::vector<int>& low, std::vector<std::pair<int, int>>& res) {
   visitado[actual] = true, tin[actual] = low[actual] = id++;
   for (int vecino : adyacencia[actual]) {
      if (vecino != anterior) {
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
      dfs(i, -1, adyacencia, visitado, id, tin, low, res);
   }
   return res;
}

int main( ) {
   int n, m;
   std::cin >> n >> m;

   std::vector<int> adyacencia[n];
   for (int i = 0; i < m; ++i) {
      int x, y;
      std::cin >> x >> y;
      adyacencia[x - 1].emplace_back(y - 1);
      adyacencia[y - 1].emplace_back(x - 1);
   }

   auto puentes = calcula_puentes(adyacencia, n);
   for (auto [x, y] : puentes) {
      std::cout << x << " " << y << "\n";
   }
}
