#include <iostream>

using namespace std;

typedef struct Nodo {
    int data; // Donde se almacena el valor
    Node *parent; // Puntero a nodo padre
    Node *left; // Puntero a nodo del hijo izquierdo
    Node *right; // Puntero a nodo del hijo derecho
} Node;

class SplayTree {
    private: // Campos y metodos privados del splayTree
        Node *root;

    void zigzag(Node *x) { // x es hijo derecho de un nodo y, luego tal nodo y es hijo izquierdo de un nodo z
        Node *y = x->parent; // Padre
        Node *z = y->parent; // Abuelo
        Node *B = x->left; // Hijo izq de x
        Node *C = x->right; // Hijo der de x
        x->left = y; // Asignamos los hijos nuevos de x
        x->right = z; 
        y->right = B; // El nuevo hijo derecho de y es ahora B
        z->left = C; // El hijo izquierdo de z es ahora C
        y->parent = x; // El padre de y es ahora x
        if(z->parent == root) { // Puede ser que z haya sido la raiz
            x->parent = nullptr; // Padre de x es nulo
            root = x; // x es ahora la raiz
        } else { // Caso en que z no es la raiz
            x->parent = z->parent; // Padre de x es ahora el padre de z
        }
        z->parent = x; // Padre de z es x
    }
    void zagzig(Node *x) { // x es hijo izquierdo de un nodo y, luego tal nodo y es hijo derecho de un nodo z
        Node *y = x->parent; // Padre
        Node *z = y->parent; // Abuelo
        
    }
    void zigzig(Node *x) { // x es hijo izquierdo de un nodo y, luego tal nodo y es tambien hijo izquierdo de un nodo z
        Node *y = x->parent; // Padre
        Node *z = y->parent; // Abuelo
    }   
    void zagzag(Node *x) { // x es hijo derecho de un nodo y, luego tal nodo y es tambien hijo derecho de un nodo z
        Node *y = x->parent; // Padre
        Node *z = y->parent; // Abuelo
    }
    void zig(Node *x) { // Caso que root sea hijo izq de la raiz
        Node *y = x->parent; // Padre de x
        y->left = x->right; // Hijo izq de y ahora es el hijo derecho de x
        x->right = y; // Hijo derecho de x es ahora y
        y->parent = x; // Padre de y ahora es x
        x->parent = nullptr; // x es ahora la raiz, no tiene padre
        root = x;
    }
    void zag(Node *x) { // Caso root es hijo derecho de la raiz
        Node *y = x->parent; // Padre de x
        y->right = x->left; // hijo izquierdo original de x es el hijo derecho de y
        x->left = y; // Hijo izq de x es ahora y
        y->parent = x; // Padre de y es ahora x
        x->parent = nullptr; // x es ahora la raiz, no tiene padre
        root = x;
    }

    void splay(Node *x) {
        ; // Implementation
    }
    public: // Campos y metodos publicos del splayTree
        SplayTree() { // Constructor
            root = nullptr;
        }
    void insert(int value) {
        ; // Implementation
    }
    void search(int value) {
        ; // Implementation
    }
};

