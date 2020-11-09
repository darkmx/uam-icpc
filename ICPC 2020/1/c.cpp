#include <iostream>
#include <map>
#include <string>
#include <vector>

int agrega_palabra(const std::string& s, std::map<std::string, int>& por_palabra, std::vector<std::string>& por_id) {
   auto [iter, insertado] = por_palabra.emplace(s, por_id.size( ));
   if (insertado) {
      por_id.push_back(s);
   }
   return iter->second;
}

int main( ) {
   int n;
   std::cin >> n;

   std::map<std::string, int> por_palabra;
   std::vector<std::string> por_id;
   std::vector<int> adyacencia[2 * n];

   for (int i = 0; i < n; ++i) {
      std::string a, b;
      std::cin >> a >> b;
      int id1 = agrega_palabra(a, por_palabra, por_id);
      int id2 = agrega_palabra(b, por_palabra, por_id);
      adyacencia[id1].push_back(id2);
      adyacencia[id2].push_back(id1);
   }

   std::string* representante[por_id.size( )] = { };
   for (int i = 0; i < por_id.size( ); ++i) {
      if (representante[i] != nullptr) {
         continue;
      }

      representante[i] = new std::string(por_id[i]);
      std::vector<int> visitar = { i };
      do {
         int actual = visitar.back( );
         visitar.pop_back( );
         for (int vecino : adyacencia[actual]) {
            if (representante[vecino] == nullptr) {
               representante[vecino] = representante[i];
               *representante[i] = std::min(*representante[i], por_id[vecino], [](const std::string& a, const std::string& b) {
                  return (a.size( ) != b.size( ) ? a.size( ) < b.size( ) : a < b);
               });
               visitar.push_back(vecino);
            }
         }
      } while (!visitar.empty( ));
   }

   std::string actual;
   while (std::cin >> actual) {
      auto iter = por_palabra.find(actual);
      if (iter == por_palabra.end( )) {
         std::cout << actual << " ";
      } else {
         std::cout << *representante[iter->second] << " ";
      }
   }
}
