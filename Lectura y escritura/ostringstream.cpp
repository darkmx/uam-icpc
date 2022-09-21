#include <iostream>
#include <sstream>
#include <string>

int main( ) {
   int a = 57;
   char c = '@';
   double f = 3.14;

   std::ostringstream bufer;
   bufer << a << " " << c << " " << f;
   std::string cadena = bufer.str( );

   std::cout << cadena;
}
