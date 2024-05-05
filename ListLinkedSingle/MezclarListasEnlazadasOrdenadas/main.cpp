
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "list_linked_single.h"
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
ListLinkedSingle<int> resolver(ListLinkedSingle<int> l1, ListLinkedSingle<int> l2) {
  return l1.mix(l2);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
  
  // leer los datos de la entrada
  int elem; cin >> elem;
  ListLinkedSingle<int> l1, l2;
  
  while(elem != 0){
    l1.push_back(elem);
    cin >> elem;
  }

  cin >> elem;
  while(elem != 0){
    l2.push_back(elem);
    cin >> elem;
  }

  ListLinkedSingle<int> sol = resolver(l1, l2);
  // escribir solución
  sol.display();
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}