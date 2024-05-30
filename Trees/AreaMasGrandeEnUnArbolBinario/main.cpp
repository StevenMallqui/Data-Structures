#include <iostream>
#include <fstream>
#include "bintree.h"
// Introduce más librerías si son necesarias
using namespace std;


// función que resuelve el problema
pair<int, int> area_mayor_sin_barreras_aux(const BinTree<bool> &tree){
   int areaActual;
   int maxArea;
   if(tree.empty()){
      areaActual = 0;
      maxArea = 0;
   }else if(tree.left().empty() && tree.right().empty()){
      if(tree.root()){
         areaActual = 0;
         maxArea = 0;
      }else{
         areaActual = 1;
         maxArea = 1;
      }
   }else{
      auto[areaActualIz, maxAreaIz] = area_mayor_sin_barreras_aux(tree.left());
      auto[areaActualDer, maxAreaDer] = area_mayor_sin_barreras_aux(tree.right());

      if(!tree.root()){
         areaActual = areaActualIz + areaActualDer + 1;
         maxArea = max(max(areaActual, maxAreaIz), maxAreaDer);
      }else{
         areaActual = 0;
         maxArea = max(maxAreaIz, maxAreaDer);
      }
   }

   return {areaActual, maxArea};
}

int area_mayor_sin_barreras(const BinTree<bool> &tree){
   return area_mayor_sin_barreras_aux(tree).second;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   BinTree<bool> tree = read_tree<bool>(cin);

   // escribir solución
   cout << area_mayor_sin_barreras(tree) <<'\n';
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