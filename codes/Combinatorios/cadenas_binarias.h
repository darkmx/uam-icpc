/**
 * Nombre: Cadenas binarias usando recursión
 * Autor: rcc
 * Descripción: Generación de cadenas binarias usando recursión.
 * Complejidad: $O(2^n\cdot n)$
 */
#include <iostream>

int n;
bool arr[MAX];

// llamada inicial: cadenas_binarias(0)
void cadenas_binarias(int i) {
   if (i == n) {
      for (int i = 0; i < n; ++i) {
         std::cout << arr[i];
      }
      std::cout << "\n";
   } else {
      arr[i] = false;
      cadenas_binarias(i + 1);
      arr[i] = true;
      cadenas_binarias(i + 1);
   }
}
