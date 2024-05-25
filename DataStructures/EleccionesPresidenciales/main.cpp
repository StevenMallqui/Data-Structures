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
#include <algorithm>

using namespace std;
using estado = string;
using partido = string;
using votos = int;

class ConteoVotos {

private: 
    struct infoEstado{
        int numCompromisarios;
        partido ganador;
        unordered_map<partido, votos> escrutinio;
    };
    unordered_map<estado, infoEstado> estados;
    unordered_map<partido, int> resultado;

public: 
    void nuevo_estado(const string &nombre, int num_compromisarios){
        if(estados.count(nombre))
            throw domain_error("Estado ya existente");
        
        estados.insert({nombre, {num_compromisarios,{}}});
    }

    void sumar_votos(const string &estado, const string &partido, int num_votos){
        if(!estados.count(estado))
            throw domain_error("Estado no encontrado");

        infoEstado &estadoInfo = estados[estado];
        string lastGanador = estadoInfo.ganador;
        estadoInfo.escrutinio[partido] += num_votos;

        if(lastGanador != partido && estadoInfo.escrutinio[lastGanador] < estadoInfo.escrutinio[partido]){
            auto it = resultado.find(lastGanador);
            if (it != resultado.end()) {
                it->second -= estadoInfo.numCompromisarios;
                if (it->second <= 0)
                    resultado.erase(it);
            }

            estadoInfo.ganador = partido;
            resultado[estadoInfo.ganador] += estadoInfo.numCompromisarios;
        }
    }

    string ganador_en(const string &estado) const{
        if(!estados.count(estado))
            throw domain_error("Estado no encontrado");

        return estados.at(estado).ganador;
    }

    vector<pair<string,int>> resultados() const{
        vector<pair<string, int>> result;
        for (const auto &entry : resultado) 
            result.push_back(make_pair(entry.first, entry.second));
        
        sort(result.begin(), result.end());
        return result;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    std::string op;
    std::cin >> op;
    if (!std::cin)
        return false;
    
    ConteoVotos centro;
    
    while (op != "FIN") {
        
        try {
            
            if (op == "nuevo_estado") {
                
                string s;
                int n;
                std::cin >> s >> n;
                
                centro.nuevo_estado(s, n);
                
            }
            
            else if (op == "sumar_votos") {
                
                string s, p;
                int n; 
                std::cin >> s >> p >> n;
                centro.sumar_votos(s,p,n);    
            }
            
            else if (op == "ganador_en") {
                string s;
                std::cin >> s;
                string winner = centro.ganador_en(s);
                cout << "Ganador en " << s << ": " << winner << "\n";
            }
            
            if (op == "resultados") {
                vector<pair<string,int> > v = centro.resultados();
                for (auto el: v) {
                    cout << el.first << " " << el.second << "\n";
                }   
            }
        }
        catch(std::domain_error& e) {
            
            std::cout << e.what() << "\n";
        }
        
        std::cin >> op;
        
    } 
    
    std::cout << "---\n";
    
    return true;
    
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso()) ;//Resolvemos todos los casos
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0; 
}