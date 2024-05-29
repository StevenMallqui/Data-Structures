#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stack_linkedlist.h"
#include "dequeue.h"

// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
Dequeue<string> resolver(string line) {
   string word;
   istringstream iss(line);
   Dequeue<string> frase; 
   StackLinkedList<string> descartes, acciones;

   while(iss >> word){
      if(word == "+"){
         if(!acciones.empty()){
            if(acciones.top() == "."){
               if(!frase.empty()) frase.pop_back();
            }else if(acciones.top() == "*"){
               if(!descartes.empty()){
                  frase.push_back(descartes.top());
                  descartes.pop();
               }
            }
            acciones.pop();
         }
      }else if(word == "*"){
         if(!frase.empty()){
            acciones.push(word);
            descartes.push(frase.back());
            frase.pop_back();
         }
      }else{
         frase.push_back(word);
         acciones.push(".");
      }
   }

   return frase;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   string line;
   getline(cin, line);
 
   Dequeue<string> frase;
   // escribir solución
   frase = resolver(line);

   frase.write(cout);
   cout << '\n';
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   cin.ignore();
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}