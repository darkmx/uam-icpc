/**
 * Nombre: Construcción de cadenas
 * Autor: rcc
 * Descripción: Ejemplo de concatenación de valores de diferentes tipos de datos en una sola cadena.
 */
#include <iostream>
#include <sstream>
#include <string>

int main( ) { ///include-line
   int a = 57;
   char c = '@';
   double f = 3.14;

   std::ostringstream bufer;
   bufer << a << " " << c << " " << f;
   std::string cadena = bufer.str( );

   std::cout << cadena;
}
