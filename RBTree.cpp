#include <iostream>

using namespace std;

#define NEGRO 0 // Definimos macros
#define ROJO 1

typedef struct NodoRB {
    int info; // Donde se almacena el valor
    NodoRB *padre; // Puntero a nodo padre
    NodoRB *izq; // Puntero a nodo del hijo izquierdo
    NodoRB *der; // Puntero a nodo del hijo derecho
    int color; // Donde guardamos el color
} NodoRB;

class RBTree { // Clase que representa a los arboles rojo-negro

    /*
    Los arboles rojo-negro son arboles de busqueda binaria, los cuales adicionalmente cumplen otros invariantes.
    Estos invariantes son los siguientes:
        1) Cada nodo del arbol es de color ROJO o NEGRO
        2) La raiz del arbol siempre es de color NEGRO
        3) Las hojas del arbol siempre son de color NEGRO tambien
        4) Si un nodo es ROJO, entonces sus hijos son NEGRO.
        5) Todo camino desde la raiz a una hoja tiene la misma cantidad de nodos NEGRO.
    Gracias a todos los invariantes anteriores, especialmente el 5, el arbol se mantiene balanceado y logra altura O(logn)
    */


    private: // Campos y metodos privados

        void rotacion_derecha(NodoRB *y) { // Rotacion hacia la derecha, con y padre de x
            if(y->izq == nullptr) { // Caso intento de rotar en una hoja
                cout << "No se puede realizar una rotacion a una hoja" << "\n";
                return;
            }

            NodoRB *x = y->izq; // x, hijo izq de y
            
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

        void rotacion_izquierda(NodoRB *y) { // Rotacion hacia la izquierda
            if(y->der == nullptr) { // Caso intento de rotar en una hoja
                cout << "No se puede realizar una rotacion a una hoja" << "\n";
                return;
            }

            NodoRB *x = y->der; // x, hijo derecho de y

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

        void balancear(NodoRB *x) { // Metodo que se encargara de balancear el arbol tras una insercion
            ; // Implementation 
        }

    public: //
        NodoRB *root; // raiz del arbol rojo-negro

        RBTree() { // Constructor
            this->root = nullptr; // Inicialmente la raiz es vacia 
        }

        
        void insert(int valor) { // Inserta un elemento en el arbol, se deben seguir cumpliendo los invariantes tras una insercion exitosa
            ; // Implementation
        }

        NodoRB *search(int valor) { // Busca un elemento en el arbol
            if(this->root == nullptr) // Arbol vacio, no esta el elemento
                return nullptr;

            NodoRB *actual = this->root; // Obtenemos la raiz
            while(actual != nullptr) { // Iteramos hasta llegar a una hoja o encontrar el valor
                if(actual->info < valor) { // Nos vamos por el hijo derecho
                    actual = actual->der;
                } else if(actual->info > valor) { // Nos vamos por el hijo izquierdo
                    actual = actual->izq;
                } else { // Encontramos al valor
                    return actual;
                }
            }
            return nullptr; // No encontramos al valor
        }
};