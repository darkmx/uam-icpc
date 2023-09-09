#include <bit>             // sólo si se necesita min_prefix
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
      return query(i, i + 1);
   }

   T query(int i, int f) const {
      return query_until(f) - query_until(i);
   }

   T query_until(int f) const {
      T res = 0;
      for (; f != 0; f -= (f & -f)) {
         res += mem_[f];
      }
      return res;
   }

   int min_prefix(T v) const {            // calcula la cantidad mínima de elementos (comenzando por la izquierda) que se necesitan para lograr un acumulado >= v;
      int i = 0;                          // si es imposible lograr dicha suma, regresa .size( ) + 1
      for (int j = std::bit_floor(mem_.size( )); j > 0; j /= 2) {
         if (i + j < mem_.size( ) && mem_[i + j] <= v) {
            v -= mem_[i + j];
            i += j;
         }
      }
      return i + (v > 0);
   }

   void replace(int i, const T& v) {
      modify_add(i, v - operator[](i));
   }

   void modify_add(int i, const T& d) {
      for (i += 1; i < mem_.size( ); i += (i & -i)) {
         mem_[i] += d;
      }
   }

private:
   std::vector<T> mem_;
};

int main( ) {
   fenwick_tree<int> arbol(10);    // inicialmente todo en cero

   for (int i = 0; i < 10; ++i) {
      arbol.replace(i, i);
   }
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol[i] << "\n";
   }
   std::cout << "\n";

   std::cout << arbol.query(0, 10) << "\n";
   std::cout << arbol.query_until(10) << "\n";
   std::cout << arbol.query(8, 10) << "\n";
   std::cout << "\n";

   arbol.modify_add(0, +6);
   for (int i = 0; i < 10; ++i) {
      std::cout << i << ": " << arbol[i] << "\n";
   }
   std::cout << "\n";

   std::cout << arbol.query(0, 10) << "\n";
   std::cout << arbol.query_until(10) << "\n";
   std::cout << arbol.query(8, 10) << "\n";
   std::cout << "\n";

   for (int i = 0; i < 10; ++i) {
      std::cout << arbol.query_until(i + 1) << " ";
   }
   std::cout << "\n";
   for (int i = 0; i < 100; ++i) {
      std::cout << i << ": " << arbol.min_prefix(i) << "\n";
   }
}
