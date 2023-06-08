# Tarea 2 - Diseño y Análisis de Algoritmos - Análisis amortizado
En esta tarea se analizan los costos amortizados de busquedas para la esctructura de splay trees y de red-black trees. 

En el archivo splayTree.cpp se puede apreciar el código de la estructura correspondientes a los Splay Trees. Tal implementación únicamente admite inserciones, busquedas y destrucciones del árbol en su totalidad. Por otro lado, en el archivo RBTree.cpp se encuentra el código de la estructura Árboles Rojo-Negro. Al igual que los Splay Trees solo admité inserciones, busquedas y destruccion puesto que otras operaciones son innecesarias para efectos de esta tarea. 


En el archivo testing se tomaron los tiempos, para ambos árboles, de $2^{28}$ busquedas donde todos los elementos son equiprobables. Esto se hizo para árboles con elementos desde 1 hasta N, con N variando desde $2^{16}$ hasta $2^{24}$ y con 5 testeos de tiempo para cada N. 
Por otro lado, en el archivo testingSkew se tomaron los tiempos con las mismas consideraciones anteriores, pero en este caso los datos tienen cierta entropía, es decir no tienen equiprobabilidad. Se testeo para un $\alpha$ = 0.5, 1.0 y 1.5. 

Para correr los programas, se utilizó el nivel de optimización -O3. Para compilar debe utilizar los comandos: 

```
g++ -O3 -o test testing.cpp 
g++ -O3 -o testingSkew.cpp 
```
Luego, para ejecutar los archivos de testeo se redirigen los resultados a un csv para poder hacer gráficos de manera más sencilla. Para hacer esto ejecute los ejecutables de la siguiente manera 

```
./testing > resultadosEquiprobables.csv  
./testingSkew > resultadosSkew.csv 
```

Finalmente, en el archivo resultadosEquiprobables.csv se pueden apreciar los tiempo para el testeo con equiprobabilidad en los datos y en resultadosSkew.csv los tiempos para el testeo con entropia en los datos.