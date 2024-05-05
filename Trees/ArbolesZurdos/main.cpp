
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include "bintree.h"
#include <utility>
// Introduce más librerías si son necesarias
using namespace std;

template <typename T> BinTree<T> read_tree(){
   char c; cin >> c;
   if(c == '.'){
      return BinTree<T>();
   }else{
      assert(c == '*');
      BinTree<T> left = read_tree<T>();
      BinTree<T> right = read_tree<T>();
      return BinTree<T>(left, c, right);
   }
}

template <typename T> pair<bool, int> es_zurdo(const BinTree<T> &tree){
   if(tree.empty()){
      return {true, 0};
   }else if(tree.left().empty() && tree.right().empty()){
      return {true, 1};
   }else{
      pair<bool, int> cleft = es_zurdo(tree.left());
      pair<bool, int> cright = es_zurdo(tree.right());
      bool zurdo = cleft.first && cright.first ? true : false;
      int cont = 0;
      if(zurdo && (cleft.second <= cright.second)){
         zurdo = false;
         cont = -1;
      }else{
         cont = cleft.second + cright.second + 1;
      }
      return {zurdo, cont};
   }
}

// resuelve un caso de prueba, le yendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   BinTree<char> tree = read_tree<char>();
   
   // escribir solución
   if(es_zurdo(tree).first)
      cout << "SI" << '\n';
   else
      cout << "NO" << '\n';
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