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
#include <algorithm>

using namespace std;

using villano = string;
using heroe = string;
using personaje = string;
using ataque = string;
using dano = int;

class SistemaBatallas{
private:

  struct infoPersonaje{
    int puntosV;
    int puntosD;
    int tipo; // 0 villano, 1 heroe
    list<personaje>::iterator it;
    map<ataque, dano> ataques;
  };

  unordered_map<personaje, infoPersonaje> personajes;
  list<personaje> turnos;
 
public: 

void aparece_villano(string v, int s, int a){
  if(personajes.count(v))
    throw invalid_argument("Personaje ya existente");
  
  turnos.push_back(v);
  personajes[v].tipo = 0;
  personajes[v].puntosV = s;
  personajes[v].puntosD = a;
  personajes[v].it = --turnos.end();
}

void aparece_heroe(string h, int s){
  if(personajes.count(h))
    throw invalid_argument("Personaje ya existente");
  
  turnos.push_back(h);
  personajes[h].tipo = 1;
  personajes[h].puntosV = s;
  personajes[h].it = --turnos.end();
}

void aprende_ataque(string h, string a, int v){
  if(!personajes.count(h) || personajes[h].tipo == 0)
    throw invalid_argument("Heroe inexistente");

  if(personajes[h].ataques.count(a))
    throw invalid_argument("Ataque repetido");

  personajes[h].ataques[a] = v;
}

vector<pair<string, int>> mostrar_ataques(string h) const{
  if(!personajes.count(h) || personajes.at(h).tipo == 0)
    throw invalid_argument("Heroe inexistente");

  vector<pair<string, int>> result;
  for(const auto &[k, v] : personajes.at(h).ataques)
    result.push_back(make_pair(k,v));

  return result;
}

vector<pair<string, int>> mostrar_turnos() const{
  vector<pair<string, int>> result;

  for(personaje p : turnos)
    result.push_back(make_pair(p, personajes.at(p).puntosV));
  
  return result;
}

bool villano_ataca(string v, string h){
  if(!personajes.count(v) || personajes.at(v).tipo == 1)
    throw invalid_argument("Villano inexistente");

  if(!personajes.count(h) || personajes.at(h).tipo == 0)
    throw invalid_argument("Heroe inexistente");

  if(personajes[v].it != turnos.begin())
    throw invalid_argument("No es su turno");

  personajes[h].puntosV -= personajes[v].puntosD;
  
  bool vencido = false;
  if(personajes[h].puntosV <= 0){
    turnos.erase(personajes[h].it);
    personajes.erase(h);
    vencido = true;
  }

  turnos.push_back(turnos.front());
  turnos.pop_front();
  personajes[v].it = --turnos.end();
  
  return vencido;
}

bool heroe_ataca(string h, string a, string v){
  if(!personajes.count(v) || personajes.at(v).tipo == 1)
    throw invalid_argument("Villano inexistente");

  if(!personajes.count(h) || personajes.at(h).tipo == 0)
    throw invalid_argument("Heroe inexistente");

  if(personajes[h].it != turnos.begin())
    throw invalid_argument("No es su turno");

  if(!personajes[h].ataques.count(a))
    throw invalid_argument("Ataque no aprendido");

  personajes[v].puntosV -= personajes[h].ataques[a];

  bool vencido = false;
  if(personajes[v].puntosV <= 0){
    turnos.erase(personajes[v].it);
    personajes.erase(v);
    vencido = true;
  }

  turnos.push_back(turnos.front());
  turnos.pop_front();
  personajes[h].it = --turnos.end();

  return vencido;
}
};

bool tratar_caso() {
  SistemaBatallas sb;
  string comando;
  cin >> comando;
  if (cin.eof()) return false;

  while (comando != "FIN") {
    try {
      if (comando == "aparece_villano") {
        string nombre;
        int puntos, ataque;
        cin >> nombre >> puntos >> ataque;
        sb.aparece_villano(nombre, puntos, ataque);
      } else if (comando == "aparece_heroe") {
        string nombre; int puntos;
        cin >> nombre >> puntos;
        sb.aparece_heroe(nombre, puntos);
      } else if (comando == "aprende_ataque") {
        string nombre; string ataque; int valor;
        cin >> nombre >> ataque >> valor;
        sb.aprende_ataque(nombre, ataque, valor);
      } else if (comando == "mostrar_ataques") {
        string nombre;
        cin >> nombre;
        vector<pair<string, int>> ataques = sb.mostrar_ataques(nombre);
        cout << "Ataques de " << nombre << "\n";
        for (const auto &[at, v] : ataques) {
          cout << at << " " << v << "\n";
        }
      } else if (comando == "mostrar_turnos") {
        vector<pair<string, int>> turnos = sb.mostrar_turnos();
        cout << "Turno:" << "\n";
        for (const auto &[nombre, pv] : turnos) {
          cout << nombre << " " << pv << "\n";
        }
      } else if (comando == "villano_ataca") {
        string villano, heroe;
        cin >> villano >> heroe;
        bool derrotado = sb.villano_ataca(villano, heroe);
        cout << villano << " ataca a " << heroe << "\n";
        if (derrotado) {
          cout << heroe << " derrotado\n";
        }
      } else if (comando == "heroe_ataca") {
        string heroe, ataque, villano;
        cin >> heroe >> ataque >> villano;
        bool derrotado = sb.heroe_ataca(heroe, ataque, villano);
        cout << heroe << " ataca a " << villano << "\n";
        if (derrotado) {
          cout << villano << " derrotado\n";
        }
      }
    } catch (invalid_argument &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> comando;
  }

  cout << "---\n";

  return true;

}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}