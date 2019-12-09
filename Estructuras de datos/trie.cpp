#include <cstddef>
#include <iostream>
#include <map>
#include <string>

class trie {
public:
   bool inserta(const std::string& s) {
      auto actual = this;
      for (int i = 0; i < s.size( ); ++i) {
         auto& siguiente = actual->nivel_[s[i]];
         if (siguiente == nullptr) {
            siguiente = new trie;
         }
         actual = siguiente;
      }
      return actual->nivel_.emplace('\0', nullptr).second;
   }

   trie* posicion(const std::string& s) {
      auto actual = this;
      for (int i = 0; i < s.size( ); ++i) {
         auto iter = actual->nivel_.find(s[i]);
         if (iter == actual->nivel_.end( )) {
            return nullptr;
         }
         actual = iter->second;
      }
      return actual;
   }

   bool busca(const std::string& s) {
      auto pos = posicion(s);
      return pos != nullptr && pos->nivel_.find('\0') != pos->nivel_.end( );
   }

   bool prefijo(const std::string& s) {
      auto pos = posicion(s);
      return pos != nullptr;
   }

private:
   std::map<char, trie*> nivel_;
};

int main( ) {
   trie t;

   t.inserta("perro");
   t.inserta("paco");
   t.inserta("casa");

   std::cout << t.prefijo("p") << '\n';
   std::cout << t.prefijo("pe") << '\n';
   std::cout << t.prefijo("perro") << '\n';
   std::cout << t.busca("gato") << '\n';
   std::cout << t.busca("p") << '\n';
   std::cout << t.busca("perro") << '\n';
}
