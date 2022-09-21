#include <iostream>
#include <sstream>
#include <string>

int main( ) {
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
