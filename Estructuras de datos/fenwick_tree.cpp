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

   T operator[](int i) const {
      return prefix(i) - (i != 0 ? prefix(i - 1) : 0);
   }

   void add(int i, const T& d) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i] += d;
      }
   }

   void replace(int i, const T& v) {
      add(i, v - operator[](i));
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
      arbol.add(i, +1);
   }
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol[i] << " (" << arbol.prefix(i) << ")\n";
   }
   std::cout << "\n";

   arbol.replace(4, 5);
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol[i] << " (" << arbol.prefix(i) << ")\n";
   }
   std::cout << "\n";
}
