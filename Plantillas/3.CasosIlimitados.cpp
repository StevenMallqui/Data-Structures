
// Autor/a: Nombre y apellidos

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
Solucion resolver(Datos datos) {
   
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   Solucion sol = resolver(datos);
   
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}