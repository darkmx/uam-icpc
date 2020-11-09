#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int main( ) {
   std::ios_base::sync_with_stdio(false);
   std::cin.tie(nullptr), std::cout.tie(nullptr);

   int n, q;
   std::cin >> n >> q;

   std::pair<int, std::vector<std::pair<int, int>>> top = { };
   std::multimap<int, int> tops[n + 1];  // i -> (#, j)
   std::unordered_map<int, std::multimap<int, int>::iterator> tabla[n + 1];     // j -> i -> iter

   for (int i = 0; i < q; ++i) {
      char c;
      std::cin >> c;

      if (c == 'R') {
         int i, j, veces;
         std::cin >> i >> j;

         auto res = tabla[j].emplace(i, std::multimap<int, int>::iterator( ));
         if (res.second) {
            veces = 1;
         } else {
            veces = res.first->second->first + 1;
            tops[i].erase(res.first->second);
         }

         res.first->second = tops[i].emplace(veces, j);
         if (veces >= top.first) {
            if (veces > top.first) {
               top = { veces, { } };
            }
            top.second.emplace_back(i, j);
         }
      } else if (c == 'Q') {
         int i;
         std::cin >> i;

         if (tops[i].empty( )) {
            std::cout << "No info\n";
         } else {
            auto iter = std::prev(tops[i].end( ));
            if (tops[i].size( ) == 1 || iter->first != std::prev(iter)->first) {
               std::cout << iter->second << "\n";
            } else {
               std::cout << "Multiple\n";
            }
         }
      } else if (c == 'B') {
         if (top.second.empty( )) {
            std::cout << "No info\n";
         } else if (top.second.size( ) == 1) {
            std::cout << top.second.front( ).first << " " << top.second.front( ).second << "\n";
         } else {
            std::cout << "Multiple\n";
         }
      }
   }
}
