#include <iostream>

using namespace std;

typedef struct Nodo {
    int info; // Donde se almacena el valor
    Nodo *padre; // Puntero a nodo padre
    Nodo *izq; // Puntero a nodo del hijo izquierdo
    Nodo *der; // Puntero a nodo del hijo derecho
} Nodo;

class SplayTree {
    private: // Campos y metodos privados del splayTree
        Nodo *root; // Raiz del splayTree

    void rotacion_derecha(Nodo *y) { // Rotacion hacia la derecha, con y padre de x
        if(y->izq == nullptr) { // Caso intento de rotar en una hoja
            cout << "No se puede realizar una rotacion a una hoja" << "\n";
            return;
        }

        Nodo *x = y->izq; // x, hijo izq de y
        
        // Actualizamos al padre de y, el cual ahora tendra como uno de sus hijos a x
        if(y->padre == nullptr) { // Caso en que y es la raiz
            root = x;
        } else if(y->padre->izq == y) { // y es hijo izquierdo de un nodo
            y->padre->izq = x;
        } else { // y es hijo derecho de un nodo
            y->padre->der = x;
        }

        // El hijo derecho de x ahora sera el hijo izquierdo de y
        if(x->der != nullptr) {
            x->der->padre = y;
        }

        // Actualizamos x e y
        y->izq = x->der; // Hijo izquierdo de y es el hijo derecho de x
        x->padre = y->padre; // El padre de x es ahora el padre de y
        y->padre = x; // y ahora tiene como padre a x
        x->der = y; // hijo derecho de x es ahora y
    }

    void rotacion_izquierda(Nodo *y) { // Rotacion hacia la izquierda
        if(y->der == nullptr) { // Caso intento de rotar en una hoja
            cout << "No se puede realizar una rotacion a una hoja" << "\n";
            return;
        }
        
        Nodo *x = y->der; // x, hijo derecho de y

        // Actualizamos al padre de y, el cual ahora tendra como uno de sus hijos a x
        if(y->padre == nullptr) { // Caso en que y es la raiz
            root = x;
        } else if(y->padre->izq == y) { // y es hijo izquierdo de un nodo
            y->padre->izq = x;
        } else { // y es hijo derecho de un nodo
            y->padre->der = x;
        }

        // El hijo izquierdo de x ahora sera el hijo derecho de y
        if(x->izq != nullptr) {
            x->izq->padre = y;
        }

        // Actualizamos x e y
        y->der = x->izq; // Hijo derecho de y es el hijo izquierdo de x
        x->padre = y->padre; // El padre de x es ahora el padre de y
        y->padre = x; // y ahora tiene como padre a x
        x->izq = y; // hijo izquierdo de x es ahora y
    }

    void splay(Nodo *x) {
        ; // Implementation
    }
    public: // Campos y metodos publicos del splayTree
        SplayTree() { // Constructor
            root = nullptr;
        }
    void insert(int valor) {
        
        ; // Implementation
    }
    void search(int valor) {
        ; // Implementation
    }
};

