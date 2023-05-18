#include <iostream>

using namespace std;

struct Node {
    int data; // Donde se almacena el valor
    Node *parent; // Puntero a nodo padre
    Node *left; // Puntero a nodo del hijo izquierdo
    Node *right; // Puntero a nodo del hijo derecho
}