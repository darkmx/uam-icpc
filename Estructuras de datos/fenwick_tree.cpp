#include <iostream>
#include <vector>

class fenwick_tree {
public:
   fenwick_tree(int n)
   : mem_(n + 1) {
   }

   void add(int i, int d) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i] += d;
      }
   }

   int prefix(int i) {
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
   fenwick_tree arbol(10);    // inicialmente todo en cero

   for (int i = 0; i < 10; ++i) {
      arbol.add(i, +1);
   }
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol.prefix(i) << "\n";
   }
}
