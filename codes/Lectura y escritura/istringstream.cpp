/**
 * Nombre: Tokenización de líneas
 * Autor: rcc
 * Descripción: Ejemplo de tokenización de líneas de texto, donde cada línea leída se divide en palabras que se imprimen individualmente.
 */
#include <iostream>
#include <sstream>
#include <string>

int main( ) { ///include-line
   std::string linea;
   while (std::getline(std::cin, linea)) {
      std::istringstream extractor(linea);
      std::string palabra;
      while (extractor >> palabra) {
         std::cout << palabra << " ";
      }
      std::cout << "\n";
   }
}
