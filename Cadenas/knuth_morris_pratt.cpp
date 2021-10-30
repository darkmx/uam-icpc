#include <iostream>
#include <string>
#include <vector>
#include <stddef.h>

std::vector<size_t> preprocesa(const std::string& s) {
   std::vector<size_t> b = { size_t(-1) };
   for (size_t i = 0, j = -1; i < s.size( ); ++i) {
      while (j != -1 && s[i] != s[j]) {
         j = b[j];
      }
      b.push_back(++j);
   }
   return b;
}

std::vector<size_t> busca(const std::string& s, const std::string& t, const std::vector<size_t>& b) {
   std::vector<size_t> res;
   for (size_t i = 0, j = 0; i < t.size( ); ++i) {
      while (j != -1 && t[i] != s[j]) {
         j = b[j];
      }
      if (++j == s.size( )) {
         res.push_back(i + 1 - s.size( ));
         j = b[j];
      }
   }
   return res;
}

int main( ) {
   std::string t = "abbabaabababaaabaaababbaaaababbabaaaba";
   std::string s = "bbaaaababba";

   auto pre = preprocesa(s);
   auto res = busca(s, t, pre);
   std::cout << res.size( ) << "\n";
   for (int pos : res) {
      std::cout << pos << " ";
   }
}
