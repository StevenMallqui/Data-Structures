#include <iostream>
#include <fstream>
#include <list>

// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
bool es_toeplitz(const list<list<int>> &matriz){
  auto iter = matriz.begin();
  auto nextIter = ++matriz.begin();
  bool toeplitz = true;
  while(nextIter != matriz.end() && toeplitz){
    auto itF = (*iter).begin();
    auto itS = ++(*nextIter).begin();

    while(itS != (*nextIter).end() && toeplitz){
      if(*itF != *itS)
        toeplitz = false;
      
      itF++;
      itS++;
    }

    iter++;
    nextIter++;
  }

  return toeplitz;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
  // leer los datos de la entrada
  int elem; cin >> elem;
  if (elem == 0)
    return false;

  list<list<int>> matriz;

  while(elem != 0){
    list<int> lista;
    while(elem != 0){
      lista.push_back(elem);
      cin >> elem;
    }
    matriz.push_back(lista);
    cin >> elem;
  }

  // escribir sol
  if(es_toeplitz(matriz))
    cout << "SI\n";
  else
    cout << "NO\n";

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