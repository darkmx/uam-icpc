// https://codeforces.com/gym/102890/problem/K
#include <algorithm>
#include <iostream>

long long factorial[2000000 + 1];
long long primo = 1000000007;

long long inverso(int n) {
   if (primo == 1) {
      return 0;
   }

   long long m = primo, y = 0, x = 1;
   while (n > 1) {
      int q = n / m, t = m;
      m = n % m;
      n = t;
      t = y;
      y = x - q * y;
      x = t;
   }
   return (x + primo) % primo;
}

long long binomial(int n, int k){
    return (((factorial[n] * inverso(factorial[k])) % primo) * inverso(factorial[n - k])) % primo;
}

unsigned long long resuelve(int a, int b, int n) {
   unsigned long long res;
   if (a < n && b < n) {
      res = binomial(a + b, n);
   } else if (a < n || b < n) {
      res = binomial(a + b, n) + primo - binomial(std::max(a, b), n);
   } else {
      res = binomial(a + b, n) + 2 * primo - binomial(a, n) - binomial(b, n);
   }
   return res % primo;
}

int main( ) {
   for (int i = 0; i <= 2000000; ++i) {
      factorial[i] = (i == 0 ? 1 : (i * factorial[i - 1]) % primo);
   }

   int n;
   std::cin >> n;
   for (int i = 0; i < n; ++i) {
      int a, b, c, k, cs;
      std::cin >> a >> b >> c >> k >> cs;
      std::cout << (k < cs || k - cs < 2 || a + b < k - cs ? 0 : (binomial(c, cs) * resuelve(a, b, k - cs)) % primo) << "\n";
   }
}
