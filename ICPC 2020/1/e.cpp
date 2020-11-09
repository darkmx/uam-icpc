#include <algorithm>
#include <iostream>
#include <string>
#include <limits.h>

template<typename FI>
int entero(FI ini, FI fin) {
   int res = 0;
   for (auto i = ini; i != fin; ++i) {
      res *= 10;
      res += (*i - '0');
   }
   return res;
}

int main( ) {
   bool compuesto[1000000] = { true, true };
   for (std::size_t i = 2; i < 1000000; ++i) {
      if (!compuesto[i]) {
         for (std::size_t j = i * i; j < 1000000; j += i) {
            compuesto[j] = true;
         }
      }
   }

   std::string s;
   std::cin >> s;
   std::sort(s.begin( ), s.end( ));

   int res = INT_MAX;
   do {
      for (int t1 = 1; t1 <= s.size( ) - 2; ++t1) {
         for (int t2 = 1; t2 <= s.size( ) - 1 - t1; ++t2) {
            if (s[0] != '0' && s[t1] != '0' && s[t1 + t2] != '0') {
               int n1 = entero(s.begin( ), s.begin( ) + t1);
               int n2 = entero(s.begin( ) + t1, s.begin( ) + t1 + t2);
               int n3 = entero(s.begin( ) + t1 + t2, s.end( ));
               if (!compuesto[n1] && !compuesto[n2] && !compuesto[n3]) {
                  res = std::min(res, n1 * n2 * n3);
               }
            }
         }
      }
   } while (std::next_permutation(s.begin( ), s.end( )));

   if (res == INT_MAX) {
      std::cout << "Bob lies\n";
   } else {
      std::cout << res << "\n";
   }
}
