/*
 * ---------------------------------------------------------------
 *                       ESTRUCTURAS DE DATOS
 * ---------------------------------------------------------------
 */
 
 //INDICAD VUESTRO NOMBRE AL FINAL DEL FICHERO. POR FAVOR.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

//{{{

//}}}
// Añade los #include que necesites
//@ </answer>


using namespace std;

//@ <answer>

// Implementa los métodos pedidos dentro de la clase.
// No te olvides del coste de cada método.
using Caco = string;
using Velocidad = int;
using Escondite = string;
class PolisCacos {
public:

  // El coste de la funcion es O(1)
  void nuevo_jugador(const string & nombre, int velocidad, const string &primer_lugar) { 
    if(cacos.find(nombre) != cacos.end()) // O(1)
      throw invalid_argument("caco ya existe");

    InfoCaco info;
    info.num = velocidad;
    info.it = cacosPillados.end(); // O(1)
    info.escondites.push_back(primer_lugar); // O(1)
    cacos.insert({nombre, info}); // O(1)
    lugares[primer_lugar][velocidad] = nombre;
  }

  // El coste de la funcion es O(1)
  void descubrir_lugar(const string & nombre, const string & nuevo_lugar){
    if(cacos.find(nombre) == cacos.end()) // O(1)
      throw invalid_argument("caco no existe");
    
    if(cacos[nombre].it != cacosPillados.end()) // O(1)
      throw invalid_argument("caco pillado");
    
    cacos[nombre].escondites.push_back(nuevo_lugar); // O(1)
  }

  // El coste de la funcion es O(n), siendo n el tamaño de la lista de escondites del caco
  void abandonar_juego(const string & nombre){ 

    if(cacos.find(nombre) == cacos.end()) // O(1)
      throw invalid_argument("caco no existe");

    InfoCaco info_caco = cacos[nombre];
    cacos.erase(nombre); // O(1)
    for(string aux : info_caco.escondites){ // O(n)
      lugares[aux].erase(info_caco.num);
    }

    if(info_caco.it != cacosPillados.end()) // O(1)
      cacosPillados.erase(info_caco.it);
  }

  // El coste de la funcion es O(1)
  string cambiar_lugar(const string & nombre){ 

    if(cacos.find(nombre) == cacos.end()) // O(1)
      throw invalid_argument("caco no existe");
    
    if(cacos[nombre].it != cacosPillados.end()) // O(1)
      throw invalid_argument("caco pillado");

    InfoCaco &info_caco = cacos[nombre];
    string n_lugar = info_caco.escondites.front(); // O(1)
    if(info_caco.escondites.size() > 1){ 
      lugares[info_caco.escondites.front()].erase(info_caco.num); // O(1)
      info_caco.escondites.push_back(info_caco.escondites.front()); // O(1)
      info_caco.escondites.pop_front(); // O(1)
      n_lugar = info_caco.escondites.front(); // O(1)
      lugares[n_lugar][info_caco.num] = nombre;
    }

    return n_lugar;
  }

  // El coste de la funcion es O(1)
  string siguiente_poli() const{ 
    if(cacosPillados.empty()) // O(1)
      throw invalid_argument("nadie ha sido pillado");

    return cacosPillados.front(); // O(1)
  }

  // El coste de la funcion es O(1)
  string poli_busca_en(string lugar){ 
    if(lugares[lugar].empty()) // O(1)
      throw invalid_argument("lugar vacio");

    int velocidad = lugares[lugar].begin()->first; // O(1)
    string caco = lugares[lugar].begin()->second; // O(1)
    lugares[lugar].erase(velocidad); // O(1)
    cacosPillados.push_back(caco); // O(1)
    cacos[caco].it = --cacosPillados.end(); //O(1)

    return caco;
  }

private:
  struct InfoCaco
  {
    Velocidad num;
    list<Caco>::iterator it;
    list<Escondite> escondites;
  };
  
  unordered_map<Caco, InfoCaco> cacos;
  unordered_map<Escondite, map<Velocidad, Caco>> lugares;
  list<Caco> cacosPillados;
};
 


//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>

bool tratar_caso() {
  PolisCacos f;
  string operacion;
  cin >> operacion;
  
  if (cin.eof()) return false;
  
  while (operacion != "FIN") {
    try {
      if (operacion == "nuevo_caco") {
        string nombre, lugar; cin >> nombre; int velocidad; cin >> velocidad;
cin >> lugar;
        f.nuevo_jugador(nombre, velocidad, lugar);
        cout << nombre << " es el nuevo jugador" << "\n";
      } else if (operacion == "descubre_nuevo_lugar") {
        string nombre, lugar; cin >> nombre >> lugar;
        f.descubrir_lugar(nombre, lugar);
        cout << nombre << " descubre " << lugar << "\n";
      } else if (operacion == "cambia_lugar") {
        string nombre; cin >> nombre;
        cout << nombre << " se refugia " << f.cambiar_lugar(nombre) << endl;
      }else if (operacion == "abandona_juego") {
        string nombre; cin >> nombre;
        f.abandonar_juego(nombre);
        cout << nombre << " abandona el juego" << "\n";
      } else if (operacion == "siguiente_poli") {
        cout << f.siguiente_poli() << " es el siguiente poli"<< "\n";
      } else if (operacion == "poli_busca_en") {
        string lugar; cin >> lugar;
        string pillado = f.poli_busca_en(lugar);
        cout << pillado << " ha sido cazado \n";
      }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> operacion;
  }  
  cout << "---\n";
  return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while(tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

//@ <answer>

// Nombre y apellidos: ________________________________________  Diego Martínez y Steven Mallqui

//@ </answer>
 

//@ <answer>