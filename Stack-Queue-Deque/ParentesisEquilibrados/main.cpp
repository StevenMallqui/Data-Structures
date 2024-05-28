#include <iostream>
#include <fstream>
#include <string>
#include "stack_linkedlist.h"

// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   string linea;
   getline(cin, linea);
   if (!std::cin)  // fin de la entrada
      return false;
   
   StackLinkedList<char> pila;
   int abiertos = 0, cerrados = 0;
   for(char c : linea){
      if(c == '{' || c == '(' || c == '['){
         pila.push(c);
         abiertos++;
      }else if(c == '}' || c == ')' || c == ']'){
         cerrados++;
      }

      if(!pila.empty()){
         if((pila.top() == '(' && c == ')') || (pila.top() == '{' && c == '}') || (pila.top() == '[' && c == ']')){
            pila.pop();
            abiertos--;
            cerrados--;
         }
      }
   }

   // escribir sol
   if(abiertos + cerrados == 0)
      cout << "SI\n";
   else
      cout << "NO\n";
   
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
#endif
   return 0;
}