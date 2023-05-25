#ifndef NODO
#define NODO

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

template <typename T> struct Nodo {
  T dato;
  Nodo *next;
};

template <typename T> Nodo<T> *crear_nodo(T &dato) {
  Nodo<T> *aux = new Nodo<T>();
  aux->dato = dato;
  aux->next = nullptr;

  return aux;
}

#endif // !NODO
#ifndef LLS
#define LLS
template <typename T> class ListaEnlazada {
protected:
  Nodo<T> *head;
  std::size_t length;

public:
  // Constructor default.
  ListaEnlazada() : head(nullptr), length(0) {}

  // Constructor con dato inicial
  ListaEnlazada(T dato) {
    this->length = 1;
    this->head = crear_nodo(dato);
  }

  ListaEnlazada(Nodo<T> *node) {
    this->head = node;
    this->length = 0;

    while (node != nullptr) {
      this->length++;
      node = node->next;
    }
  }

  // Constructor via arreglo
  ListaEnlazada(T datos[], std::size_t largo) {
    this->head = nullptr;
    this->length = 0;

    for (size_t i = 0; i < largo; i++) {
      // Se agregan 'al reves', para mantener el orden.
      this->agregarFrente(datos[largo - i - 1]);
    }
  }

  // Constructor via listas
  // Permite pasar valores {T1, T2, ..., Tn} directo a la funcion como
  // argumento, en vez de tener que asignarlos primero a una variable
  // Esto probablemente tiene complejidad O(N^2)! por lo que mantenlo a listas
  // pequeños.
  ListaEnlazada(const std::initializer_list<T> &datos) {
    this->head = nullptr;
    this->length = 0;

    for (auto e : datos) {
      this->agregarAtras(e);
    }
  }

  void agregarFrente(T dato) {
    auto aux = crear_nodo(dato);

    aux->next = this->head;
    this->head = aux;
    this->length++;
  }

  void agregarAtras(T dato) {
    if (this->head == nullptr) {
      this->head = crear_nodo(dato);
      this->length++;
      return;
    }

    auto aux = this->head;

    while (aux->next != nullptr) {
      aux = aux->next;
    }

    aux->next = crear_nodo(dato);
    this->length++;
  }

  void remover(size_t posicion) {
    if (posicion < 0 || posicion >= this->length || this->head == nullptr) {
      return;
    }

    auto aux = this->head;
    if (posicion == 0) {
      // Quiero remover el primer nodo
      this->head = aux->next;
      this->length--;
      free(aux);
      return;
    } else if (posicion == this->length) {
      // Quiero remover el ultimo nodo
      size_t cont = 0;
      while (cont < posicion - 1) {
        aux = aux->next;
        cont++;
      }

      free(aux->next);
      aux->next = nullptr;
      this->length--;
    } else {
      // Quiero remover un nodo del medio
      size_t cont = 0;
      while (cont < posicion - 1) {
        aux = aux->next;
        cont++;
      }

      auto to_delete = aux->next;
      aux->next = to_delete->next;
      free(to_delete);
      this->length--;
    }
  }

  bool vacio() { return this->length == 0; }

  std::size_t largo() { return this->length; }

  void vaciar() {
    while (this->head != nullptr) {
      auto aux = this->head;
      this->head = aux->next;
      free(aux);
    }

    this->length = 0;
  }

  // NOTE: Esto entrega un puntero al dato, para poder revisar que no sea nulo.
  T *frente() {
    if (this->head == nullptr) {
      return nullptr;
    }

    return &(this->head->dato);
  }

  // NOTE: Esto entrega el dato en si, pero no revisa que la cabeza sea nula o
  // no, y puede resultar en Segfault.
  T unsafe_front() { return this->head->dato; }

  ListaEnlazada *separar(size_t posicion) {
    if (posicion == 0) {
      // El indice 0 es identico a esta lista, la retorno.
      auto aux = this->head;
      this->head = nullptr;
      this->length = 0;
      return new ListaEnlazada(aux);
    } else if (posicion >= this->length || posicion < 0) {
      // Entrego una lista vacia si me pide un indice mayor al largo, o menor a
      // cero
      return new ListaEnlazada();
    }

    size_t cont = 0;
    auto aux = this->head;
    while (cont != posicion - 1) {
      aux = aux->next;
      cont++;
    }

    auto next_lls_head = aux->next;
    aux->next = nullptr;
    return new ListaEnlazada(next_lls_head);
  }

  void ver() {
    if (this->length == 0) {
      std::cout << "[]" << std::endl;
      return;
    }

    std::cout << "[" << std::endl;
    Nodo<T> *aux = head;
    std::size_t cont = 0;
    while (aux != nullptr) {
      std::cout << "\t" << cont << "| " << aux->dato << std::endl;

      // Avanzo la lista
      aux = aux->next;
      cont++;
    }

    std::cout << "]" << std::endl;
  }
};

#endif // !LLS
