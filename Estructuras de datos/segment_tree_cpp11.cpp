#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template<typename T, typename F = const T&(*)(const T&, const T&)>
class segment_tree {
public:
   segment_tree(T n, F f)
   : pisos_(1), neutro_(std::move(n)), funcion_(std::move(f)) {
   }

   int size( ) const {
      return pisos_[0].size( );
   }

   const T& operator[](int i) const {
      return pisos_[0][i];
   }

   void push_back(T v) {
      for (int p = 0;; ++p, pisos_.resize(std::max(p + 1, int(pisos_.size( ))))) {
         pisos_[p].push_back(std::move(v));
         if (pisos_[p].size( ) % 2 == 1) {
            break;
         }
         v = funcion_(*(pisos_[p].end( ) - 2), *(pisos_[p].end( ) - 1));
      }
   }

   void pop_back( ) {
      for (int p = 0;; ++p) {
         pisos_[p].pop_back( );
         if (pisos_[p].size( ) % 2 == 0) {
            break;
         }
      }
   }

   void replace(int i, T v) {
      for (int p = 0;; ++p, i /= 2) {
         pisos_[p][i] = std::move(v);
         if (i + (i % 2 == 0) == pisos_[p].size( )) {
            break;
         }
         v = funcion_(pisos_[p][i - i % 2], pisos_[p][i - i % 2 + 1]);
      }
   }

   T query(int ini, int fin) const {
      T res = neutro_;
      visit(ini, fin, [&](const T& actual) {
         res = funcion_(res, actual);
      });
      return res;
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      for (int p = 0; ini != fin; ++p, ini /= 2, fin /= 2) {
         if (ini % 2 == 1) {
            vis(pisos_[p][ini++]);
         }
         if (fin % 2 == 1) {
            vis(pisos_[p][--fin]);
         }
      }
   }

private:
   std::vector<std::vector<T>> pisos_;
   F funcion_;
   T neutro_;
};

template<typename T, typename F>
segment_tree<T, F> make_segment_tree(const T& v, F f) {
   return segment_tree<T, F>(v, f);
}

int main( ) {
   auto s = make_segment_tree(0, std::plus<int>( ));
   for (int i = 0; i < 50; ++i) {
      s.push_back(i);
   }
   std::cout << s.query(5, 10) << "\n";

   s.visit(5, 10, [&](int actual) {
      std::cout << actual << " ";
   });
}
