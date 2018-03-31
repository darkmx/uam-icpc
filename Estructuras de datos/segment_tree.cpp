#include <numeric>
#include <vector>

template<typename T, typename F>
class segment_tree {
public:
   segment_tree(F f = { })
   : pisos(1), funcion(f) {
   }

   int size( ) const {
      return pisos[0].size( );
   }

   void update(T v, int i) {
      for (int p = 0;; ++p, i /= 2) {
         pisos[p][i] = std::move(v);
         if (i + (i % 2 == 0) == pisos[p].size( )) {
            break;
         }
         v = funcion(pisos[p][i - i % 2], pisos[p][i - i % 2 + 1]);
      }
   }

   void push_back(T v) {
      for (int p = 0;; ++p, pisos.resize(std::max(p + 1, int(pisos.size( ))))) {
         pisos[p].push_back(std::move(v));
         if (pisos[p].size( ) % 2 == 1) {
            break;
         }
         v = funcion(*(pisos[p].end( ) - 2), *(pisos[p].end( ) - 1));
      }
   }

   T query(int ini, int fin, const T& v) const {
      return query(ini, fin, v, pisos.size( ) - 1);
   }

private:
   T query(int ini, int fin, const T& v, int p) const {
      if (ini == fin) {
         return v;
      } else {
         int grupo = 1 << p, xi = ini / grupo + bool(ini % grupo), xf = fin / grupo;
         if (xi < xf && xf <= pisos[p].size( )) {
            return funcion(std::accumulate(pisos[p].begin( ) + xi, pisos[p].begin( ) + xf, v, funcion), funcion(query(ini, xi * grupo, v, p - 1), query(xf * grupo, fin, v, p - 1)));
         } else {
            return query(ini, fin, v, p - 1);
         }
      }
   }

   std::vector<std::vector<T>> pisos;
   F funcion;
};

template<typename T, typename F>
segment_tree<T, F> make_segment_tree(F f = { }) {
   return segment_tree<T, F>(f);
}

int main( ) {
   auto s = make_segment_tree<int>(std::max<int>);
   for (int i = 0; i < 50; ++i) {
      s.push_back(i);
   }
}
