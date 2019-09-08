#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template<typename T, typename F = const T&(*)(const T&, const T&)>
class segment_tree {
public:
   segment_tree(T n = { }, F f = { })
   : pisos_(1), neutro_(std::move(n)), funcion_(std::move(f)) {
   }

   int size( ) const {
      return pisos_[0].size( );
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
      for (int p = 0; p < pisos_.size( ); ++p) {
         pisos_[p].pop_back( );
         if (pisos_[p].size( ) % 2 == 0) {
            break;
         }
      }
   }

   void update(T v, int i) {
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
      visit_(ini, fin, pisos_.size( ) - 1, [&](const T* ini, const T* fin) {
         res = funcion_(res, std::accumulate(ini, fin, neutro_, funcion_));
      });
      return res;
   }

   template<typename V>
   void visit(int ini, int fin, V&& v) const {
      visit_(ini, fin, pisos_.size( ) - 1, v);
   }

private:
   template<typename V>
   void visit_(int ini, int fin, int p, V&& v) const {
      if (ini != fin) {
         int grupo = 1 << p, xi = ini / grupo + bool(ini % grupo), xf = fin / grupo;
         if (xi < xf && xf <= pisos_[p].size( )) {
            v(pisos_[p].data( ) + xi, pisos_[p].data( ) + xf);
            visit_(ini, xi * grupo, p - 1, v);
            visit_(xf * grupo, fin, p - 1, v);
         } else {
            visit_(ini, fin, p - 1, v);
         }
      }
   }

   std::vector<std::vector<T>> pisos_;
   F funcion_;
   T neutro_;
};

template<typename T, typename F>
segment_tree<T, F> make_segment_tree(T neutro, F f) {
   return segment_tree<T, F>(std::move(neutro), std::move(f));
}

int main( ) {
   segment_tree<int, std::plus<int>> s;
   for (int i = 0; i < 50; ++i) {
      s.push_back(i);
   }
   std::cout << s.query(5, 10) << "\n";

   std::vector<int> v;
   s.visit(5, 10, [&](const int* ini, const int* fin) {
      std::copy(ini, fin, std::back_inserter(v));
   });
   for (auto p : v) {
      std::cout << p << " ";
   }
}
