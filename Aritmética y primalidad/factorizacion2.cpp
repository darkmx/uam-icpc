// https://omegaup.com/arena/problem/Puertas-del-Tiempo#problems
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <math.h>
#include <stdint.h>

int64_t potencia(int64_t b, int64_t e, int64_t mod) {
    int64_t res = 1; b %= mod;
    while (e != 0) {
      if (e % 2 == 1) {
         res = (__int128_t(res) * b) % mod;
      }
      b = (__int128_t(b) * b) % mod;
      e /= 2;
    }
    return res;
}

bool primalidad_miller_rabin(int64_t n) {      // versión determinista: https://cp-algorithms.com/algebra/primality_tests.html
   if (n < 2) {
      return false;
   }

   int64_t d = n - 1, s = 0;
   while (d % 2 == 0) {
      d /= 2, s += 1;
   }
   auto compuesto_con = [&](int64_t a) {
      int64_t x = potencia(a, d, n);
      if (x == 1 || x == n - 1) {
         return false;
      }
      for (int64_t r = 1; r < s; ++r) {
         x = (__int128_t(x) * x) % n;
         if (x == n - 1) {
            return false;
         }
      }
      return true;
   };

   for (int64_t a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
      if (n == a) {
         return true;
      } else if (compuesto_con(a)) {
         return false;
      }
   }
   return true;
}

int64_t factor_pollard_rho(int64_t n, int64_t c) {
   int64_t x = 2, y = 2, k = 2;
   for (int64_t i = 2; ; ++i) {
      x = ((__int128_t(x) * x) % n) + c;
      if (x >= n)	{
         x -= n;
      }
      int64_t d = std::gcd(x - y, n);
      if (d != 1) {
         return d;
      }
      if (i == k) {
         y = x, k *= 2;
      }
   }
}

std::vector<int64_t> factoriza(int64_t n) {      // suposición: n >= 2
   std::vector<int64_t> factores;
   if (primalidad_miller_rabin(n)) {
      factores.push_back(n);
   } else {
      for (int64_t i = 2; ; i++) {
         auto checar = factor_pollard_rho(n, i);
         if (checar != n) {
            std::vector<int64_t> factores1 = factoriza(checar);
            std::vector<int64_t> factores2 = factoriza(n / checar);
            factores.insert(factores.end( ), factores1.begin( ), factores1.end( ));
            factores.insert(factores.end( ), factores2.begin( ), factores2.end( ));
            break;
         }
      }
   }
   return factores;
}

int main( ) {
   int t;
   std::cin >> t;

   for (int i = 0; i < t; ++i) {
      int64_t actual;
      std::cin >> actual;
      auto factores = factoriza(actual);
      std::sort(factores.begin( ), factores.end( ));
      for (auto f : factores) {
         std::cout << f << " ";
      }
      std::cout << "\n";
   }
}
