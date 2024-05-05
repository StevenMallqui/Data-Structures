#include <iostream>
#include <fstream>
#include "list_linked_single.h"
// Introduce más librerías si son necesarias
using namespace std;


// función que resuelve el problema
void resolver(ListLinkedSingle<int> lista) {
   lista.duplicate();
   lista.display();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
  // leer los datos de la entrada
  int elem; cin >> elem; 
  ListLinkedSingle<int> lista;
  while(elem != 0){
    lista.push_back(elem);
    cin >> elem;
  }

  resolver(lista);
  
  // escribir solución
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