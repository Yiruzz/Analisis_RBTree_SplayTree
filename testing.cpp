#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "RBTree.cpp"
#include "splayTree.cpp"

using namespace std;

void mezclarArreglo(int *(&arr), int n) { // Funcion que genera una permutacion aleatoria del arreglo
    random_shuffle(arr, arr+n);
}

// Funcion que ejecutara n busquedas aleatorias en un splayTree y tomara el tiempo que demora
chrono::duration<double> testSearchSplayTree(SplayTree &tree, int *(&arr), int n){
    auto start = chrono::system_clock::now(); // Tomamos el tiempo de ahora
    for(int i = 0; i < n ; i++) // Hacemos n busquedas aleatorias
        tree.search(arr[i]);
        
    auto end = chrono::system_clock::now(); // Calculamos el tiempo denuevo
 
    chrono::duration<double> elapsed_seconds = end-start; // Calculamos el tiempo efectivo que demoro
    return elapsed_seconds; // Retornamos el tiempo que demoro
}

// Funcion que ejecutara n busquedas aleatorias en un RBTree y tomara el tiempo que demora
chrono::duration<double> testSearchRBTree(RBTree &tree, int *(&arr), int n){
    auto start = chrono::system_clock::now(); // Tomamos el tiempo de ahora
    for(int i = 0; i < n ; i++) // Hacemos n busquedas aleatorias
        tree.search(arr[i]);

    auto end = chrono::system_clock::now(); // Calculamos el tiempo denuevo

    chrono::duration<double> elapsed_seconds = end-start; // Calculamos el tiempo efectivo que demoro
    return elapsed_seconds; // Retornamos el tiempo que demoro
}

double mean(double data[]) { // Funcion que calcula el promedio de un arreglo
  double sum = 0.0;
  for(int i = 0; i < 5; ++i)
    sum += data[i]/5;
  return sum;
}

double calculateSD(double data[]) { // Funcion que calcula la desviacion estandar de un arreglo de tamaño 10
  double standardDeviation = 0.0;
  double promedio = mean(data); // Se calcula el promedio

  // Se calcula la desviacion estandar y se retorna tal valor
  for(int i = 0; i < 5; i++)
    standardDeviation += pow(data[i] - promedio, 2);
  return sqrt(standardDeviation / 5);
}

int main() {
  // Arreglos para guardar los valores de testeo de esta ejecucion
  double csv_splayTiempos[45]; // Arreglo con los tiempos del splayTree
  double csv_splayMySD[18]; // Arreglo con las medias y desviaciones estandar de los tiempos de las busquedas de splayTree
  double csv_RBTiempos[45]; // Lo mismo para el RBTree
  double csv_RBMySD[18];

  int size_arr = pow(2,28); // Tamaño del arreglo a utilizar
  int *M = new int[size_arr]; // Creamos un arreglo en memoria dinamica de tamaño n=2**28

  for (int N = 16; N <= 24 ; N++) { // Iteramos para todos los n desde 2**16 hasta 2**24
    double data1[5]; // Arreglo que guardara los tiempos obtenido en cada uno de los 5 testeos por cada n para SplayTree
    double data2[5]; // Mismo arreglo para el segundo algoritmo que utiliza RBTree
    int n = pow(2, N); // Calculamos el n de esta iteracion
    int *a = new int[n]; // Creamos el arreglo a que contendra los valores de 1, ..., n
    for (int i = 0; i < n; i++) { // Lo inicializamos con valores
      a[i] = i+1;
    }
    mezclarArreglo(a, n); // Conseguimos permutacion aleatoria para inicializar los arboles de manera desordenada

    SplayTree splayTree; // Declaramos el splayTree
    RBTree rbTree; // Declaramos el RBTree
     
    for(int j = 0; j < n; j++) { // Inicializamos los arboles con la permutacion aleatoria conseguida
        splayTree.insert(a[j]);
        rbTree.insert(a[j]);
    }

    // Inicializamos el arreglo M que contendra los elementos a buscar, cada valor se debera repetir algunas veces para alcanzar 2**28 valores
    int repetir = pow(2, (28 - N)); // repetir = M/2**N = 2**28/2**N = 2**(28-N) 
    int indice = 0; // Variable auxiliar para inicializar el arreglo
    for(int i = 0; i < n; i++) { // Inicializamos el arreglo
      for(int k = 0; k < repetir; k++) // Cada elemento tiene que aparecer una cantidad repetir de veces para que haya equiprobabilidad y llegar al tamaño 2**28
          M[indice++] = i+1;
    }

    // Haremos 5 testeos de busqueda para cada arbol
    for(int i = 0; i < 5; i++) {
        mezclarArreglo(M, size_arr); // Conseguimos una permutacion aleatoria del arreglo M

        chrono::duration<double> time; // Declaramos la variable time que guardara lo que demora en ejecutarse un algoritmo

        time = testSearchSplayTree(splayTree, M, size_arr); // Buscamos los elementos en un splayTree y guardamos cuanto demora
        data1[i] = time.count(); // Guardamos el tiempo que demora en el arreglo respectivo
        csv_splayTiempos[i+5*(N-16)] = time.count(); // Guardamos el tiempo en el arreglo que utilizaremos para exportar los resultados posteriormente

        time = testSearchRBTree(rbTree, M, size_arr); // Busamos los elementos en el RBTree y guardamos el tiempo que demora
        data2[i] = time.count(); // Guardamos el tiempo que demora en los arreglos que corresponden
        csv_RBTiempos[i+5*(N-16)] = time.count();

    }

    csv_splayMySD[(N-16)*2] = mean(data1); // Calculamos y guardamos la media del algoritmo1 en el arreglo correspondiente 
    csv_splayMySD[(N-16)*2 + 1] = calculateSD(data1); // Calculamos y guardamos la desviacion estandar del algoritmo1 en el arreglo que corresponde

    csv_RBMySD[(N-16)*2] = mean(data2); // Calculamos y guardamos la media y disviacion estandar del algoritmo2 en el arreglo correspondiente 
    csv_RBMySD[(N-16)*2 + 1] = calculateSD(data2);
    
    splayTree.destroy(); // Destruimos ambos arboles, pues el n cambiara
    rbTree.destroy();
    delete[] a; // Liberamos la memoria para el actual n
  }
  delete[] M; // Liberamos la memoria del arreglo de M = 2**28

  // Primero printeamos los "heads" del archivo csv
  cout << "SP_t1,SP_t2,SP_t3,SP_t4,SP_t5,SP_Mean,SP_SD,RB_t1,RB_t2,RB_t3,RB_t4,RB_t5,RB_Mean,RB_SD" << "\n";
  for(int i = 0; i<9; i++) { // Iteramos para printear los valores correspondientes
    for(int j = 0; j < 5; j++)  // Printeamos los valores de los tiempos obtenidos del SplayTree
      cout << csv_splayTiempos[j+5*i] << ",";
    
    cout << csv_splayMySD[i*2] << ","; // Printeamos la media del SplayTree
    cout << csv_splayMySD[i*2+1] << ","; // Printeamos la desviacion estandar del SplayTree

    for(int j = 0; j < 5; j++) // Hacemos exactamente lo mismo para los tiempos obtenidos en el RBTree
      cout << csv_RBTiempos[j+5*i] << ",";
    
    cout << csv_RBMySD[i*2] << ",";
    cout << csv_RBMySD[i*2+1] << "\n";
  }
  return 0; // Finalizamos la ejecucion
}