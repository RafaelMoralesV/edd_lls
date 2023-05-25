#include "headers/lls.h"
#include <iostream>

int main_personas();
int main_ints();

int main() {
  std::cout << "Imprimiendo lista de Numeros!" << std::endl;
  main_ints();

  std::cout << "Imprimiendo lista de personas!" << std::endl;
  main_personas();
}

// Demostracion de como utilizar la lista enlazada.
int main_ints() {
  auto lls = new ListaEnlazada<int>({1, 4, 2, 7, 9});

  std::cout << "Mostrando nueva lista de numeros." << std::endl;
  lls->ver();

  std::cout << "Vamos a quitar el valor en la posicion 1 (valor 4)"
            << std::endl;
  lls->remover(1);
  lls->ver();

  std::cout << "Agregare adelante el valor 34, y atras el valor 35"
            << std::endl;
  lls->agregarFrente(34);
  lls->agregarAtras(35);
  lls->ver();

  std::cout
      << "Voy a separar la lista en dos espacios, a partir de la posicion 2."
      << std::endl;
  auto aux = lls->separar(2);

  std::cout << "Lista 1: " << std::endl;
  lls->ver();

  std::cout << "Lista 2: " << std::endl;
  aux->ver();

  std::cout << "Finalmente, vacio la lista 1." << std::endl;
  lls->vaciar();

  // WARN: Esto produce un Segmentation Fault debido a que la lista esta vacia.
  // Prefiere usar front() y desreferenciar el puntero.
  // lls->unsafe_front();

  std::cout << "Lista 1: " << std::endl;
  lls->ver();

  std::cout << "Lista 2: " << std::endl;
  aux->ver();

  return 0;
}

class Persona {
private:
  std::string nombre;
  unsigned short edad;

public:
  Persona() : nombre(""), edad(0) {}
  Persona(std::string nombre, unsigned short edad)
      : nombre(nombre), edad(edad) {}

  // Necesario para poder imprimir el objeto!
  friend std::ostream &operator<<(std::ostream &os, const Persona &p) {
    os << "Nombre: " << p.nombre << "\tEdad: " << p.edad;
    return os;
  }
};

// Demostracion de que funciona para cualquier tipo de dato
int main_personas() {
  auto marxistas = new ListaEnlazada<Persona>({
      Persona("Karl Marx", 64),
      Persona("Friedrich Engels", 74),
      Persona("Vladimir Lenin", 53),
      Persona("Joseph Stalin", 74),
      Persona("Mao Tse-Tung", 82),
  });

  marxistas->ver();

  return 1;
}
