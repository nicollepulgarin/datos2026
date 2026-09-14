/*
ctrl l para limpiar terminal
Para compilar:
g++ -o nombre(puede ser el del archivo sin extencion) nombre del archivo con extension ej: $ g++ -o clases clases.cpp 

Para correr:
./nombre del archivo sin extension (ejecutable) ej: ./clases*/
#include <iostream>

using namespace std;

class Point {
private:
  int x;
  int y;
public:
  Point(int px, int py) : x(px), y(py) {}
  void move(int dx, int dy) {
    x = x + dx;
    y = y + dy;
  }
};

int main() {
  Point p(3, 7);
  p.move(1, 1);
}