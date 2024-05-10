#include <stdio.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map> 
#include <list> 
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

using rasgo = string;
using sospechoso = string;
using jugador = string;
using descartado = string;
class MisteriosDePekin {
   
    private:
  
    struct InfoJugador{
      unordered_set<descartado> descartados;
      list<jugador>::iterator it;
    };
    //  unordered_map: conjunto desordenado de sospechosos para cada rasgo 
    unordered_map<rasgo, unordered_set<sospechoso>> rasgos;
    // conjunto de sospechosos ordenado
    set<sospechoso> sospechosos;
    // unordered_map: conjunto desordenado de descartados para cada jugador.
    unordered_map<jugador, InfoJugador> jugadores;
    list<jugador> ganadoresPotencial;
    string culpable; 

    public:

    MisteriosDePekin(const string &culpable) : culpable(culpable){
      sospechosos.insert(culpable);
    }

    void anyadir_rasgo(const string &sospechoso, const string &rasgo) {
      if(!jugadores.empty())
        throw domain_error("Juego ya empezado");
      
      auto &it = rasgos[rasgo];
      if(it.count(sospechoso) == 0){
        it.insert(sospechoso);
      }
      
      if(sospechosos.find(sospechoso) == sospechosos.end())
        sospechosos.insert(sospechoso);
    }

    vector<string> sospechososF() const {
      vector<string> lista;
      for(sospechoso s : sospechosos){
        lista.push_back(s);
      }

      return lista;
    }

    vector<string> ganadores_potenciales() const{
      vector<string> lista;
      for(jugador j : ganadoresPotencial){
        lista.push_back(j);
      }
      return lista;
    }

    void nuevo_jugador(const string &nombre) { 
      
      if(jugadores.count(nombre))
        throw domain_error("Jugador existente");

      jugadores.insert({nombre, {}});
      jugadores[nombre].it = ganadoresPotencial.end();

      if(puede_detener_culpable(nombre)){
        ganadoresPotencial.push_back(nombre);
        jugadores[nombre].it = --ganadoresPotencial.end();
      }
    }

    bool jugador_enganyado(const string &jugador) const {
      auto it = jugadores.find(jugador);
      if(it == jugadores.end())
        throw domain_error("Jugador no existente");
      
      return it->second.descartados.count(culpable);
    }

    void jugador_descarta(const string &jugador, const string &rasgo) {
      if(jugadores.count(jugador) == 0)
        throw domain_error("Jugador no existente");
      
      for(sospechoso s : rasgos[rasgo]){
        jugadores[jugador].descartados.insert(s);
      }

      if(puede_detener_culpable(jugador) && jugadores[jugador].it == ganadoresPotencial.end()){
        ganadoresPotencial.push_back(jugador);
        jugadores[jugador].it = --ganadoresPotencial.end();
      }else if(!ganadoresPotencial.empty() &&  (sospechosos.size() == jugadores[jugador].descartados.size()))
        ganadoresPotencial.erase(jugadores[jugador].it);
      
    }

    bool puede_detener_culpable(const string &jugador) {
      auto it = jugadores.find(jugador);
      if(it == jugadores.end())
        throw domain_error("Jugador no existente");

      return (it->second.descartados.size() == sospechosos.size() - 1) && (it->second.descartados.find(culpable) == it->second.descartados.end());
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string culpable;
    cin >> culpable;
    if (!std::cin)
        return false;
    if (culpable == "FIN") {
        std::cout << "---\n";
        return true;
    }
    cout << "OK\n";
    MisteriosDePekin centro(culpable);
    std::string op;
    std::cin >> op;
    while (op != "FIN") {
        
        try {
            
            if (op == "nuevo_jugador") {
                
                string j;
                std::cin >> j;
                
                centro.nuevo_jugador(j);
                cout << "OK\n";
            }
            
            else if (op == "anyadir_rasgo") {
                
                string s, r;
                std::cin >> s >> r;
                centro.anyadir_rasgo(s, r);
                cout << "OK\n";
            }
            
            else if (op == "puede_detener_culpable") {
                string j;
                std::cin >> j;
                bool puede = centro.puede_detener_culpable(j);
                cout << j;
                if (!puede) {
                    cout << " no";
                }
                cout << " puede detener al culpable\n";
            }
            else if (op == "jugador_enganyado") {
                string j;
                std::cin >> j;
                bool enganyado = centro.jugador_enganyado(j);
                cout << j;
                if (!enganyado) {
                    cout << " no";
                }
                cout << " ha sido enganyado\n";
            } else if (op == "ganadores_potenciales") {
                vector<string> v = centro.ganadores_potenciales();
                bool first = true;
                for (string el: v) {
                    if (first) {
                        first = false;
                        cout << el;
                    } else {
                        cout << " " << el;
                    }
                }   
                cout << "\n";
            } else if (op == "jugador_descarta") {
                string j, r;
                cin >> j >> r;
                centro.jugador_descarta(j,r);
                cout << "OK\n";
            } else if (op == "sospechosos") {
                vector<string> v = centro.sospechososF();
                bool first = true;
                for (string el: v) {
                    if (first) {
                        first = false;
                        cout << el;
                    } else {
                        cout << " " << el;
                    }
                }   
                cout << "\n";
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
        while (resuelveCaso()) ;//Resolvemos todos los casos
    #ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
}