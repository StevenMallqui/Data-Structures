
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "bintree.h"
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
int diametro_Arbol(BinTree<char> tree, int& n) {
  int diametro;
  if(tree.empty()){
    diametro = 0;
  }else{
    int diamIz = diametro_Arbol(tree.left(), n);
    int diamDer = diametro_Arbol(tree.right(), n);
    if(diamIz + diamDer >= n)
      n = diamIz + diamDer + 1;
    diametro = max(diamIz, diamDer) + 1;
  }
  return diametro;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
  // leer los datos de la entrada
  BinTree<char> tree = read_tree<char>(cin);

  // escribir solución
  int diametro = 0;
  diametro_Arbol(tree, diametro);
  cout << diametro << '\n';
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