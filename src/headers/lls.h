/*
 * Este archivo fue creado por Rafael Morales para la asignatura Estructura de
 * Datos S1-2023. Su uso es publico y abierto para cualquiera que quiera
 * utilizarlo, y esta cubierto por la licencia GPL V3. En caso de no recibir una
 * copia de esta licencia junto con este programa, puedes verla en
 * <hhtps://www.gnu.org/licenses/>.
 */

#include <iostream>

#ifndef NODO
#define NODO

/**
 * Estructura base para la lista enlazada. Contiene un tipo de dato T, y un
 * puntero al siguiente elemento de la lista.
 */
template <typename T> struct Nodo {
  T dato;
  Nodo *next;
};

/**
 * Crea un nuevo nodo.
 *
 * Esta funcion crea un nuevo nodo en el heap, lo puebla con un valor `dato`, y
 * un puntero nulo.
 *
 * @params dato El valor a ser contenido por el nodo.
 * @return Un puntero hacia un nuevo nodo.
 */
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
  size_t length;

public:
  /*
   * Constructor default.
   *
   * Inicializa la lista con una cabeza nula, y un largo de 0.
   */
  ListaEnlazada() : head(nullptr), length(0) {}

  /*
   * Constructor con dato inicial
   *
   * Inicializa la lista con el dato provisto y un largo 1.
   */
  ListaEnlazada(T dato) {
    this->length = 1;
    this->head = crear_nodo(dato);
  }

  /*
   * Constructor a partir de un nodo.
   *
   * Utilizado principalmente por la funcion `separar`, crear una lista via el
   * nodo provisto, y luego recorre los punteros que estos tengan para
   * determinar el largo de la lista.
   */
  ListaEnlazada(Nodo<T> *node) {
    this->head = node;
    this->length = 0;

    while (node != nullptr) {
      this->length++;
      node = node->next;
    }
  }

  /*
   * Constructor via Arreglo
   *
   * A partir de un arreglo definido, inicia una lista enlazada.
   *
   * @param datos[] Un arreglo con los datos a agregar.
   * @param largo El largo del arreglo a agregar.
   */
  ListaEnlazada(T datos[], size_t largo) {
    this->head = nullptr;
    this->length = 0;

    for (size_t i = 0; i < largo; i++) {
      // Se agregan 'al reves', para mantener el orden.
      this->agregarFrente(datos[largo - i - 1]);
    }
  }

  /*
   * Constructor via listas
   *
   * Permite pasar valores {T1, T2, ..., Tn} directo a la funcion como
   * argumento, en vez de tener que asignarlos primero a una variable
   * Esto probablemente tiene complejidad O(N^2)! por lo que mantenlo a listas
   * pequeños.
   */
  ListaEnlazada(const std::initializer_list<T> &datos) {
    this->head = nullptr;
    this->length = 0;

    for (auto e : datos) {
      this->agregarAtras(e);
    }
  }

  /*
   * Agrega un valor al inicio de la lista
   *
   * Esto tiene complejidad O(1), y es la forma mas directa y rapida de agregar
   * un elemento a la lista.
   *
   * @param dato El elemento a agregar
   */
  void agregarFrente(T dato) {
    auto aux = crear_nodo(dato);

    aux->next = this->head;
    this->head = aux;
    this->length++;
  }

  /*
   * Agrega un valor al fianl de la lista
   *
   * Esto tiene complejidad O(n), pues requiere recorrer toda la lista antes de
   * poder incluir el dato
   *
   * @param dato El elemento a agregar
   */
  void agregarAtras(T dato) {
    // Si no hay elementos en la lista, se inicia una lista nueva
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

  /*
   * Elimina un elemento `n` de la lista.
   *
   * Tiene 4 casos a considerar:
   * - Si la lista esta vacia, o la posicion solicitada no es valida, no hace
   * nada.
   * - Si la posicion es 0, actua similar al `pop` de una pila.
   * - Si la posicion es la ultima, debe recorrerse todo el arreglo.
   * - Si la posicion es cualquier otra, se debe jugar con los punteros de los
   * nodos para poder lograr remover el nodo solicitado exitosamente.
   *
   * Se sugiere encarecidamente que lean la implementacion! pues es la mas
   * dificil de lograr en las listas enlazadas.
   *
   * @param posicion La posicion del elemento a eliminar, considerando 0 como
   * el primer elemento.
   */
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

  /// @return true si esta vacia, false en caso contrario.
  inline bool vacio() { return this->length == 0; }

  /// @return la cantidad de elementos de la lista.
  inline size_t largo() { return this->length; }

  /*
   * Vacia la lista y libera todos los elementos de la memoria.
   */
  void vaciar() {
    while (this->head != nullptr) {
      auto aux = this->head;
      this->head = aux->next;
      free(aux);
    }

    this->length = 0;
  }

  /*
   * Entrega un puntero al primer valor de la lista
   *
   * Debido a que la lista puede estar vacia, se entrega un puntero al valor, y
   * no el valor mismo, con el proposito de que se verifique si el puntero no es
   * nulo!
   *
   * @return puntero al primer valor, nullptr si la lista esta vacia.
   */
  T *frente() {
    if (this->head == nullptr) {
      return nullptr;
    }

    return &(this->head->dato);
  }

  /*
   * Entrega el dato del primer nodo.
   *
   * Esta funcion puede producir un segfault si la lista esta vacia, pues
   * intentaria acceder al valor de un puntero nulo! por lo que solo utilizada
   * si estas revisando activamente que la lista sigue conteniendo elementos.
   *
   * @returns el valor del primer elemento.
   */
  inline T unsafe_front() { return this->head->dato; }

  /*
   * Separa la lista en dos en la posicion n.
   *
   * Si la posicion n es 0, crea una nueva lista, y vacia la lista que llama
   * esta funcion. En caso contrario, corta la lista que llama en la posicion
   * `posicion - 1`, y crea una nueva lista con los nodos restantes. Si la
   * posicion solicitada es mayor a la cantidad de elementos (o es invalida),
   * crea una lista vacia, sin alterar la lista original.
   */
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

  /// Imprime la lista en el output estandar.
  void ver() {
    if (this->length == 0) {
      std::cout << "[]" << std::endl;
      return;
    }

    std::cout << "[" << std::endl;
    Nodo<T> *aux = head;
    size_t cont = 0;
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
