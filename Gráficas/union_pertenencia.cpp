#include <iostream>
#include <numeric>
#include <vector>

struct union_find {
   std::vector<int> repr;

   union_find(int n)
   : repr(n) {
      std::iota(repr.begin( ), repr.end( ), 0);
   }

   int leader(int i) {
      if (repr[i] != i) {
         repr[i] = leader(repr[i]);
      }
      return repr[i];
   }

   void join(int i, int j) {
      int ri = leader(i), rj = leader(j);
      if (ri != rj) {
         repr[ri] = rj;
      }
   }

   bool connected(int i, int j) {
      return leader(i) == leader(j);
   }
};

int main( ) {
   int n;
   std::cin >> n;

   union_find uf(n);
   int v1, v2;
   std::cin >> v1 >> v2;
   uf.join(v1, v2);
   std::cout << uf.connected(v1, v2);
}
