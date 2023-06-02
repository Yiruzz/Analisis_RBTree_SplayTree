#include <iostream>

using namespace std;

#define NEGRO 0 // Definimos macros
#define ROJO 1

typedef struct NodoRB {
    int info; // Donde se almacena el valor
    NodoRB *padre; // Puntero a nodo padre
    NodoRB *izq; // Puntero a nodo del hijo izquierdo
    NodoRB *der; // Puntero a nodo del hijo derecho
    char color; // Donde guardamos el color
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

        void balanceoMedianteRotacion(NodoRB *x) {
            // Tenemos varios casos segun estemos en un zigzig, zagzag, zigzag o zagzig
            if(x == x->padre->izq && x->padre == x->padre->padre->izq) { // Caso zigzig, se rota a la derecha en el abuelo y el padre con el abuelo cambian sus colores
                x->padre->padre->color = ROJO;
                x->padre->color = NEGRO;
                rotacion_derecha(x->padre->padre);
            } else if(x == x->padre->der && x->padre == x->padre->padre->der) { // Caso zagzag, simetrico a zigzig
                x->padre->padre->color = ROJO;
                x->padre->color = NEGRO;
                rotacion_izquierda(x->padre->padre);
            } else if(x == x->padre->der && x->padre == x->padre->padre->izq) { // Caso zigzag
                rotacion_izquierda(x->padre); // Tras esta rotacion, quedamos en el caso zigzig
                x->color = NEGRO;
                x->padre->color = ROJO;
                rotacion_derecha(x->padre); // Tras rotar a la izquierda, ahora soy el nodo del medio del zigzig. Rotamos por el padre hacia la derecha
            } else { // Caso zagzig, simetrico a zigzag
                rotacion_derecha(x->padre);
                x->color = NEGRO;
                x->padre->color = ROJO;
                rotacion_izquierda(x->padre);
            }
        }

        void balancear(NodoRB *x) { // Metodo que se encargara de balancear el arbol tras una insercion     
            while(x->padre->color == ROJO) { // Solo necesitamos hacer cambios cuando el padre es ROJO, iteramos porque hay casos en los que se debe recheckear la condicion
                NodoRB *tio = (x->padre == x->padre->padre->izq) ? x->padre->padre->der : x->padre->padre->izq;
                if(tio == nullptr) { // Caso en que tio es una hoja, o sea de color NEGRO
                    balanceoMedianteRotacion(x);
                }
                else if(tio->color == ROJO) { // Caso en que el tio es ROJO, cambiamos color al padre, tio y abuelo. Luego checkeamos al abuelo
                    x->padre->color = NEGRO;
                    tio->color = NEGRO;
                    if(x->padre->padre == this->root) { // La raiz no debemos cambiarla nunca a color rojo, en caso de que el abuelo sea la raiz se termina tras los cambios de color
                        return;
                    } 
                    x->padre->padre->color = ROJO; 
                    x = x->padre->padre; // Ahora el abuelo puede estar violando el invariante, se debe checkear denuevo    
                } else { // Caso en que el tio es NEGRO
                    balanceoMedianteRotacion(x);
                }

                if(x->padre == nullptr) return; // x llego a ser la raiz, se cumplen los invariantes pues su padre es nulo
            }
        }

        void destroyTree(NodoRB *nodo) { // Destruimos el arbol recorriendolo en preorden
            if(nodo == nullptr) // Estamos en una hoja
                return;
            destroyTree(nodo->izq); // Destruimos los hijos izquierdos
            destroyTree(nodo->der); // Destruimos los hijos derechos
            delete [] nodo; // Destruimos el nodo
        }

    public: //
        NodoRB *root; // raiz del arbol rojo-negro

        RBTree() { // Constructor
            this->root = nullptr; // Inicialmente la raiz es vacia 
        }

        
        void insert(int valor) { // Inserta un elemento en el arbol, se deben seguir cumpliendo los invariantes tras una insercion exitosa
            NodoRB *nuevoNodo = new NodoRB; // Inicializamos un nuevo nodo
            nuevoNodo->der = nullptr; // Sus hijos seran nulos inicialmente
            nuevoNodo->izq = nullptr;
            nuevoNodo->info = valor;
            nuevoNodo->color = ROJO; // Los nuevos nodos tendran siempre color rojo, en caso de que necesitemos que sea negro se cambiara luego
            if(this->root == nullptr) { // Caso arbol vacio, insertamos en la raiz
                nuevoNodo->color = NEGRO;
                nuevoNodo->padre = nullptr;
                this->root = nuevoNodo;
                return;
            }
            // Insertamos en una hoja
            NodoRB *actual = this->root; // El nodo que estaremos actualizando
            NodoRB *father = nullptr; // El padre de tal nodo, asi cuando llegamos a una hoja, no perdemos la informacion del padre de tal hoja
            while(actual != nullptr) { // Iteramos hasta llegar a una hoja
                father = actual; // Actualizamos el valor del padre
                if(actual->info < valor) { // Nos vamos por el hijo derecho
                    actual = actual->der;
                } else if(actual->info > valor) { // Nos vamos por el hijo izquierdo
                    actual = actual->izq;
                } else { // Insertamos valor ya existente ?
                    cout << "Intento de insercion de valor repetido, no se inserta nada" << "\n";
                    delete nuevoNodo;
                    return;
                }
            }

            // Ahora actual es una hoja y father es su padre
            nuevoNodo->padre = father;
            if(father->info < valor) { // Somos hijo derecho
                father->der = nuevoNodo;
            } else if(father->info > valor) { // Somos hijo izquierdo
                father->izq = nuevoNodo;
            } else { // Insertamos valor ya existente ?
                cout << "Intento de insercion de valor repetido" << "\n";
                delete nuevoNodo;
                return;
            }

            // Finalmente balanceamos el arbol para que siga cumpliendo los invariantes
            balancear(nuevoNodo);
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

    void destroy() { // Function que destruye la totalidad del arbol, es decir libera la memoria asociada a cada nodo
        destroyTree(this->root); // Llamamos a funcion auxiliar recursiva
        this->root = nullptr; // La raiz ahora es nula
    }
};


/*int main() {
    RBTree t;
    t.insert(1);
    cout << t.root->info << endl;
    t.insert(3);
    cout << t.root->info << endl;
    t.insert(2);
    cout << t.root->info << endl;
    t.insert(4);
    cout << t.root->info << endl;
    t.insert(5);
    cout << t.root->info << endl;
    t.insert(6);
    cout << t.root->info << endl;
    t.insert(7);
    cout << t.root->info << endl;
    t.insert(8);
    cout << t.root->info << endl;
    t.insert(9);
    cout << t.root->info << endl;
    t.search(3);
    cout << t.root->info << endl;
    t.search(7);
    cout << t.root->info << endl;
}*/