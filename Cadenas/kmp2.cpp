#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<int> preprocesa(const std::string& p)
{
   std::vector<int> b(p.size( ) + 1, -1);

   for (int i = 1, j = -1; i <= p.size( ); ++i) {
      while (j >= 0 && p[j] != p[i - 1]) {
         j = b[j];
      }

      b[i] = ++j;
   }

   return b;
}

int kmp(const std::string& t, const std::string& p, const std::vector<int>& b)
{
   for (int i = 0, j = 0; i < t.size( ); ++i) {
      while (j >= 0 && p[j] != t[i]) {
         j = b[j];
      }

      if (++j == p.size( )) {
         return i + 1 - p.size( );
      }
   }

   return std::string::npos;
}

int main( )
{
   std::mt19937 gen(std::time(0));

   for (int i = 0; i < 100; ++i) {
      std::cerr << "ronda " << i << "...\n";

      int n = 100;
      std::uniform_int_distribution<int> dist1(0, 1);
      std::uniform_int_distribution<int> dist2(1, n - 1);
      int m = dist2(gen);

      std::string s;
      for (int i = 0; i < n; ++i) {
         s.push_back(dist1(gen) + '0');
      }

      /*std::string r;
      for (int i = 0; i < m; ++i) {
         r.push_back(dist1(gen) + '0');
      }

      for (int i = 0; i < n; ++i) {
         for (int x = 0; x < n; ++x) {
            for (int y = x + 1; y < n; ++y) {
               auto p = s.substr(x, y - x);
               if (kmp(s, p, preprocesa(p)) != s.find(p)) {
                  std::cerr << ":( " << x << ' ' << y << '\n';
                  std::cerr << s << ' ' << p << ": " << kmp(s, p, preprocesa(p)) << ' ' << s.find(p) << '\n';
               }
            }
         }
      }*/

      for (int i = 0; i < 10000; ++i) {
         std::string r;
         for (int i = 0; i < m; ++i) {
            r.push_back(dist1(gen) + '0');
         }

         if (kmp(s, r, preprocesa(r)) != s.find(r)) {
            std::cerr << ":( r\n";
            std::cerr << s << ' ' << r << ": " << kmp(s, r, preprocesa(r)) << ' ' << s.find(r) << '\n';
            std::exit(0);
         }
      }
   }
}
