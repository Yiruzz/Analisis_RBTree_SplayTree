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

void correrDataset(double alpha){
  // Arreglos para guardar los valores de testeo de esta ejecucion
  double csv_splayTiempos[45]; // Arreglo con los tiempos del splayTree
  double csv_splayMySD[18]; // Arreglo con las medias y desviaciones estandar de los tiempos de las busquedas de splayTree
  double csv_RBTiempos[45]; // Lo mismo para el RBTree
  double csv_RBMySD[18];

  for (int N = 16; N <= 24 ; N++){ // Iteramos para todos los n desde 2**16 hasta 2**24
    double data1[5]; // Arreglo que guardara los tiempos obtenido en cada uno de los 5 testeos por cada n para splay tree
    double data2[5]; // Mismo arreglo para el segundo algoritmo que utiliza RBTree

    // Crea una permutacion aleatoria de pi en 1,...N
    int n = pow(2, N); // Calculamos el n de esta iteracion
    int *a = new int[n];
    for (int i = 0; i < n; i++) // Lo inicializamos con valores
      a[i] = i+1;

    mezclarArreglo(a, n); // Conseguimos permutacion aleatoria para inicializar los arboles de manera desordenada
  

    // Creamos el arreglo f que contendra las frecuencias no normalizadas
    long long *f = new long long[n];
    long long SUM = 0; // Valor que guardara la suma de las frecuencias no normalizadas

    for(int i = 0; i < n ; i++) { // Calculamos la frecuencia para cada valor i del arreglo aleatorio
        f[i] = floor(pow(i, alpha));
        SUM+=f[i]; // Calculamos SUM
    }
  
    int *phi = new int[n]; // Creamos el arreglo phi
    int largoArregloNormalizado = 0; // Variable que guardara la cantidad efectiva de elemento, que podra ser un poco mayor a M=2**28
    int M = pow(2,28); // Calculamos M
    for(int i = 0; i < n; i++) { // Inicializamos el arreglo phi que guardara las frecuencias normalizadas de cada valor
        phi[i] = ceil((f[i]*1.0)*((M*1.0)/(SUM*1.0))); // Formula dada por el enunciado  
        largoArregloNormalizado += phi[i]; // Calculamos el largo del arreglo para saber cuanta memoria alocar
    }

    delete[] f; // Ya no necesitamos el arreglo f, eliminamos su memoria asociada

    int *C1 = new int[largoArregloNormalizado]; // Creamos el arreglo C1 que contendra los valores 1,...,N repetidos segun lo obtenido en phi
    int indice = 0; // Variable auxiliar para iterar
    for(int i = 0; i < n; i++) { // Iteramos inicializando el arreglo C1 con el que haremos las busquedas
        for(int j = 0; j < phi[i]; j++) // Debemos repetir phi[i] veces para el valor i-esimo
            C1[indice++] = a[i];
    }

    delete[] phi; // Ya no necesitamos el arreglo phi, liberamos su memoria asociada

    SplayTree splayTree; // Declaramos el splayTree
    RBTree rbTree; // Declaramos el RBTree
    
    for(int j = 0; j < n; j++) { // Inicializamos los arboles con la permutacion aleatoria conseguida
        splayTree.insert(a[j]);
        rbTree.insert(a[j]);
    }

    // Haremos 5 testeos de busqueda para cada arbol
    for(int i = 0; i < 5; i++) { 
        mezclarArreglo(C1, largoArregloNormalizado); // Conseguimos una permutacion aleatoria del arreglo C1

        chrono::duration<double> time; // Declaramos la variable time que guardara lo que demora en ejecutarse un algoritmo

        time = testSearchSplayTree(splayTree, C1, largoArregloNormalizado); // Buscamos los elementos en un splayTree y guardamos cuanto demora
        data1[i] = time.count(); // Guardamos el tiempo que demora en el arreglo respectivo
        csv_splayTiempos[i+5*(N-16)] = time.count(); // Guardamos el tiempo en el arreglo que utilizaremos para exportar los resultados posteriormente

        time = testSearchRBTree(rbTree, C1, largoArregloNormalizado); // Busamos los elementos en el RBTree y guardamos el tiempo que demora
        data2[i] = time.count(); // Guardamos el tiempo que demora en los arreglos que corresponden
        csv_RBTiempos[i+5*(N-16)] = time.count();
    }

    csv_splayMySD[(N-16)*2] = mean(data1); // Calculamos y guardamos la media del splayTree en el arreglo correspondiente 
    csv_splayMySD[(N-16)*2 + 1] = calculateSD(data1); // Calculamos y guardamos la desviacion estandar del SplayTree en el arreglo que corresponde

    csv_RBMySD[(N-16)*2] = mean(data2); // Calculamos y guardamos la media y desviacion estandar del arbol rojo-negro en el arreglo correspondiente 
    csv_RBMySD[(N-16)*2 + 1] = calculateSD(data2);
    
    splayTree.destroy(); // Destruimos ambos arboles, pues el n cambiara
    rbTree.destroy();
    delete[] a; // Liberamos la memoria para el actual n
    delete[] C1;
  }

  // Iteramos printeando los resultados obtenidos en los distintos N
  for(int i = 0; i<9; i++) { // Iteramos para printear los valores correspondientes
    for(int j = 0; j < 5; j++) // Printeamos los valores de los tiempos obtenidos del SplayTree
      cout << csv_splayTiempos[j+5*i] << ",";

    cout << csv_splayMySD[i*2] << ","; // Printeamos la media del SplayTree
    cout << csv_splayMySD[i*2+1] << ","; // Printeamos la desviacion estandar del SplayTree

    for(int j = 0; j < 5; j++) // Hacemos exactamente lo mismo para los tiempos obtenidos en el RBTree
      cout << csv_RBTiempos[j+5*i] << ",";

    cout << csv_RBMySD[i*2] << ",";
    cout << csv_RBMySD[i*2+1] << "\n";
  }
  return; // Finalizamos la ejecucion
}

int main() {
  // Primero printeamos los "heads" del archivo csv
  cout << "SP_t1,SP_t2,SP_t3,SP_t4,SP_t5,SP_Mean,SP_SD,RB_t1,RB_t2,RB_t3,RB_t4,RB_t5,RB_Mean,RB_SD" << "\n";
  correrDataset(0.5); // Ejecutamos para alpha = 0.5
  correrDataset(1); // alpha = 1.0
  correrDataset(1.5); // alpha = 1.5
}