#include <iostream>
#include <fstream>
#include <list>
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
void suavizar(list<int> &lista){   
  auto cur = lista.begin();
  auto sig = ++lista.begin();
  
  while(sig != lista.end()){
    int ini = *cur;
    if(*cur < *sig){
      ini += 1;
      for(int i = ini; i < *sig; i++){
        lista.insert(sig, i);
      }
    }else if(*cur > *sig){
      ini -= 1;
      for(int i = ini; i > *sig; i--){
        lista.insert(sig, i);
      }
    }else{
      lista.erase(cur);
    }

    cur = sig;
    sig++; 
  }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
  // leer los datos de la entrada
  int N, elem; cin >> N;
  if (!std::cin)  // fin de la entrada
    return false;

  list<int> lista;
  for(int i = 0; i < N; i++){
    cin >> elem;
    lista.push_back(elem);
  }

  suavizar(lista);

 // escribir sol
  for(auto it = lista.begin(); it != lista.end(); it++){
    cout << *it;
    if(it != --lista.end())
      cout << " ";
  }

  cout << '\n';
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