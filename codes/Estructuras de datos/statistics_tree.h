/**
 * Nombre: Árboles con estadísticas
 * Autor: GNU
 * Descripción: Implementación de árboles ordenados con índices a partir de 0 para sus nodos
 * Complejidad: $O(\log n)$
 * Uso:
 *  statistics_set<int> s;
 *  s.insert(3), s.insert(5), s.insert(7);
 *  std::cout << s.order_of_key(5) << "\n";    // índice dada la clave de búsqueda
 *  std::cout << *s.find_by_order(1) << "\n";  // iterador al nodo dado el índice
 */
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>  /// include-line
#include <ext/pb_ds/tree_policy.hpp>      /// include-line

namespace gnu = __gnu_pbds;

template<typename T>
using statistics_set = __gnu_pbds::tree<T, gnu::null_type, std::less<T>, gnu::rb_tree_tag, gnu::tree_order_statistics_node_update>;

template<typename T, typename V>
using statistics_map = __gnu_pbds::tree<T, V, std::less<T>, gnu::rb_tree_tag, gnu::tree_order_statistics_node_update>;
