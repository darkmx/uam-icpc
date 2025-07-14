/**
 * Nombre: Ejemplo
 * Autor: gomita
 * Descripción: Estructuras y funciones de ejemplo que realmente no hacen
 *              nada. ¡Aquí se admiten comandos LaTeX! Como este $2^2=3$.
 * Complejidad: $O(M * N^4)$ donde $M$ = gatos, $N$ = ratones.
 * Memoria: $O(2^N)$ donde $N$ = gatos.
 * Uso:
 *  for (int i = 0; i < 10; i++) {
 *  \t cout << i << '\n'; // $\sum_{i=1}^{n} i = \frac{n(n+1)}{2}$
 *  \t\t cout << i*2 << '\n'; // \large LaTeX en comentarios!!
 *  }
 *  <-------------------------Ancho máximo------------------------->
 */

/// IMPORTANTE:
/// Para que el archivo sea visible, necesita tener, como mínimo:
/// Nombre, Autor y Descripción.
/// En "Uso:", no uses '@', '`', '#', '%',
/// ni llaves ('{', '}') sin cerrar en cadenas o comentarios.

// Usa una indentación de 3 espacios y mantén un ancho de línea
// máximo de 68 caracteres. La indentación de 3 espacios se
// convertirá en 2 espacios.
//<--------------------------Ancho máximo-------------------------->

/// Se añadirá la referencia y se quitará el include
#include "referencia.h"

struct EstructuraEjemplo {
   /// Se eliminará este comentario.
   long long costo; /// Este también

   /// Se eliminará el prefijo "std::" en todo el código
   std::pair<int, int> vertice;
   // Este comentario se mantendrá
   std::vector<int> aristas; // Este también
};

/// Las líneas de abajo no se incluirán.
const long long a = 5; /** exclude-line */
const long long b = 6; /// exclude-line

int funcion(int gatos, int ratones) {
   int suma = 0;
   // suma += gatos * ratones; /// include-line
   /// La línea de arriba pasará a ser la siguiente:
   suma += gatos * ratones;
   return suma;
}

/// Si se quita el include line, la funcion main() no se incluira
int main( ) { ///include-line
   std::cout << funcion(1, 2);
}
