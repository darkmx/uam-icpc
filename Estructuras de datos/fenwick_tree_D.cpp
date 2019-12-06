#include <iostream>
#include <vector>

template<int D>
class fenwick_tree {
public:
   template<typename... T>
   fenwick_tree(int n, const T&... s)
   : mem_(n + 1, fenwick_tree<D - 1>(s...)) {
   }

   template<typename... T>
   void add(int i, const T&... s) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i].actualiza(s...);
      }
   }

   template<typename... T>
   int prefix(int i, const T&... s) {
      int res = 0;
      for (i += 1; i != 0; i -= (i & -i)) {
         res += mem_[i].cuenta(s...);
      }
      return res;
   }

private:
   std::vector<fenwick_tree<D - 1>> mem_;
};

template<>
class fenwick_tree<0> {
public:
   void actualiza(int v) {
      v_ += v;
   }

   int cuenta( ) {
      return v_;
   }

private:
   int v_ = 0;
};

int main( ) {
   prueba_1d: {
      fenwick_tree<1> arbol(10);
      arbol.actualiza(2, +1);
      arbol.actualiza(4, +1);

      for (int i = 0; i < 10; ++i) {
         std::cout << arbol.cuenta(i) << " ";
      }
      std::cout << "\n";
   }

   std::cout << "\n\n";

   prueba_2d: {
      fenwick_tree<2> arbol(10, 10);
      arbol.actualiza(2, 2, +1);
      arbol.actualiza(4, 4, +1);

      for (int i = 0; i < 10; ++i) {
         for (int j = 0; j < 10; ++j) {
            std::cout << arbol.cuenta(i, j) << " ";
         }
         std::cout << "\n";
      }
      std::cout << "\n";
   }
}
