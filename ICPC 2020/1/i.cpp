#include <algorithm>
#include <iostream>
#include <string>
#include <ctype.h>

bool valida_mayus(const std::string& s) {
   return std::any_of(s.begin( ), s.end( ), isupper);
}

bool valida_minus(const std::string& s) {
   return std::any_of(s.begin( ), s.end( ), islower);
}

bool valida_digit(const std::string& s) {
   int veces = 0;
   for (auto it = s.begin( ); (it = std::find_if(it, s.end( ), isdigit)) != s.end( ); ++it, ++veces) {
      if (isdigit(*(it + 1)) && std::abs(*it - *(it + 1)) == 1) {
         return false;
      }
   }
   return veces > 0;
}

bool valida_punct(const std::string& s) {
   return s.find_first_of(".#$%/(&)") != std::string::npos;
}

bool valida_tam(const std::string& s) {
   return s.size( ) >= 10;
}

int main( ) {
   int t;
   std::cin >> t;

   for (int ti = 1; ti <= t; ++ti) {
      std::string s;
      std::cin >> s;
      int res = valida_mayus(s) + valida_minus(s) + valida_digit(s) + valida_punct(s) + valida_tam(s);
      std::cout << "Assertion number #" << ti << ": " << (res == 5 ? "Strong" : (res == 4 ? "Good" : (res == 3 ? "Weak" : "Rejected"))) << "\n";
   }
}
