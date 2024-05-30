#include <iostream>
#include <fstream>
#include "bintree_eda.h"
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
pair<int, int> buscar_tesoros(bintree<int> tree, int carga) {
  int barcos, huecos;
  if(tree.empty()){
    barcos = 0;
    huecos = 0;
  }else if(tree.left().empty() && tree.right().empty()){
    int resto = tree.root() % carga;
    if(resto > 0){
      barcos = (tree.root() / carga) + 1;
      huecos = carga - resto;
    }else{
      barcos = tree.root() / carga;
      huecos = 0;
    }
  }else{
    auto[barcosIz, huecosIz] = buscar_tesoros(tree.left(), carga);
    auto[barcosDer, huecosDer] = buscar_tesoros(tree.right(), carga);
    if((huecosIz + huecosDer) - tree.root() == 0){
      barcos = barcosIz + barcosDer;
      huecos = 0;
    }else if((huecosIz + huecosDer) - tree.root() > 0){
      barcos = barcosIz + barcosDer;
      huecos = (huecosIz + huecosDer) - tree.root();
    }else{
      int sobrantes = (tree.root() - (huecosIz + huecosDer));
      int resto = sobrantes % carga;
      if(resto > 0){ 
        barcos = (barcosIz + barcosDer) + (sobrantes / carga) + 1;
        huecos = carga - resto;
      }else{
        barcos = (barcosIz + barcosDer) + (sobrantes / carga);
        huecos = 0;
      }
    }
  }
  return {barcos, huecos};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
  // leer los datos de la entrada
  bintree<int> tree = leerArbol(-1);
  int N; cin >> N;
  auto[barcos, huecos] = buscar_tesoros(tree, N);
  
  // escribir solución
  cout << barcos << " " << huecos <<'\n';
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