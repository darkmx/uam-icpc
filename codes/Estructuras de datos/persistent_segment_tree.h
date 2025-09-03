/**
 * Nombre: Árbol de segmentos persistente
 * Autor: rcc
 * Descripción: Árbol de segmentos que permite consultar cualquier versión
 *              anterior del árbol después de cada modificación.
 * Complejidad: $O(\log n)$
 * Uso:
 *  auto s = persistent_segment_tree(std::move(vector_inicial), 0, std::plus( ));
 *  int suma1 = s.query(5, 10);
 *  auto s2 = s.replace(i, rand( ));
 *  int suma2 = s.query(5, 10);
 */
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <memory>
#include <utility>

template<typename T, typename F = const T&(*)(const T&, const T&)>
class persistent_segment_tree {
public:
   struct nodo {
      T valor;
      nodo *izq, *der;
   };

   persistent_segment_tree(std::vector<T>&& init, T v0, F f)
   : mem(std::make_shared<std::deque<nodo>>( )), neutro(std::move(v0)), funcion(std::move(f)), tam(init.size( )) {
      auto p = init.data( );
      raiz = replace(nullptr, 0, size( ), 0, size( ), [&]{
         return std::move(*p++);
      });
   }

   int size( ) const {
      return tam;
   }

   const nodo* root( ) const {
      return raiz;
   }

   const T& operator[](int i) const {
      const T* res;
      visit(i, i + 1, [&](const T& valor) {
         res = &valor;
      });
      return *res;
   }

   T query(int ini, int fin) const {
      T res = neutro;
      visit(ini, fin, [&](const T& valor) {
         res = funcion(res, valor);
      });
      return res;
   }

   persistent_segment_tree replace(int i, T v) {
      return { mem, neutro, funcion, size( ), replace(raiz, i, i + 1, 0, size( ), [&]{
         return std::move(v);
      }) };
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      return visit(raiz, ini, fin, 0, size( ), vis);
   }

private:
   persistent_segment_tree(std::shared_ptr<std::deque<nodo>>& m, T v0, F f, int t, nodo* r)
   : mem(m), neutro(std::move(v0)), funcion(std::move(f)), tam(t), raiz(r) {
   }

   template<typename I>
   nodo* replace(nodo* p, int qi, int qf, int ini, int fin, I&& entrada) {
      if (qi >= qf) {
         return p;
      } else if (fin - ini == 1) {
         return crea(entrada( ));
      } else {
         int mitad = ini + (fin - ini) / 2;
         auto izq = replace((p == nullptr ? nullptr : p->izq), qi, std::min(qf, mitad), ini, mitad, entrada);
         auto der = replace((p == nullptr ? nullptr : p->der), std::max(qi, mitad), qf, mitad, fin, entrada);
         return crea(funcion(izq->valor, der->valor), izq, der);
      }
   }

   template<typename V>
   void visit(const nodo* p, int qi, int qf, int ini, int fin, V& vis) const {
      if (qi == ini && qf == fin && ini != fin) {
         vis(p->valor);
      } else if (qi < qf) {
         int mitad = ini + (fin - ini) / 2;
         visit(p->izq, qi, std::min(qf, mitad), ini, mitad, vis);
         visit(p->der, std::max(qi, mitad), qf, mitad, fin, vis);
      }
   }

   template<typename... P>
   nodo* crea(P&&... v) {
      return &*mem->insert(mem->end( ), nodo{std::forward<P>(v)...});
   }

   std::shared_ptr<std::deque<nodo>> mem;
   T neutro;
   F funcion;
   int tam;
   nodo* raiz;
};

// < C++17 checar segment_tree
