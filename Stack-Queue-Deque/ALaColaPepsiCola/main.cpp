
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "queue_linkedlist.h"
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   QueueLinkedList<int> cola, colegas;
   int elem;
   cin >> elem;
   while(elem != -1){
      cola.push(elem);
      cin >> elem;
   }

   int pringao; cin >> pringao;

   cin >> elem;
   while(elem != -1){
      colegas.push(elem);
      cin >> elem;
   }

   cola.write(cout);
   cout <<'\n';
   cola.colarse(pringao, colegas);
   cola.write(cout);
   cout <<'\n';
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