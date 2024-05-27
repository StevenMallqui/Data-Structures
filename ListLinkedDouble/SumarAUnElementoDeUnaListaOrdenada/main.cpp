#include <iostream>
#include <fstream>
#include "list_linked_double.h"
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
  // leer los datos de la entrada
  int N, i, m, elem; cin >> N; cin >> i; cin >> m;
  if (N == 0 && i == 0 && m == 0)
    return false;

  ListLinkedDouble lista;
  for(int i = 0; i < N; i++){
    cin >> elem;
    lista.push_back(elem);
  }

   lista.add_to(i, m);
  // // escribir sol
   lista.display();
   cout <<'\n';

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