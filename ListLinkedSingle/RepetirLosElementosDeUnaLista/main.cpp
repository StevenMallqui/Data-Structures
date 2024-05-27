#include <iostream>
#include <fstream>
#include "list_linked_single.h"
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
  // leer los datos de la entrada
  int N, elem; cin >> N;
  ListLinkedSingle<int> xs, ys;
  for(int i = 0; i < N; i++){
    cin >> elem;
    xs.push_front(elem);
  }

  for(int i = 0; i < N; i++){
    cin >> elem;
    ys.push_front(elem);
  }

  xs.replicate(ys);
  // escribir solución
  xs.display();
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}