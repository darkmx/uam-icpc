#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

struct bipartito_hopcroft {
   std::vector<std::vector<int>> adyacencia;
   std::vector<int> match_b;

   bipartito_hopcroft(int n, int m)
   : adyacencia(n), match_b(m, -1) {
   }

   void agrega_arco(int i, int j) {
      adyacencia[i].push_back(j);
   }

   int calcula_acoplamiento( ) {
      for (;;) {
         std::vector<int> capas = calcula_capas( );
         bool mejora = false, visto_a[adyacencia.size( )] = { };
         for (int i = 0; i < adyacencia.size( ); ++i) {
            mejora |= (capas[i] == 0 && aumenta(i, visto_a, capas));
         }
         if (!mejora) {
            return match_b.size( ) - std::count(match_b.begin( ), match_b.end( ), -1);
         }
      }
   }

private:
   std::vector<int> calcula_capas( ) {
      std::vector<int> capas(adyacencia.size( ), 0);
      std::deque<int> cola(adyacencia.size( ));
      std::iota(cola.begin( ), cola.end( ), 0);
      for (int j = 0; j < match_b.size( ); ++j) {
         int i = match_b[j];
         if (i != -1) {
            cola[i] = capas[i] = -1;
         }
      }

      cola.erase(std::remove(cola.begin( ), cola.end( ), -1), cola.end( ));
      for (; !cola.empty( ); cola.pop_front( )) {
         int i = cola.front( );
         for (int j : adyacencia[i]) {
            if (match_b[j] != -1 && capas[match_b[j]] == -1) {
               capas[match_b[j]] = capas[i] + 1;
               cola.push_back(match_b[j]);
            }
         }
      }

      return capas;
   }

   bool aumenta(int i, bool visto_a[], const std::vector<int>& capas) {
      if (!visto_a[i]) {
         visto_a[i] = true;
         for (int j : adyacencia[i]) {
            if (match_b[j] == -1 || capas[i] + 1 == capas[match_b[j]] && aumenta(match_b[j], visto_a, capas)) {
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

   bipartito_hopcroft bp(n, n);
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
