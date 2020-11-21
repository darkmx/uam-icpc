#include <iostream>
#include <vector>

template<typename T>
class fenwick_tree {
public:
   fenwick_tree(int n)
   : mem_(n + 1) {
   }

   int size( ) const {
      return mem_.size( ) - 1;
   }

   T current(int i) {
      return prefix(i) - (i != 0 ? prefix(i - 1) : 0);
   }

   void replace(int i, const T& v) {
      advance(i, v - current(i));
   }

   void advance(int i, const T& d) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i] += d;
      }
   }

   T prefix(int i) const {
      T res = 0;
      for (i += 1; i != 0; i -= (i & -i)) {
         res += mem_[i];
      }
      return res;
   }

private:
   std::vector<T> mem_;
};

int main( ) {
   fenwick_tree<int> arbol(10);    // inicialmente todo en cero

   for (int i = 0; i < 10; ++i) {
      arbol.advance(i, +1);
   }
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol.current(i) << " (" << arbol.prefix(i) << ")\n";
   }
   std::cout << "\n";

   arbol.replace(4, 5);
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol.current(i) << " (" << arbol.prefix(i) << ")\n";
   }
   std::cout << "\n";
}
