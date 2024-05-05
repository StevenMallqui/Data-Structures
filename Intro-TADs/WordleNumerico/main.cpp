/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
 /*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Steven Mallqui Aguilar
  Componente 2:
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:
  Multiconjunto():num_elems(0){}
  void anyadir(int elem);
  void eliminar(int elem);
  bool pertenece(int elem) const;
  // Implementa las operaciones necesarias.
  // No olvides el coste!
  
private:
  struct Elem {
    int valor;
    int multiplicidad;
  };
  Elem elems[MAX_ELEMS];
  int num_elems;

  int binarySearch(int target) const;
};

//Coste logarítmico

int Multiconjunto::binarySearch(int target) const{
  int low = 0;
  int high = num_elems - 1;

  while(low <= high){
    int middle = (low + high) / 2;
    if(elems[middle].valor == target) 
      return middle;
    else if ( elems[middle].valor < target) 
      low = middle + 1;
    else 
      high = middle - 1;
  }

  return low;
}

//Coste lineal con respecto a num_elems

void Multiconjunto::anyadir(int elem){
  int i = binarySearch(elem);
 
  if(elems[i].valor != elem || i == num_elems){
    for(int j = num_elems; j > i; j--){
      elems[j] = elems[j-1];
    }
    elems[i].valor = elem;
    elems[i].multiplicidad = 1;
    num_elems++;
  }else if(elems[i].valor == elem ){
    elems[i].multiplicidad++;
  }
}

//Coste logarítmico con respecto a num_elems

void Multiconjunto::eliminar(int elem){
  int i = binarySearch(elem);

  if(elems[i].valor == elem && i < num_elems){
    elems[i].multiplicidad--;

    if(elems[i].multiplicidad == 0){
      for(int j = i; j < num_elems; j++){
        elems[j] = elems[j + 1];
      }
      num_elems--;
    }
  }
}

//Coste logarítmico con respecto a num_elems

bool Multiconjunto::pertenece(int elem) const{
  int i = binarySearch(elem);
  return i < num_elems && elems[i].valor == elem && elems[i].multiplicidad != 0;
}

// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
void resuelve_caso(const vector<int> secuencia,const vector<int> intento, Multiconjunto mc, const int M){
  string resultado;

  for(int i = 0; i < M; i++){
      if(intento[i] == secuencia[i]){
        resultado.push_back('#');
        mc.eliminar(intento[i]);
      }     
       else resultado.push_back('.');
  }
  

  for(int i = 0; i < M; i++){
    if(mc.pertenece(intento[i]) && resultado[i] != '#'){
      resultado[i] = 'O';
      mc.eliminar(intento[i]);
    }
  }

  cout << resultado << endl;
}

//Coste lineal con respecto a M

bool tratar_caso() {
  int M;
  cin >> M;
  if(M == 0) return false;

  vector<int> secuencia(M), intento(M);
  Multiconjunto mc;

  for(int i = 0; i < M; i++){
    cin >> secuencia[i];
    mc.anyadir(secuencia[i]);
  }

  for(int i = 0; i < M; i++){
    cin >> intento[i];
  }

  resuelve_caso(secuencia, intento, mc, M);

  return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar en Windows si la consola se cierra inmediatamente
  // system("PAUSE");
#endif
  return 0;
}
