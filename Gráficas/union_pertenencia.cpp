#include <algorithm>
#include <iostream>
#include <vector>

struct union_find {
   std::vector<int> data;

   union_find(int n)
   : data(n, -1) {
   }

   int leader(int i) {
      return (data[i] < 0 ? i : data[i] = leader(data[i]));
   }

   int size(int i) {
      return -data[leader(i)];
   }

   bool connected(int i, int j) {
      return leader(i) == leader(j);
   }

   void join(int i, int j) {
      int ri = leader(i), rj = leader(j);
      if (ri != rj) {
        if (-data[ri] < -data[rj]) {
          std::swap(ri, rj);
        }
        data[ri] += data[rj];
        data[rj] = ri;
      }
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
