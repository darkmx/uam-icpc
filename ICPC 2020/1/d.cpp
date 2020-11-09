#include <algorithm>
#include <iostream>

int main( ) {
   int n;
   std::cin >> n;

   int arr[n + 1] = { }, *iter[n + 1] = { arr };
   for (int i = 1; i <= n; ++i) {
      std::cin >> arr[i];
      iter[i] = &arr[i];
   }

   std::sort(iter, iter + n + 1, [](int* p1, int* p2) {
      return *p1 < *p2;
   });
   for (int i = 1; i <= n; ++i) {
      *iter[i] = i;
   }

   int res = 0;
   auto ini = arr, fin = arr + n + 1;
   for (int i = 1; i <= n && ini != fin; ++i) {
      auto iter = std::find(ini, fin, i);
      res += (iter - ini - 1);
      ini = iter;
   }

   std::cout << res << "\n";
}
