
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "bintree.h"
#include <utility>
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
template <typename T> pair<int,int> rescatar(const BinTree<T> &tree) {
  if(tree.empty()){
    return {-1, -1};
  }else if(tree.left().empty() && tree.right().empty()){
    return {1, tree.root()};
  }else{
    pair<int, int> cleft = rescatar(tree.left());
    pair<int, int> cright = rescatar(tree.right());
    int grupos, max;
    if(cleft.first == -1 && cright.first > 0){
      
    }else if(cleft.first > 0 && cright.first == -1){
    
    }
    return {grupos, max}
  }

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   BinTree<int> tree = read_tree<int>(cin);
   // escribir solución
   pair<int,int> sol = rescatar(tree);
   cout << sol.first << sol.second << '\n';
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
   system("PAUSE");
#endif
   return 0;
}