#include <algorithm>
#include <iostream>
#include <numeric>

constexpr std::size_t factorial(std::size_t n)
{
   return (n == 0 ? 1 : n * factorial(n - 1));
}

template<typename T>
std::size_t indice(T ini, T fin)
{
   std::size_t n = fin - ini, r = factorial(n - 1), res = 0;
   for (T i = ini; i != fin; ++i) {
      res += r * std::count_if(i + 1, fin, [&](std::size_t v) { return v < *i; });
      if (fin - i - 1 != 0) {
         r /= fin - i - 1;
      }
   }

   return res;
}

template<typename T>
void permutacion(T ini, T fin, std::size_t indice)
{
   std::iota(ini, fin, std::size_t(0));

   std::size_t n = fin - ini, r = factorial(n - 1);
   for (T i = ini; i != fin; ++i) {
      std::size_t d = indice / r; indice %= r;
      std::rotate(i, i + d, i + d + 1);
      if (fin - i - 1 != 0) {
         r /= fin - i - 1;
      }
   }
}

int main( )
{
   constexpr int n = 5;
   constexpr int f = factorial(n);

   for (int i = 0; i < f; ++i) {
      int buffer[n];
      permutacion(buffer, buffer + n, i);
      int x = indice(buffer, buffer + n);

      std::cout << i << " vs " << x << ": ";
      for (int j = 0; j < n; ++j) {
         std::cout << buffer[j] << " ";
      }
      std::cout << "\n";
   }
}
