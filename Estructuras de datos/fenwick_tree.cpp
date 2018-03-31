#include <iostream>
#include <vector>

class fenwick_tree {
public:
   fenwick_tree(int n)
   : mem_(n + 1) {
   }

   void actualiza(int i, int v) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i] += v;
      }
   }

   int cuenta(int i) {
      int res = 0;
      for (i += 1; i != 0; i -= (i & -i)) {
         res += mem_[i];
      }
      return res;
   }

private:
   std::vector<int> mem_;
};

int main( ) {
   fenwick_tree arbol(10);

   for (int i = 0; i < 10; ++i) {
      arbol.actualiza(i, +1);
   }
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol.cuenta(i) << "\n";
   }
}
