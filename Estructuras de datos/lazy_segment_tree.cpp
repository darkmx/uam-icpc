#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

template<typename T, typename U, typename F1 = const T&(*)(const T&, const T&), typename F2 = bool(*)(T&, int n, const U&), typename F3 = const U&(*)(const U&, const U&)>
class lazy_segment_tree {
   struct nodo {
      T valor;
      U lazy;
   };

public:
   template<typename I>
   lazy_segment_tree(T n1, U n2, F1 f1, F2 f2, F3 f3, I&& entrada, int t)
   : mem_(2 * t), neutro1_(std::move(n1)), neutro2_(std::move(n2)), funcion1_(std::move(f1)), funcion2_(std::move(f2)), funcion3_(std::move(f3)), tam_(t) {
      construye(0, 0, t, entrada);
   }

   template<typename RI>
   lazy_segment_tree(T n1, U n2, F1 f1, F2 f2, F3 f3, RI ini, RI fin)
   : lazy_segment_tree(std::move(n1), std::move(n2), std::move(f1), std::move(f2), std::move(f3), [&]( ) { return *ini++; }, fin - ini) {
   }

   int size( ) const {
      return tam_;
   }

   T operator[](int i) const {
      return query(i, i + 1);
   }

   T query(int ini, int fin) const {
      T res = neutro1_;
      visit(0, ini, fin, 0, tam_, [&](const nodo& actual, int tam) {
         res = funcion1_(res, actual.valor);
      });
      return res;
   }

   void modify_apply(int ini, int fin, const U& v) {
      visit(0, ini, fin, 0, tam_, [&](nodo& actual, int tam) {
         modifica(actual, tam, v);
      }, true);
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      visit(0, ini, fin, 0, tam_, [&](const nodo& actual, int tam) {
         vis(actual.valor);
      });
   }

private:
   void modifica(nodo& actual, int tam, const U& v) const {
      if (v != neutro2_ && funcion2_(actual.valor, tam, v)) {
         actual.lazy = (actual.lazy != neutro2_ ? funcion3_(actual.lazy, v) : v);
      }
   }

   template<typename I>
   void construye(int i, int ini, int fin, I& entrada) {
      if (ini == fin) {
         return;
      } else if (fin - ini == 1) {
         mem_[i] = { entrada( ), neutro2_ };
      } else {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         construye(izq, ini, mitad, entrada);
         construye(der, mitad, fin, entrada);
         mem_[i] = { funcion1_(mem_[izq].valor, mem_[der].valor), neutro2_ };
      }
   }

   template<typename V>
   void visit(int i, int qi, int qf, int ini, int fin, V&& vis, bool actualizar = false) const {
      if (qi >= qf) {
         return;
      } else if (qi == ini && qf == fin) {
         vis(mem_[i], fin - ini);
      } else {
         int tam = fin - ini, mitad = ini + tam / 2, izq = i + 1, der = i + 2 * (tam / 2);
         modifica(mem_[izq], tam / 2, mem_[i].lazy);
         modifica(mem_[der], tam - tam / 2, mem_[i].lazy);
         mem_[i].lazy = neutro2_;

         visit(izq, qi, std::min(qf, mitad), ini, mitad, vis, actualizar);
         visit(der, std::max(qi, mitad), qf, mitad, fin, vis, actualizar);
         if (actualizar) {
            mem_[i].valor = funcion1_(mem_[izq].valor, mem_[der].valor);
         }
      }
   }

   mutable std::vector<nodo> mem_;
   T neutro1_;
   U neutro2_;
   F1 funcion1_;
   F2 funcion2_;
   F3 funcion3_;
   int tam_;
};

// < C++17 checar segment_tree

#include <numeric>

int main( ) {
   auto imprime = [&](const auto& s) {
      for (int i = 0; i < s.size( ); ++i) {
         std::cout << s[i] << " ";
      }
      std::cout << "\n";
   };

   caso1: {    // query: suma, update: suma
      auto s = lazy_segment_tree(
         0,
         0,
         std::plus( ),
         [](int& a, int n, int b) { return a += n * b, true; },
         std::plus( ),
      [i = 0]( ) mutable {
         return i++;
      }, 50);
      imprime(s);

      std::cout << "original...\n";
      int arr[s.size( )];
      std::iota(arr, arr + s.size( ), 0);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (std::accumulate(arr + i, arr + f, 0) != s.query(i, f)) {
               std::cout << "X_X " << i << " " << f << "\n";
               return 0;
            }
         }
      }

      std::cout << "[0,50)...\n";
      std::for_each(arr, arr + 50, [](int& v) { v += 10; });
      s.modify_apply(0, 50, 10);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (std::accumulate(arr + i, arr + f, 0) != s.query(i, f)) {
               std::cout << "X_X " << i << " " << f << "\n";
               return 0;
            }
         }
      }

      std::cout << "[10,40)...\n";
      std::for_each(arr + 10, arr + 40, [](int& v) { v += 312; });
      s.modify_apply(10, 40, 312);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (std::accumulate(arr + i, arr + f, 0) != s.query(i, f)) {
               std::cout << "X_X\n";
               return 0;
            }
         }
      }

      std::cout << ":)\n";
   }

   caso2: {    // query: max, update: asignación
      auto s = lazy_segment_tree(
         INT_MIN,
         std::optional<int>( ),
         std::max,
         [](int& a, int n, std::optional<int> b) { return a = *b, true; },
         [](std::optional<int> a, std::optional<int> b) { return b; },
      [i = 0]( ) mutable {
         return i++;
      }, 50);
      imprime(s);

      std::cout << "original...\n";
      int arr[s.size( )];
      std::iota(arr, arr + s.size( ), 0);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (i != f && *std::max_element(arr + i, arr + f) != s.query(i, f)) {
               std::cout << "X_X " << i << " " << f << "\n";
               return 0;
            }
         }
      }

      std::cout << "[0,50)...\n";
      std::for_each(arr, arr + 50, [](int& v) { v = 10; });
      s.modify_apply(0, 50, 10);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (i != f && *std::max_element(arr + i, arr + f) != s.query(i, f)) {
               std::cout << "X_X " << i << " " << f << "\n";
               return 0;
            }
         }
      }

      std::cout << "[10,40)...\n";
      std::for_each(arr + 10, arr + 40, [](int& v) { v = 312; });
      s.modify_apply(10, 40, 312);
      for (int i = 0; i <= s.size( ); ++i) {
         for (int f = i; f <= s.size( ); ++f) {
            if (i != f && *std::max_element(arr + i, arr + f) != s.query(i, f)) {
               std::cout << "X_X " << i << " " << f << "\n";
               return 0;
            }
         }
      }

      std::cout << ":)\n";
   }
}
