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
   persistent_segment_tree(T n, F f, int t, I&& entrada)
   : mem_(std::make_shared<std::deque<nodo>>( )), neutro_(std::move(n)), funcion_(std::move(f)), tam_(t), raiz_(construye(0, t, entrada)) {
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
      return { mem_, neutro_, funcion_, tam_, replace(raiz_, i, 0, tam_, std::move(v)) };
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      return visit(raiz_, ini, fin, 0, tam_, vis);
   }

private:
   persistent_segment_tree(std::shared_ptr<std::deque<nodo>>& m, T n, F f, int t, nodo* r)
   : mem_(m), neutro_(std::move(n)), funcion_(std::move(f)), tam_(t), raiz_(r) {
   }

   template<typename I>
   nodo* construye(int ini, int fin, I& entrada) {
      if (ini == fin) {
         return nullptr;
      } else if (fin - ini == 1) {
         return crea(entrada( ));
      } else {
         int mitad = ini + (fin - ini) / 2;
         auto izq = construye(ini, mitad, entrada), der = construye(mitad, fin, entrada);
         return crea(funcion_(izq->valor, der->valor), izq, der);
      }
   }

   nodo* replace(nodo* p, int i, int ini, int fin, T&& v) {
      if (ini == fin) {
         return nullptr;
      } else if (fin - ini == 1) {
         return crea(std::move(v));
      } else {
         int mitad = ini + (fin - ini) / 2, tam = fin - ini;
         auto izq = p->izq, der = p->der;
         if (i < tam / 2) {
            izq = replace(p->izq, i, ini, mitad, std::move(v));
         } else {
            der = replace(p->der, i - tam / 2, mitad, fin, std::move(v));
         }
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
      mem_->push_back(nodo{std::forward<P>(v)...});
      return &mem_->back( );
   }

   std::shared_ptr<std::deque<nodo>> mem_;
   T neutro_;
   F funcion_;
   int tam_;
   nodo* raiz_;
};

int main( ) {
   auto s1 = persistent_segment_tree(0, std::plus( ), 50, [i = 0]( ) mutable {
      return i++;
   });
   auto s2 = s1.replace(13, 27);
   auto s3 = s2.replace(42, -14);

   auto imprime = [&](const auto& s) {
      for (int i = 0; i < s.size( ); ++i) {
         std::cout << s1[i] << " ";
      }
      std::cout << "\n";
   };
   imprime(s1), imprime(s2), imprime(s3);

   int arr[50];
   std::iota(arr, arr + 50, 0);
   for (int i = 0; i <= 50; ++i) {
      for (int f = i; f <= 50; ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s1.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   arr[13] = 27;
   for (int i = 0; i <= 50; ++i) {
      for (int f = i; f <= 50; ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s2.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   arr[42] = -14;
   for (int i = 0; i <= 50; ++i) {
      for (int f = i; f <= 50; ++f) {
         if (std::accumulate(arr + i, arr + f, 0) != s3.query(i, f)) {
            std::cout << "X_X\n";
         }
      }
   }

   std::cout << ":)\n";
}
