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
class PolisCacos {
public:

  // El coste de la funcion es O(log n), siendo n el numero de velocidades en el map
  void nuevo_jugador(const string & nombre, int velocidad, const string &primer_lugar) { 
    auto it = cacos.find(nombre); // O(1)
    if (it != cacos.end())
      throw invalid_argument("caco ya existe");

    InfoCaco info;
    info.velocidad = velocidad;
    info.esconditeActual = primer_lugar;
    cacos.insert({nombre, info}); // O(1)
    velocidades.insert({velocidad, nombre}); // O(log n)
  }

  // El coste de la funcion es O(n), siendo n el numero de cacosPillados en la lista
  void descubrir_lugar(const string & nombre, const string & nuevo_lugar){
    auto it = cacos.find(nombre); // O(1)
    if (it == cacos.end())
      throw invalid_argument("caco no existe");
    
    bool pillado = false;
    for (auto it = cacosPillados.cbegin(); it != cacosPillados.cend() && !pillado; ++it) { // O(n)
      if(*it == nombre)
        pillado = true;
    }

    if(pillado)
      throw invalid_argument("caco pillado");

    cacos[nombre].escondites.push_back(nuevo_lugar); // O(1)
  }

  // El coste de la funcion es O(n + log n) = O(n), siendo n el numero de cacosPillados en la lista
  void abandonar_juego(const string & nombre){ 
    auto it = cacos.find(nombre); // O(1)
    if (it == cacos.end())
      throw invalid_argument("caco no existe");

    InfoCaco info_caco = cacos[nombre];
    cacos.erase(nombre); // O(1)
    velocidades.erase(info_caco.velocidad); // O(log n)
    bool borrado = false;
    for (auto it = cacosPillados.begin(); it != cacosPillados.end() && !borrado; ++it) { // O(n)
      if (*it == nombre){
          it = cacosPillados.erase(it); // O(n)
          borrado = true;
      }
    }
  }

  // El coste de la funcion es O(n), siendo n el numero de cacosPillados en la lista
  string cambiar_lugar(const string & nombre){ 
    auto it = cacos.find(nombre); // O(1)
    if (it == cacos.end())
      throw invalid_argument("caco no existe");
    
    bool pillado = false;
    for (auto it = cacosPillados.cbegin(); it != cacosPillados.cend() && !pillado; ++it) { // O(n)
      if(*it == nombre)
        pillado = true;
    }

    if(pillado)
      throw invalid_argument("caco pillado");

    InfoCaco &info_caco =  cacos[nombre];
    info_caco.escondites.push_back(info_caco.esconditeActual); // O(1)
    info_caco.esconditeActual = info_caco.escondites.front(); // O(1)
    info_caco.escondites.pop_front(); // O(1)

    return info_caco.esconditeActual;
  }

  // El coste de la funcion es O(1)
  string siguiente_poli() const{ 
    if(cacosPillados.empty()) // O(1)
      throw invalid_argument("nadie ha sido pillado");

    return cacosPillados.front(); // O(1)
  }

  // El coste de la funcion es O(n), siendo n el numero de velocidades en el map
  string poli_busca_en(string lugar){ 
    bool capturado = false;
    Caco nombre = "";
    for(auto it = velocidades.begin(); it != velocidades.end() && !capturado; ++it){ // O(n)
      InfoCaco &info_caco = cacos[it->second];
      if(info_caco.esconditeActual == lugar){
        nombre = it->second;
        info_caco.esconditeActual = "";
        cacosPillados.push_back(nombre); // O(1)
        capturado = true;
      }
    }

    if(!capturado)
      throw invalid_argument("lugar vacio");

    return nombre;
  }

private:
  struct InfoCaco
  {
    int velocidad;
    string esconditeActual;
    list<string> escondites;
  };
  
  unordered_map<Caco, InfoCaco> cacos;
  map<Velocidad, Caco> velocidades;
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