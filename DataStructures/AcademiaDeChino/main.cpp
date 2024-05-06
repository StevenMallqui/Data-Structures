
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <list>

// Introduce más librerías si son necesarias
using namespace std;

class academia_chino {
public:
  void nuevo_estudiante(string dni, int grupo){
    if(alumnos.find(dni) != alumnos.end())
      throw domain_error("Estudiante existente");
    if(grupo < 1 || grupo > 6)
      throw domain_error("Grupo incorrecto");

    grupos[grupo].push_back(dni);
    alumnos[dni] = {grupo, --grupos[grupo].end()};
  }

  void promocionar(string dni){
    if(alumnos.find(dni) == alumnos.end())
      throw domain_error("Estudiante no existente");
    if(graduated.find(dni) != graduated.end())
      throw domain_error("Estudiante ya graduado");

    InfoAlumno &info_alumno = alumnos[dni];
    grupos[info_alumno.nivel].erase(info_alumno.it);
    if(info_alumno.nivel < 6){
      info_alumno.nivel += 1;
      grupos[info_alumno.nivel].push_back(dni);
      info_alumno.it = --grupos[info_alumno.nivel].end();
    }else{
      graduated.insert(dni);
    }
  }

  int grupo_estudiante(string dni){
    if(alumnos.find(dni) == alumnos.end())
      throw domain_error("Estudiante no existente");
    if(graduated.find(dni) != graduated.end())
      throw domain_error("Estudiante ya graduado");
    
    return alumnos[dni].nivel;
  }

  list<string> graduados(){
    list<string> graduados;
    for(string alumno : graduated){
      graduados.push_back(alumno);
    }

    return graduados;
  }

  string novato(int grupo){
    if(grupo < 1 || grupo > 6)
      throw domain_error("Grupo incorrecto");
    
    if(grupos[grupo].empty())
      throw domain_error("Grupo vacio");

    return grupos[grupo].back();
  }

private:
  struct InfoAlumno
  {
    int nivel;
    list<string>::iterator it;
  };
  
  unordered_map<int, list<string>> grupos;
  unordered_map<string, InfoAlumno> alumnos;
  set<string> graduated;
};

bool tratar_caso() {
  academia_chino ac;
  string comando;
  cin >> comando;
  if (cin.eof()) return false;

  while (comando != "FIN") {
    try {
      if (comando == "nuevo_estudiante") {
        string dni;
        int grupo;
        cin >> dni >> grupo;
        ac.nuevo_estudiante(dni, grupo);
      } else if (comando == "grupo_estudiante") {
        string dni;
        cin >> dni;
        int grupo = ac.grupo_estudiante(dni);
        cout << dni << " esta en el grupo " << grupo << "\n";
      } else if (comando == "promocionar") {
        string dni;
        cin >> dni;
        ac.promocionar(dni);
      } else if (comando == "graduados") {
        list<string> graduados = ac.graduados();
        cout << "Lista de graduados:";
        for (const string &s: graduados) {
          cout << " " << s;
        }
        cout << "\n";
      } else if (comando == "novato") {
        int grupo;
        cin >> grupo;
        string novato = ac.novato(grupo);
        cout << "Novato de " << grupo << ": " << novato << "\n";
      }
    } catch (std::domain_error &e) {
      cout << "ERROR: " << e.what() << "\n";
    }

    cin >> comando;
  }
  cout << "---\n";
  
  return true;
} // tratar_caso

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}