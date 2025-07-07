#include <algorithm>
#include <iostream>
#include <vector>

struct bipartito_kuhn {
   std::vector<std::vector<int>> adyacencia;
   std::vector<int> match_b;

   bipartito_kuhn(int n, int m)
   : adyacencia(n), match_b(m, -1) {
   }

   void agrega_arco(int i, int j) {
      adyacencia[i].push_back(j);
   }

   int calcula_acoplamiento( ) {   // sólo llamar una vez
      int res = 0;
      for (int i = 0; i < adyacencia.size( ); ++i) {
         bool visto_a[adyacencia.size( )] = { };
         res += aumenta(i, visto_a);
      }
      return res;
   }

private:
   bool aumenta(int i, bool visto_a[]) {
      if (!visto_a[i]) {
         visto_a[i] = true;
         for (int j : adyacencia[i]) {
            if (match_b[j] == -1 || aumenta(match_b[j], visto_a)) {
               match_b[j] = i;
               return true;
            }
         }
      }
      return false;
   }
};

int main( ) {
   int n, p, k;
   std::cin >> n >> p >> k;

   std::pair<int, int> intervalo[n];
   std::fill(intervalo, intervalo + n, std::make_pair(0, n - 1));
   for (int i = 0; i < p; ++i) {
      for (int j = 0; j < n; ++j) {
         int actual;
         std::cin >> actual;
         intervalo[actual] = { std::max(intervalo[actual].first, j - k), std::min(intervalo[actual].second, j + k) };
      }
   }

   bipartito_kuhn bp(n, n);
   for (int i = 0; i < n; ++i) {
      for (int j = intervalo[i].first; j <= intervalo[i].second; ++j) {
         bp.agrega_arco(i, j);
      }
   }

   int res = bp.calcula_acoplamiento( );
   if (res == n) {
      for (int i = 0; i < n; ++i) {
         std::cout << bp.match_b[i] << " ";
      }
   } else {
      std::cout << -1 << "\n";
   }
}
