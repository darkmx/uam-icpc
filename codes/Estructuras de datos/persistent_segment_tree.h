/**
 * Nombre: Árbol de segmentos persistente
 * Autor: rcc
 * Descripción: Árbol de segmentos que permite consultar cualquier versión
 *              anterior del árbol después de cada modificación.
 * Complejidad: $O(\log n)$
 * Estado: probado en https://www.spoj.com/problems/MKTHNUM/
 * Uso:
 *  auto s = persistent_segment_tree(std::move(vector_inicial), assoc_op(0, std::plus( )));
 *  int suma1 = s.query(5, 10);
 *  auto s2 = s.replace(i, rand( ));
 *  int suma2 = s.query(5, 10);
 */
#include "segment_tree.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <memory>
#include <utility>
#include <vector>

template<typename OP>
class persistent_segment_tree {
public:
   const OP op;
   using T = decltype(OP::neutro);

   struct nodo {
      T valor;
      nodo *izq, *der;
   };

   persistent_segment_tree(std::vector<T>&& v, OP p)
   : mem(std::make_shared<std::deque<nodo>>( )), op(std::move(p)), tam(v.size( )) {
      auto ini = v.data( );
      raiz = replace(nullptr, 0, size( ), 0, size( ), [&]{
         return std::move(*ini++);
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
      T res = op.neutro;
      visit(ini, fin, [&](const T& valor) {
         res = op.funcion(res, valor);
      });
      return res;
   }

   persistent_segment_tree replace(int i, T v) {
      return { mem, op, size( ), replace(raiz, i, i + 1, 0, size( ), [&]{
         return std::move(v);
      }) };
   }

   template<typename V>
   void visit(int ini, int fin, V&& vis) const {
      return visit(raiz, ini, fin, 0, size( ), vis);
   }

private:
   persistent_segment_tree(std::shared_ptr<std::deque<nodo>>& m, OP p, int t, nodo* r)
   : mem(m), op(std::move(p)), tam(t), raiz(r) {
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
         return crea(op.funcion(izq->valor, der->valor), izq, der);
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
   int tam;
   nodo* raiz;
};

// < C++17 checar segment_tree
