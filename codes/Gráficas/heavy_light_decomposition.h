/**
 * Nombre: Heavy-Light Decomposition
 * Autor: rcc
 * Descripción: Descomposición de un árbol con ejemplo de queries en el camino entre dos vértices
 * Complejidad: $O(n \log n)$ para procesar, $O(\log^2 n)$ por query
 * Estado: probado en omegaup.com/arena/problem/El-problema-de-asignacion
 * Uso:
 *   // calcula información para LCA y para descomposición HL
 *   calcula_stats(0, -1, adyacencia, datos, preorden_aumentado);
 *   // calcula información para LCA
 *   vector<int> primera_aparicion(n);
 *   vector<vector<int>> grupos = { { 0 } };
 *   // descomposición HL (cuidado con el reserve del ejemplo, ¡sí importa!)
 *   descomposicion_hl(0, -1, adyacencia, datos, grupos, grupos[0]);
 *   for (...) {
 *      // crear estructura de datos por arista después de la descomposición
 *      arbol_arista.push_back(stree_arista(grupos[i], adyacencia));
 *   }
 */
struct stats {
   int altura, peso;
};

void calcula_stats(int actual, int anterior, const vector<map<int, int>>& adyacencia, vector<stats>& datos, vector<int>& preorden_aumentado) {
   int altura = 0, peso = 0;
   preorden_aumentado.push_back(actual);
   for (auto [v, c] : adyacencia[actual]) {
      if (v == anterior) {
         continue;
      }
      calcula_stats(v, actual, adyacencia, datos, preorden_aumentado);
      altura = max(altura, datos[v].altura), peso += datos[v].peso;
      preorden_aumentado.push_back(actual);
   }
   datos[actual] = { altura + 1, peso + 1 };
}

void descomposicion_hl(int actual, int anterior, const vector<map<int, int>>& adyacencia, const vector<stats>& datos, vector<vector<int>>& grupos, vector<int>& trabajo) {
   for (auto [v, c] : adyacencia[actual]) {
      if (v == anterior) {
         continue;
      }
      if (2 * datos[v].peso >= datos[actual].peso) {
         trabajo.push_back(v);
         descomposicion_hl(v, actual, adyacencia, datos, grupos, trabajo);
      } else {
         vector<int> temp = { actual, v };
         descomposicion_hl(v, actual, adyacencia, datos, grupos, temp);
         grupos.push_back(move(temp));
      }
   }
}

auto stree_arista(const vector<int>& grupo, const vector<map<int, int>>& adyacencia) {
   vector<int> costos;
   for (int i = 0; i < grupo.size( ) - 1; ++i) {
      costos.push_back(adyacencia[grupo[i]].find(grupo[i + 1])->second);
   }
   return lazy_segment_tree(        // depende del problema, puede ser no-lazy
      move(costos),
      0,                            // neutro aditivo
      1,                            // neutro multiplicativo
      [](int v1, int v2) {          // query aditivo
         return v1 + v2;
      },
      [](int& v, int n, int u) {    // actualización multiplicativa
         v *= u;                    // cambiar si hay overflow
         return true;
      },
      [](int u1, int u2) {
         return u1 * u2;            // cambiar si hay overflow
      }
   );
}

struct identidad {                  // para aprovechar el lazy_segment_tree para implementar el LCA
   auto operator<=>(const identidad&) const = default;
};

void ejemplo( ) {
   // n = vértices, q = queries
   vector<map<int, int>> adyacencia(n);
   for (int i = 0; i < n - 1; ++i) {
      // costo c en la arista (x, y)
      adyacencia[x][y] = c;
      adyacencia[y][x] = c;
   }

   vector<stats> datos(n + 1, { -1, -1 });
   vector<int> preorden_aumentado;
   calcula_stats(0, -1, adyacencia, datos, preorden_aumentado);
   vector<int> primera_aparicion(n);
   for (int i = preorden_aumentado.size( ) - 1; i >= 0; --i) {
      primera_aparicion[preorden_aumentado[i]] = i;
   }
   auto arbol_lca = lazy_segment_tree(
      move(preorden_aumentado),
      n,
      identidad( ),
      [&](int i, int j) {
         return (datos[i].altura > datos[j].altura ? i : j);
      },
      [](int& v, int n, identidad) {
         return true;
      },
      [](identidad, identidad) {
         return identidad( );
      }
   );

   vector<vector<int>> grupos = { { 0 } };
   grupos.reserve(n), descomposicion_hl(0, -1, adyacencia, datos, grupos, grupos[0]);
   vector<pair<int, int>> invertido(n, { -1, -1 });
   vector<decltype(stree_arista(grupos[0], adyacencia))> arbol_arista;
   for (int i = 0; i < grupos.size( ); ++i) {
      for (int j = 1; j < grupos[i].size( ); ++j) {
         invertido[grupos[i][j]] = { i, j };
      }
      arbol_arista.push_back(stree_arista(grupos[i], adyacencia));
   }

   for (int i = 0; i < q; ++i) {
      // query de x a y, posiblemente con algún cambio c
      int res = 0, ancestro = lca.query(min(primera_aparicion[x], primera_aparicion[y]), max(primera_aparicion[x], primera_aparicion[y]) + 1);
      for (int hijo : { x, y }) {
         while (hijo != ancestro) {
            auto& arbol = arbol_arista[invertido[hijo].first];
            auto [tope, pos_tope] = (invertido[hijo].first == invertido[ancestro].first ? pair(ancestro, invertido[ancestro].second) : pair(grupos[invertido[hijo].first][0], 0));
            arbol.update_with(pos_tope, invertido[hijo].second, c);     // quitar si no hay cambios
            res += arbol.query(pos_tope, invertido[hijo].second);       // suponer query aditiva (ajustar si no, cuidar overflow)
            hijo = tope;
         }
      }
      cout << res << "\n";
   }
}
