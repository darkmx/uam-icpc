#include <iostream>
#include <vector>

template<typename T, int D>
class fenwick_tree {
public:
   template<typename... P>
   fenwick_tree(int n, const P&... s)
   : mem_(n + 1, fenwick_tree<T, D - 1>(s...)) {
   }

   template<typename... P>
   void add(int i, const P&... s) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i].add(s...);
      }
   }

   template<typename... P>
   T prefix(int i, const P&... s) const {
      T res = 0;
      for (i += 1; i != 0; i -= (i & -i)) {
         res += mem_[i].prefix(s...);
      }
      return res;
   }

private:
   std::vector<fenwick_tree<T, D - 1>> mem_;
};

template<typename T>
class fenwick_tree<T, 0> {
public:
   T get( ) {
      return v_;
   }

   void add(const T& v) {
      v_ += v;
   }

   void replace(int i, const T& v) {
      v_ = v;
   }

   T prefix( ) const {
      return v_;
   }

private:
   T v_ = 0;
};

int main( ) {
   prueba_1d: {
      fenwick_tree<int, 1> arbol(10);
      arbol.add(2, +1);
      arbol.add(4, +1);
      for (int i = 0; i < 10; ++i) {
         std::cout << arbol.prefix(i) << " ";
      }
      std::cout << "\n";
   }

   std::cout << "\n\n";

   prueba_2d: {
      fenwick_tree<int, 2> arbol(10, 10);
      arbol.add(2, 2, +1);
      arbol.add(4, 4, +1);
      for (int i = 0; i < 10; ++i) {
         for (int j = 0; j < 10; ++j) {
            std::cout << arbol.prefix(i, j) << " ";
         }
         std::cout << "\n";
      }
      std::cout << "\n";
   }
}
