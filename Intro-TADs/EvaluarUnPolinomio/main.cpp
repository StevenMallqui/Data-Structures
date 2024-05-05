
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include <iostream>
#include <fstream>
using namespace std;
const int MAX_MONOMIOS = 10000;

class Polinomio {

public:
   Polinomio():num_monomios(0){};
   
   void anyadir_monomio(int coef, int exp){
      if(coef != 0 && num_monomios <= MAX_MONOMIOS){
         int index = binarySearch(exp);
         if(index != num_monomios){
            for(int i = num_monomios; i > index; i--){
               monomios[i] = monomios[i - 1];
            }
         }
         monomios[index] = {coef, exp};
         num_monomios++;
      }
   }

   long long int evaluar(int valor){
      long long int respuesta = 0;
      for(int i = 0; i < num_monomios; i++){
         long long int potencia = 1;
         int exponente = monomios[i].exponente;
         int base = valor;

         while (exponente > 0) {
            if (exponente % 2 == 1) {
               potencia *= base;
            }
            base *= base;
            exponente /= 2;
         }

         respuesta += monomios[i].coeficiente * potencia;      
      }
      return respuesta;
   }

private:
   struct Monomio {
      int coeficiente;
      int exponente;
   };
   Monomio monomios[MAX_MONOMIOS];
   int num_monomios;

   int binarySearch(int target) const{
      int low = 0;
      int high = num_monomios - 1;

      while(low <= high){
         int middle = (low + high) / 2;
         if(monomios[middle].exponente == target) 
            return middle;
         else if ( monomios[middle].exponente < target) 
            low = middle + 1;
         else 
            high = middle - 1;
      }

      return low;
   }
};

// función que resuelve el problema
int resolver(Polinomio p, int valor) {
   return p.evaluar(valor); 
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
  // leer los datos de la entrada
  int N, V; cin >> N >> V;
  if (N == 0 && V == 0)
    return false;
  
  int i = 1, coeficiente = 0, exponente = 0;
  Polinomio p;

  while(i <= 2 * N){
   cin >> coeficiente >> exponente;
   p.anyadir_monomio(coeficiente, exponente);
   i += 2;
  }
  
  long long int sol = resolver(p, V);
  
  // escribir sol
  cout << sol << '\n';
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
