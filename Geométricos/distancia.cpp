#include <cmath>
#include <iostream>
#include <utility>

template<typename T>
double distancia(const std::pair<T, T>& a, const std::pair<T, T>& b) {
   auto dx = a.first - b.first;
   auto dy = a.second - b.second;
   return std::sqrt(dx * dx + dy * dy);
}

int main( ) {
   std::cout << distancia<int>({ 0, 0 }, { 1, 1 }) << "\n";
}
