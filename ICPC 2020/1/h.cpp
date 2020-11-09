#include <iostream>

int main( ) {
   int t;
   std::cin >> t;

   for (int ti = 0; ti < t; ++ti) {
      int n;
      std::cin >> n;

      int arr[n];
      for (int i = 0; i < n; ++i) {
         std::cin >> arr[i];
      }

      int memoria[n + 2];
      for (int i = n + 1; i >= 0; --i) {
         if (i >= n) {
            memoria[i] = 0;
         } else {
            memoria[i] = std::max(arr[i] + memoria[i + 2], memoria[i + 1]);
         }
      }

      std::cout << memoria[0] << "\n";
   }
}
