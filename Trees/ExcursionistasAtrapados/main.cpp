
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "bintree.h"
#include <utility>
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
template <typename T> pair<int,int> rescatar(const BinTree<T> &tree) {
   int grupos, maxG;
   if(tree.empty()){
      grupos = 0;
      maxG = 0;
   }else if(tree.right().empty() && tree.left().empty()){
      if(tree.root())
         grupos = 1;
      else
         grupos = 0;
      maxG = tree.root();
   }else{
      auto[gruposIz, maxGIz] = rescatar(tree.left());
      auto[gruposDer, maxGDer] = rescatar(tree.right());
      maxG = max(maxGIz, maxGDer) + tree.root();
      if(gruposIz > 0 && gruposDer > 0){
         grupos = gruposIz + gruposDer;
      }else if(gruposIz > 0 && gruposDer == 0){
         grupos = gruposIz;
      }else if(gruposIz == 0 && gruposDer > 0){
         grupos = gruposDer;
      }else if(gruposIz == 0 && gruposDer == 0){
         if(maxG > 0)
            grupos = 1;
         else
            grupos = 0;
      }
   }

   return {grupos, maxG};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   BinTree<int> tree = read_tree<int>(cin);
   // escribir solución
   pair<int,int> sol = rescatar(tree);
   cout << sol.first <<" " << sol.second << '\n';
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