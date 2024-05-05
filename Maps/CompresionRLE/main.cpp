#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

int toPosition(int x, int y, int W){
  return (y - 1) * W + x;
}

bool tratar_caso() {
  int W, H; cin >> W >> H;
  if(W == 0 && H == 0){
    return false;
  }
  map<int, string> pcx;
  
  int N; cin >> N; 
  int longitud, sum = 0;
  string color;
  while(N--){
    cin >> longitud >> color;
    sum += longitud;
    pcx.insert({sum, color});
  }

  int C, x , y; cin >> C;
  while(C--){
    cin >> x >> y;
    int posicion = toPosition(x, y, W);
    auto it = pcx.lower_bound(posicion);
    cout << it->second << '\n';
  }

  cout << "---\n";

  return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
