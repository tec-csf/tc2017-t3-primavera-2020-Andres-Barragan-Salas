#include <iostream>
#include "Strassen.cpp"
#include "SubconjuntosSuma.cpp"
using namespace std;

int main() {
    /*Se muestra el funcionamiento del algoritmo de buscqueda de subconjuntos con sumatoria igual al valor buscado*/
    cout<<"Funcionamiento del algoritmo de subconjuntos con sumatoria buscada (pregunta 4): "<<endl; 
    cout<<"---------------------------------------------------------------------------------------"<<endl; 
    SubconjuntosSuma<int> subs; 
    int arreglo[] = {16, 5, 32, 10, 2, 6, 20, 4, 8, 9, 1, 3}; //Se crea un arreglo de enteros (el cual usualmente debería tener orden ascendente)
    int valorBuscado = 12; //Se establece el valor de sumatoria buscado
    int tamano = sizeof(arreglo)/sizeof(arreglo[0]); //Se obtiene el tamaño del arreglo

    subs.subconjuntos(arreglo, tamano, valorBuscado); //Se busca el valor 15 con la función "subconjuntos"
    cout<<"\n"<<endl;

    /*Se muestra el funcionamiento del Algoritmo de Strassen*/
    cout<<"Funcionamiento del algoritmo de Strassen (pregunta 7): "<<endl; 
    cout<<"---------------------------------------------------------------------------------------"<<endl; 
    Strassen<int> strassen; 
    int n; 

    //Se crean 2 arreglos bidimensionales 
    n = 2; 
    int a[][2] = {{23, 54}, {5, 19}}; 
    int b[][2] = {{24, 50}, {62, 7}};

    //Se crean 2 apuntadores a apuntadores para almacenar los pasados arreglos bidimensionales
    int **A = new int*[n];
    int **B = new int*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
        B[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            A[i][j] = a[i][j]; 
            B[i][j] = b[i][j]; 
        }
    }

    //Se calcula el resultado de multiplicar las 2 matrices anteriores
    int **R1 = strassen.strassen(A, B, n);
    //Se muestran las matrices utilizadas y el resultado de su multiplicación
    cout<<"Matriz A:"<<endl; 
    strassen.printMatrix(A, n); 
    cout<<"Matriz B:"<<endl; 
    strassen.printMatrix(B, n);
    cout<<"Matriz AxB:"<<endl; 
    strassen.printMatrix(R1, n);  
    cout<<"\n"<<endl;

    //Se crean 2 arreglos bidimensionales, en esta ocasión de orden 4
    n = 4;
    int c[][4] = {{13, 16, 5, 21}, {19, 3, 25, 1}, {32, 14, 37, 24}, {31, 20, 1, 0}}; 
    int d[][4] = {{5, 48, 34, 3}, {6, 15, 5, 14}, {27, 2, 13, 11}, {2, 0, 12, 19}};

    //Se crean 2 apuntadores a apuntadores para almacenar los pasados arreglos bidimensionales
    int **C = new int*[n];
    int **D = new int*[n];
    for (int i = 0; i < n; ++i) {
        C[i] = new int[n];
        D[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            C[i][j] = c[i][j]; 
            D[i][j] = d[i][j]; 
        }
    }

    //Se calcula el resultado de multiplicar las 2 matrices anteriores
    int **R2 = strassen.strassen(C, D, n);
    //Se muestran las matrices utilizadas y el resultado de su multiplicación
    cout<<"Matriz C:"<<endl; 
    strassen.printMatrix(C, n); 
    cout<<"Matriz D:"<<endl; 
    strassen.printMatrix(D, n);
    cout<<"Matriz CxD:"<<endl; 
    strassen.printMatrix(R2, n);  

    return 0; 
}