/*

medico:
  - string: nombre
  - los pacientes tienen un orden de llegada
  - elimina de la lista al siguiente paciente

paciente:
  -string: nombre
  - ser atendido por un medico, puede estar esperando a varios medicos
  - no puede pedir consulta a un medico que ya esta esperado (no tiene que estar en la cola del medico dos veces)
  - paciente cansado de esperar, puede abandonar (iterador)
  - lista ordenada de medicos que dejan de atender a este paciente


  unordered_map<medico, list<paciente>> medicos;
  unordered_map<paciente, map<medico, iterator>> pacientes;
*/

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;

bool resuelveCaso();

using medico = string;
using paciente = string;
using listaMedicos = list<medico>;
using listaEspera = list<paciente>;

class Hospital {
	
	unordered_map<medico, listaEspera> medicos;
	unordered_map<paciente, map<medico, listaEspera::iterator>> pacientes;
	
public:
	
	void altaMedico(medico m) {
    if(medicos.count(m))
      throw domain_error("Medico existente");

    medicos[m];
	}
	
	void pedirConsulta(paciente p, medico m) {
    if(!medicos.count(m))
      throw domain_error("Medico inexistente");

    if(pacientes.count(p) && pacientes[p].count(m))
      throw domain_error("Paciente ya esperando");

    medicos[m].push_back(p);
    pacientes[p][m] = --medicos[m].end();
	}
	
	paciente siguientePaciente(medico m) {
    if(!medicos.count(m))
      throw domain_error("Medico inexistente");
    
    if(medicos[m].empty())
      throw domain_error("Medico sin pacientes");

    return medicos[m].front();
	}
	
	void atenderConsulta(medico m) {
    if(!medicos.count(m))
      throw domain_error("Medico inexistente");
    
    if(medicos[m].empty())
      throw domain_error("Medico sin pacientes");
    
    pacientes[medicos[m].front()].erase(m);
    if(pacientes[medicos[m].front()].empty())
      pacientes.erase(medicos[m].front());
    medicos[m].pop_front();
	}
	
	listaMedicos abandonarConsulta(paciente p) {
    if(!pacientes.count(p))
      throw domain_error("Paciente inexistente");

    listaMedicos lista;
    for(auto [k, v]: pacientes[p]){
      lista.push_back(k);
      medicos[k].erase(v);
    }
    pacientes.erase(p);

    return lista;
	}

};

bool resuelveCaso() {
   
	std::string op;
	std::cin >> op;
	if (!std::cin)
		return false;
	
	Hospital hospital;
	
	while (op != "FIN") {
		
		try {
			
			if (op == "altaMedico") {
				
				medico m;
				std::cin >> m;
				
				hospital.altaMedico(m);
				
			}
			
			else if (op == "pedirConsulta") {
				
				paciente p;
				medico m;

				std::cin >> p >> m;
				
				hospital.pedirConsulta(p, m);
				
			}
			
			else if (op == "siguientePaciente") {
				
				medico m;
				std::cin >> m;
				std::cout << hospital.siguientePaciente(m) << '\n';
			}
		
			else if (op == "atenderConsulta") {
				
				medico m;
				std::cin >> m;
				hospital.atenderConsulta(m);
				
			}
			if (op == "abandonarConsulta") {
				paciente p;
				std::cin >> p;
				listaMedicos lista = hospital.abandonarConsulta(p);
				cout << "Medicos abandonados: ";
				int i = 0;
				for (medico m : lista) {
					cout << m;
					if (i < lista.size() - 1) cout << " ";
					i++;
				}
				cout << '\n';
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