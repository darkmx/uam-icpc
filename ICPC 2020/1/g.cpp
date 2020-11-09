#include <iostream>
#include <string>

int main( ) {
   int par[18];
   for (int i = 0; i < 18; ++i) {
      std::cin >> par[i];
   }

   int res = 0;
   for (int i = 0; i < 18; ++i) {
      std::string s;
      std::getline(std::cin >> std::ws, s);

      if (s == "hole in one") {
         res += 1;
      } else if (s == "condor") {
         res += par[i] - 4;
      } else if (s == "albatross") {
         res += par[i] - 3;
      } else if (s == "eagle") {
         res += par[i] - 2;
      } else if (s == "birdie") {
         res += par[i] - 1;
      } else if (s == "par") {
         res += par[i];
      } else if (s == "bogey") {
         res += par[i] + 1;
      } else if (s == "double bogey") {
         res += par[i] + 2;
      } else if (s == "triple bogey") {
         res += par[i] + 3;
      }
   }

   std::cout << res << "\n";
}
