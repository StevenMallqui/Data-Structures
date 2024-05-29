#include <list>
#include <iostream>
#include <fstream>
using namespace std;

enum class Categoria { Primero=1, Segundo=2, Postre=3 };
struct Plato {
  Categoria categoria;
  string nombre;
};

void ordenar_menu(list<Plato> &platos) {
    auto it = platos.begin(); 
    auto next = platos.begin(); //Apuntará a la posición posterior al último primero procesado
    int size = platos.size();
    Plato aux;

    for (int i = 0; i < size; i++) {
        if (it->categoria == Categoria::Primero) {
            next = platos.insert(next, *it);
            aux = *it;
            it = platos.erase(it);

            if (next != platos.end())
                next++;
            if (it->categoria == aux.categoria && it->nombre == aux.nombre)
                it = next;
        }
        else if (it->categoria == Categoria::Postre) {
            platos.push_back(*it);

            if (it == next && it != platos.end())
                next++;
            it = platos.erase(it);
        }
        else {
            ++it;
        }
    }
}


string enumToString(Categoria c) {
    string res = "";
    if (c == Categoria::Primero) {
        res = "1";
    } else if (c == Categoria::Segundo) {
        res = "2";
    } else {
        res = "P";
    }
    return res;

}
bool resolverCaso() {
    int n;
    cin >> n;
    if (n == 0) {
        return false;
    }
    list<Plato> lista;
    for (int i = 0; i < n; i++) {
        Plato p;
        char c;
        cin >> c;
        switch(c) {
            case '1':
                p.categoria = Categoria::Primero;
                break;
            case '2':
                p.categoria = Categoria::Segundo;
                break;
            default:
                p.categoria = Categoria::Postre;
                break;
        }
        getline(cin, p.nombre); 
        lista.push_back(p);
    }
    ordenar_menu(lista);
    for (Plato p: lista) {
        cout << enumToString(p.categoria) << p.nombre << "\n";
    }
    cout << "---\n";
    return true;
}


int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resolverCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}