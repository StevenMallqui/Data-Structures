#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "list_linked_double.h"
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

void readList(ListLinkedDouble& lista){
  int elem;

  cin >> elem;
  while(elem != 0){
    lista.push_back(elem); 
    cin >> elem;
  }
}

void resuelveCaso() {
   
  // leer los datos de la entrada
  ListLinkedDouble l1, l2;

  readList(l1);
  readList(l2);

  l1.interseccion(l2);
  // escribir solución
  l1.display();
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
  int numCasos;
  std::cin >> numCasos;
  cin.ignore();
  for (int i = 0; i < numCasos; ++i)
    resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}