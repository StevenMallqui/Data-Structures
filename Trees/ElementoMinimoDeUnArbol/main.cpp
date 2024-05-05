
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "bintree.h"
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
template <typename T> T min_elem(const BinTree<T> &tree) {
  if(tree.left().empty() && tree.right().empty()){
    return tree.root();
  }else{
    T min = tree.root();

    if(!tree.left().empty()){
      T mleft = min_elem(tree.left());
      if(mleft < min){
        min = mleft;
      }
    }
    
    if(!tree.right().empty()){
      T mright = min_elem(tree.right());
      if(mright < min){
        min = mright;
      }
    }

    return min;
  }
}

bool resuelveCaso() {
  
  // leer los datos de la entrada
  char type; cin >> type;
  if (!std::cin)  // fin de la entrada
    return false;

  if(type == 'N'){
    BinTree<int> arbin;
    arbin = read_tree<int>(cin);
    cout << min_elem(arbin) << "\n";
  }else if(type == 'P'){
    BinTree<string> arbin;
    arbin = read_tree<string>(cin);
    cout << min_elem(arbin) << "\n";
  }
    
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
   system("PAUSE");
#endif
   return 0;
}