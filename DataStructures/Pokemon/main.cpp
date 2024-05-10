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

using entrenador = string;
using nivel = int;
using pokemon = string;

class CentroPokemon {
public:

	void capturar_pokemon (entrenador e, pokemon p, nivel n){

		auto& it = centroPokemon[e];

		if(it.tipos.count(p))
			throw invalid_argument("Pokemon repetido");

		if(it.niveles.count(n))
			throw invalid_argument("Nivel repetido");

		it.pokemons.push_back(p);
		it.tipos[p] = {n, --it.pokemons.end()};
		it.niveles[n] = p;
	}

	pair<pokemon,nivel> vencer_pokemon(entrenador e,nivel n){

		if(centroPokemon.count(e) == 0)
			throw invalid_argument("Entrenador no existente");
		
		if(centroPokemon[e].pokemons.empty())
			throw invalid_argument("No tiene pokemons");

		auto pokemonMax = --centroPokemon[e].niveles.end();
		if(pokemonMax->first < n)
			throw invalid_argument("El pokemon no puede ser vencido");
		
		return pair<pokemon, nivel>(pokemonMax->second, pokemonMax->first);
	}

	int dia_de_liberacion(pokemon p){
		int liberados = 0;
		for(auto it = centroPokemon.begin(); it != centroPokemon.end(); it++){
			if(it->second.tipos.count(p)){
				it->second.niveles.erase(it->second.tipos[p].n);
				it->second.pokemons.erase(it->second.tipos[p].it);
				it->second.tipos.erase(p);
				liberados++; 	
			}	
		}

		return liberados;
	}

	pokemon gimnasio(entrenador e){
		if(centroPokemon.count(e) == 0)
			throw invalid_argument("Entrenador no existente");
		
		if(centroPokemon[e].pokemons.empty())
			throw invalid_argument("No tiene pokemons");
			
		pokemon gymPok = centroPokemon[e].pokemons.front();
		centroPokemon[e].niveles.erase(centroPokemon[e].tipos[gymPok].n);
		centroPokemon[e].tipos.erase(gymPok);
		centroPokemon[e].pokemons.pop_front();

		return gymPok;
	}

private:

	struct pokemonInfo{
		nivel n;
		list<pokemon>::iterator it;
	};

	struct entrenadorInfo{
		list<pokemon> pokemons;
		unordered_map<pokemon, pokemonInfo> tipos;
		map<nivel, pokemon> niveles;
	};

	unordered_map<entrenador, entrenadorInfo> centroPokemon;
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	
	std::string op;
	std::cin >> op;
	if (!std::cin)
		return false;
	
	CentroPokemon centro;
	
	while (op != "FIN") {
		
		try {
			
			if (op == "capturar_pokemon") {
				
				entrenador e; pokemon p; nivel n;
				std::cin >> e >> p >> n;
				
				centro.capturar_pokemon(e, p, n);
				
			}
			
			else if (op == "vencer_pokemon") {
				
				entrenador e; int n;
				std::cin >> e >> n;
				
				std::pair<pokemon,nivel> p = centro.vencer_pokemon(e,n);
				std::cout << e << " utiliza el pokemon " << p.first << " con nivel " <<
p.second << " para vencer a un nivel " << n << '\n';
			}
			
			else if (op == "dia_de_liberacion") {
				pokemon p;
				std::cin >> p;
				int n = centro.dia_de_liberacion(p);
				std::cout << "Liberados "<< n << " pokemon " << p << '\n';
			}
			
			if (op == "gimnasio") {
				entrenador e;
				std::cin >> e;
				pokemon p = centro.gimnasio(e);
				std::cout << e << " deja el pokemon " << p << " en un gimnasio\n";
			}
		}
		catch(std::invalid_argument& e) {
			
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
		// Descomentar si se trabaja en Windows
		// system("PAUSE");
	#endif
		return 0;	
}