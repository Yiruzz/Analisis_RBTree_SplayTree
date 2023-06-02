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
        //Nodo *root; // Raiz del splayTree

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

    void splay(Nodo *x) { // La funcion splay deja al nodo x del Splay Tree en su raiz
        while(x != this->root) { // Iteramos hasta dejar al nodo x en la raiz
            if(x->padre == root) { // El padre de x es la raiz, hacemos zig o zag
                if(x == x->padre->izq) { // Caso zig
                    rotacion_derecha(x->padre); // Padre de x pasa a ser su hijo derecho
                } else { // Caso zag
                    rotacion_izquierda(x->padre); // Padre de x pasa a ser su hijo izquierdo
                }
            } else if(x == x->padre->izq && x == x->padre->padre->izq->izq) { // Caso zig-zig
                // Tras esta doble rotacion a la derecha, el abuelo de x pasa a ser el nieto y el padre de x pasa a ser su hijo derecho
                rotacion_derecha(x->padre->padre); // Aplicamos rotacion derecha en el abuelo
                rotacion_derecha(x->padre); // Aplicamos rotacion derecha al padre
            } else if(x == x->padre->der && x == x->padre->padre->izq->der) { // Caso zig-zag
                // Tras esta doble rotacion, el abuelo de x pasa a ser su hijo derecho y su padre su hijo izquierdo
                rotacion_izquierda(x->padre); // Rotamos a la izquierda en el padre, asi x pasa a ser el hijo izquierdo de su abuelo y su padre pasa a ser su hijo izquierdo
                rotacion_derecha(x->padre); // Rotamos a la derecha el padre de x, ahora el hijo derecho de x es su padre
            } else if(x == x->padre->izq && x == x->padre->padre->der->izq) { // Caso zag-zig
                // Tras esta doble rotacion, el abuelo de x pasa a ser su hijo izquierdo y su padre su hijo derecho
                rotacion_derecha(x->padre); // Rotamos a la derecha en el padre, asi x pasa a ser el hijo derecho de su abuelo y su padre pasa a ser su hijo derecho
                rotacion_izquierda(x->padre); // Rotamos a la izquierda el padre de x, ahora el hijo izquierdo de x es su padre 
            } else { // Caso zag-zag
                // Tras esta doble rotacion a la izquierda, el abuelo de x pasa a ser el nieto y el padre de x pasa a ser su hijo izquierdo
                rotacion_izquierda(x->padre->padre); // Aplicamos rotacion derecha en el abuelo
                rotacion_izquierda(x->padre); // Aplicamos rotacion derecha al padre
            }
        }
    }

    void destroyTree(Nodo *nodo) {// Destruimos el arbol recorriendolo en preorden
        if(nodo == nullptr)// Estamos en una hoja
            return;
        destroyTree(nodo->izq); // Destruimos los hijos izquierdos
        destroyTree(nodo->der); // Destruimos los hijos derechos
        delete [] nodo; // Destruimos el nodo
    }

    public: // Campos y metodos publicos del splayTree

        Nodo *root;

        SplayTree() { // Constructor
            root = nullptr;
        }
    
    void insert(int valor) { // Metodo para insertar un nuevo valor a un splayTree, tal valor no debe ya existir en el splayTree
        Nodo *nuevoNodo = new Nodo; // Inicializamos el nuevo nodo a insertar
        nuevoNodo->info = valor;
        nuevoNodo->der = nullptr; // puntero nulo
        nuevoNodo->izq = nullptr; 
        if(this->root == nullptr) { // Caso en que el arbol este vacio
            nuevoNodo->padre = nullptr;
            this->root = nuevoNodo;
            return;
        }
        Nodo *actual = this->root; // El nodo que estaremos actualizando
        Nodo *father = nullptr; // El padre de tal nodo, asi cuando llegamos a una hoja, no perdemos la informacion del padre de tal hoja
        while(actual != nullptr) { // Iteramos hasta llegar a una hoja
            father = actual; // Actualizamos el valor del padre
            if(actual->info < valor) { // Nos vamos por el hijo derecho
                actual = actual->der;
            } else if(actual->info > valor) { // Nos vamos por el hijo izquierdo
                actual = actual->izq;
            } else { // Insertamos valor ya existente ?
                cout << "Intento de insercion de valor repetido, se deja el nodo con el valor en la raiz" << "\n";
                splay(actual); // Dejamos al elemento que intentamos insertar como raiz
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
        
        // Hacemos splay del nuevo nodo (lo dejamos en la raiz)
        splay(nuevoNodo);
    }
    Nodo *search(int valor) { // Funcion para buscar un elemento en el splayTree
        if(this->root == nullptr) // Arbol vacio, no esta el elemento
            return nullptr;


        Nodo *actual = this->root; // Obtenemos la raiz
        Nodo *father = nullptr;

        while(actual != nullptr) { // Iteramos hasta llegar a una hoja o encontrar el valor
            father = actual; // Actualizamos el valor del padre
            if(actual->info < valor) { // Nos vamos por el hijo derecho
                actual = actual->der;
            } else if(actual->info > valor) { // Nos vamos por el hijo izquierdo
                actual = actual->izq;
            } else { // Encontramos al valor
                splay(actual); // Hacemos splay de tal valor
                return actual;
            }
        }
        // Si terminamos la iteracion y no encontramos el valor, estamos en una hoja. Debemos hacer splay del ultimo nodo visitado (father)
        splay(father);
        return nullptr;
    }

    void destroy() { // Function que destruye la totalidad del arbol, es decir libera la memoria asociada a cada nodo
        destroyTree(this->root); // Llamamos a funcion recursiva que ira destruyendo los nodos
        this->root = nullptr; // La raiz es ahora nula
    }
};

int main() {
    SplayTree t;
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
}