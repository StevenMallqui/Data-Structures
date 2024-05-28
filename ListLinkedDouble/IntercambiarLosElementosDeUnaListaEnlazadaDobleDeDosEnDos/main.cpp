
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "list_linked_double.h"
// Introduce más librerías si son necesarias
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
  // leer los datos de la entrada
  int N, elem; cin >> N;
  if (N == 0)
    return false;
  
  ListLinkedDouble l1;
  for(int i = 0; i < N; i++){
    cin >> elem;
    l1.push_back(elem);
  }

  l1.intercambiar();

  // escribir sol
  l1.display();

  return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}