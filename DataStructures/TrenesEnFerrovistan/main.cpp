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

using namespace std;

using estacion = string;
using linea = string;
using posicion = int;
using distancia = int;
class Ferrovistan{
private:
  unordered_map<estacion, map<linea, posicion>> estaciones;
  unordered_map<linea, map<posicion, estacion>> lineas;

public:
  void nueva_linea(const string &nombre){
    if(lineas.count(nombre))
      throw domain_error("Linea existente");
    
    lineas.insert({nombre, {}});
  }

  void nueva_estacion(const string &linea, const string &nombre, int posicion){
    if(!lineas.count(linea))
      throw domain_error("Linea no existente");
    
    if(estaciones.count(nombre) && estaciones[nombre].count(linea))
      throw domain_error("Estacion duplicada en linea");
    
    if(lineas[linea].count(posicion))
      throw domain_error("Posicion ocupada");

    estaciones[nombre][linea] = posicion;
    lineas[linea][posicion] = nombre;
  }

  void eliminar_estacion(const string &estacion){
    if(!estaciones.count(estacion))
      throw domain_error("Estacion no existente");

    for(auto [k, v] : estaciones[estacion]){
      lineas[k].erase(v);
    }
    estaciones.erase(estacion);
  }

  vector<string> lineas_de(const string &estacion) const{
    if(!estaciones.count(estacion))
      throw domain_error("Estacion no existente");
    
    vector<string> result;

    for(const auto &[k ,v] : estaciones.at(estacion))
      result.push_back(k);
    
    return result;
  }

  string proxima_estacion(const string &linea, const string &estacion) const{
    if(!lineas.count(linea))
      throw domain_error("Linea no existente");

    if(!estaciones.count(estacion) || !estaciones.at(estacion).count(linea))
      throw domain_error("Estacion no existente");

    const int actual = estaciones.at(estacion).at(linea);
    auto proxima = ++lineas.at(linea).find(actual);

    if(proxima == lineas.at(linea).end())
      throw domain_error("Fin de trayecto");
    
    return proxima->second;
  }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
	std::string op;
	std::cin >> op;
	if (!std::cin)
		return false;
	
	Ferrovistan ferrovistan;
	
	while (op != "FIN") {
		
		try {
			
			if (op == "nueva_linea") {
				
				linea l;
				std::cin >> l;
				
				ferrovistan.nueva_linea(l);
				
			}
			
			else if (op == "nueva_estacion") {
				
				linea l;
				estacion e;
				distancia d;

				std::cin >> l >> e >> d;
				
				ferrovistan.nueva_estacion(l, e, d);
				
			}
			
			else if (op == "eliminar_estacion") {
				
				estacion e;
				std::cin >> e;
				ferrovistan.eliminar_estacion(e);
			}
		
			else if (op == "lineas_de") {
				
				estacion e;
				std::cin >> e;
				vector<linea> lineas = ferrovistan.lineas_de(e);
				cout << "Lineas de " << e << ": ";
				int i = 0;
				for (linea l : lineas) {
					cout << l;
					if (i < lineas.size() - 1) cout << " ";
					i++;
				}
				cout << '\n';
				
			}
			if (op == "proxima_estacion") {
				linea l;
				estacion e;
				std::cin >> l >> e;
				
				cout << ferrovistan.proxima_estacion(l, e) << '\n';
			}
			
		}
		catch(std::domain_error& e) {
			
			std::cout << "ERROR: " << e.what() << "\n";
		}
		
		std::cin >> op;
		
	}
	
	std::cout << "---\n";
	
	return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (resuelveCaso());

#ifndef DOMJUDGE
std::cin.rdbuf(cinbuf);
#endif
return 0;
}