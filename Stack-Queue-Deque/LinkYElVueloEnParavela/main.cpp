#include <iostream>
#include <fstream>
#include "stack_linkedlist.h"
#include "queue_linkedlist.h"
// Introduce más librerías si son necesarias
using namespace std;

// función que resuelve el problema
void resolver(QueueLinkedList<int> datos) {
   StackLinkedList<int> pilares;
   
   cout << "NO HAY\n";
   pilares.push(datos.front());
   datos.pop();
   bool encontrado = false;
   while(!datos.empty()){
      while(!pilares.empty() && !encontrado){
         if(datos.front() < pilares.top()){
            cout << pilares.top() <<'\n';
            pilares.push(datos.front());
            encontrado = true;
         }else{
            pilares.pop();
         }
      }
      if(pilares.empty()){
         cout << "NO HAY\n";
         pilares.push(datos.front());
      }
      encontrado = false;
      datos.pop();
   }

   cout << "---\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int elem; cin >> elem;
   if (elem == -1)
      return false;
   
   QueueLinkedList<int> cola;
   while(elem != -1){
      cola.push(elem);
      cin >> elem;
   }

   // escribir sol
   resolver(cola);

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