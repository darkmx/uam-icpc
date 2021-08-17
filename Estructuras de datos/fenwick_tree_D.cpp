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
   void modify_add(int i, const P&... s) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i].modify_add(s...);
      }
   }

   template<typename... P>
   T prefix_until(int f, const P&... s) const {
      T res = 0;
      for (; f != 0; f -= (f & -f)) {
         res += mem_[f].prefix_until(s...);
      }
      return res;
   }

private:
   std::vector<fenwick_tree<T, D - 1>> mem_;
};

template<typename T>
class fenwick_tree<T, 0> {
public:
   void modify_add(const T& d) {
      v_ += d;
   }

   T prefix_until( ) const {
      return v_;
   }

private:
   T v_ = 0;
};

int main( ) {
   prueba_1d: {
      fenwick_tree<int, 1> arbol(10);
      arbol.modify_add(2, +1);
      arbol.modify_add(4, 1);
      for (int i = 0; i < 10; ++i) {
         std::cout << arbol.prefix_until(i + 1) << " ";
      }
      std::cout << "\n";
   }

   std::cout << "\n\n";

   prueba_2d: {
      fenwick_tree<int, 2> arbol(10, 10);
      arbol.modify_add(2, 2, 1);
      arbol.modify_add(4, 4, 1);
      for (int i = 0; i < 10; ++i) {
         for (int j = 0; j < 10; ++j) {
            std::cout << arbol.prefix_until(i + 1, j + 1) << " ";
         }
         std::cout << "\n";
      }
      std::cout << "\n";
   }
}
