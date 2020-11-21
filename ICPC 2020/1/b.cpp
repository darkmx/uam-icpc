#include <deque>
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

int personas_atras(const fenwick_tree<int>& ft, int pos) {
   return ft.prefix(pos - 1);
}

int personas_adelante(const fenwick_tree<int>& ft, int pos) {
   return ft.prefix(ft.size( ) - 1) - ft.prefix(pos);
}

int main( ) {
   int n;
   std::cin >> n;

   std::deque<int> por_estacion[100000 + 1];
   for (int i = 0; i < n; ++i) {
      int actual;
      std::cin >> actual;
      por_estacion[actual].push_back(i + 1);
   }

   fenwick_tree<int> izq(n + 2), opt(n + 2);
   for (int i = 0; i < n + 2; ++i) {
      izq.advance(i, (1 <= i && i <= n));
      opt.advance(i, (1 <= i && i <= n));
   }

   long long res1 = 0, res2 = 0;
   for (auto& estacion : por_estacion) {
      for (int pos : estacion) {
         res1 += personas_atras(izq, pos);
         izq.advance(pos, -1);
      }
      while (!estacion.empty( )) {
         int p1 = personas_atras(opt, estacion.front( ));
         int p2 = personas_adelante(opt, estacion.back( ));
         if (p1 <= p2) {
            res2 += p1;
            opt.advance(estacion.front( ), -1);
            estacion.pop_front( );
         } else {
            res2 += p2;
            opt.advance(estacion.back( ), -1);
            estacion.pop_back( );
         }
      }
   }

   std::cout << res1 << " " << res2 << "\n";
}
