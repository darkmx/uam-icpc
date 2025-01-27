/**
 * Nombre: Trie
 * Autor: rcc
 * Descripción:  Árbol enraizado que mantiene un conjunto de cadenas. La función \textit{inserta}
 *               añade una cadena al trie, \textit{posicion} devuelve el nodo donde termina una cadena
 *               (o \textit{nullptr} si no existe), \textit{busca} verifica si una cadena completa está
 *               presente, y \textit{prefijo} comprueba si un prefijo dado existe en el trie.
 * Complejidad: $O(n)$
 */
#include <cstddef>
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
