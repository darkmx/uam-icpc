/**
 * Nombre: Cadenas numéricas usando recursión
 * Autor: rcc
 * Descripción: Generación de cadenas numéricas usando recursión.
 * Complejidad: $O(10^n\cdot n)$
 */
#include <iostream>

int n;
int arr[MAX];

// llamada inicial: cadenas_numericas(0)
void cadenas_numericas(int i) {
   if (i == n) {
      for (int i = 0; i < n; ++i) {
         std::cout << arr[i] << " ";
      }
      std::cout << "\n";
   } else {
      for (int d = 0; d <= 9; ++d) {
         arr[i] = d;
         cadenas_numericas(i + 1);
      }
   }
}
