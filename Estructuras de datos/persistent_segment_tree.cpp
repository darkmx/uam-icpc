#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <memory>
#include <utility>

template<typename T, typename F = const T&(*)(const T&, const T&)>
class persistent_segment_tree {
   struct nodo {
      T valor;
      nodo *izq, *der;
   };

public:
   template<typename I>
   persistent_segment_tree(T n, F f, I&& entrada, int t)
   : mem_(std::make_shared<std::deque<nodo>>( )), neutro_(std::move(n)), funcion_(std::move(f)), tam_(t), raiz_(replace(nullptr, 0, tam_, 0, tam_, entrada)) {
   }

   int size( ) const {
      return tam_;
   }

   const T& operator[](int i) const {
      const T* res;
      visit(i, i + 1, [&](const T& actual) {
         res = &actual;
      });
      return *res;
   }

   T query(int ini, int fin) const {
      T res = neutro_;
      visit(ini, fin, [&](const T& actual) {
         res = funcion_(res, actual);
      });
      return res;
   }

   persistent_segment_tree replace(int i, T v) {
      return { neutro_, funcion_, tam_, replace(raiz_, i, i + 1, 0, tam_, [&]( ) { return std::move(v); }), mem_ };
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      return visit(raiz_, ini, fin, 0, tam_, vis);
   }

private:
   persistent_segment_tree(T n, F f, int t, nodo* r, std::shared_ptr<std::deque<nodo>>& m)
   : mem_(m), neutro_(std::move(n)), funcion_(std::move(f)), raiz_(r), tam_(t) {
   }

   template<typename I>
   nodo* replace(nodo* p, int qi, int qf, int ini, int fin, I&& entrada) {
      if (ini == fin || qi >= qf) {
         return p;
      } else if (fin - ini == 1) {
         return crea(entrada( ));
      } else {
         int mitad = ini + (fin - ini) / 2, tam = fin - ini;
         auto izq = replace((p == nullptr ? nullptr : p->izq), qi, std::min(qf, mitad), ini, mitad, entrada);
         auto der = replace((p == nullptr ? nullptr : p->der), std::max(qi, mitad), qf, mitad, fin, entrada);
         return crea(funcion_(izq->valor, der->valor), izq, der);
      }
   }

   template<typename V>
   void visit(const nodo* p, int qi, int qf, int ini, int fin, V& vis) const {
      if (qi >= qf) {
         return;
      } else if (qi == ini && qf == fin) {
         vis(p->valor);
      } else {
         int mitad = ini + (fin - ini) / 2;
         visit(p->izq, qi, std::min(qf, mitad), ini, mitad, vis);
         visit(p->der, std::max(qi, mitad), qf, mitad, fin, vis);
      }
   }

   template<typename... P>
   nodo* crea(P&&... v) {
      return &*mem_->insert(mem_->end( ), nodo{std::forward<P>(v)...});
   }

   std::shared_ptr<std::deque<nodo>> mem_;
   T neutro_;
   F funcion_;
   int tam_;
   nodo* raiz_;
};

int main( ) {
   auto s1 = persistent_segment_tree(0, std::plus( ), [i = 0]( ) mutable {
      return i++;
   }, 50);
   auto s2 = s1.replace(13, 27);
   auto s3 = s2.replace(42, -14);

   auto imprime = [&](const auto& s) {
      for (int i = 0; i < s.size( ); ++i) {
         std::cout << s[i] << " ";
      }
      std::cout << "\n";
   };
   imprime(s1), imprime(s2), imprime(s3);

   int arr[s1.size( )];
   std::iota(arr, arr + s1.size( ), 0);
   for (int i = 0; i <= s1.size( ); ++i) {
      for (int f = i; f <= s1.size( ); ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s1.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   arr[13] = 27;
   for (int i = 0; i <= s2.size( ); ++i) {
      for (int f = i; f <= s2.size( ); ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s2.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   arr[42] = -14;
   for (int i = 0; i <= s3.size( ); ++i) {
      for (int f = i; f <= s3.size( ); ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s3.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   std::cout << ":)\n";
}
