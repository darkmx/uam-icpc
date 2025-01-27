/**
 * Nombre: Permutaciones usando recursión
 * Autor: rcc
 * Descripción: Generación de permutaciones usando recursión.
 * Complejidad: $O(n!\cdot n)$
 */
#include <iostream>
#include <algorithm>

int n;
int arr[MAX]; // inicializar con { 0, 1, ..., n - 1 }

// llamada inicial: permutaciones(0)
void permutaciones(int i) {
   if (i == n) {
      for (int i = 0; i < n; ++i) {
         std::cout << arr[i] << " ";
      }
      std::cout << "\n";
   } else {
      for (int j = i; j < n; ++j) {
         std::swap(arr[i], arr[j]);
         permutaciones(i + 1);
         std::swap(arr[i], arr[j]);
      }
   }
}
