#include <iostream>
using namespace std;

template <class T>
class Strassen{
    private: 
        /* Metodo utilizado para la suma y resta de matrices cuadradas.
         * @param A: Primer matriz a ser considerada en la operación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param a0: Indice de las filas de la primera matriz a partir de la cual se comienza a sumar/restar.
         * @param B: Segunda matric a ser considerada en la operación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param b0: Indice de las filas de la segunda matriz a partir de la cual se comienza a sumar/restar.
         * @param n: Orden de las matrices (cantidad de filas/colummnas). 
         * @param operation: Operación a realizar, ya sea summa ("sum") o resta ("substraction"). 
         */
        T** matrixOperation(T **A, int a0, T **B, int b0, int n, string operation) {
            //Se crea un apuntador a un apuntador para poder almacenar arreglos de 2 dimensiones 
            T **C = new T*[n];
            for (int i = 0; i < n; ++i) 
                C[i] = new int[n];

            //Se realiza una suma o resta de matrices segun sea el caso
            for (int i=0; i<n; ++i) {
                for (int j=0, aj=a0, bj=b0; j<n; ++j, ++aj, ++bj) {
                    if (operation == "sum") {
                        C[i][j] = A[i][aj] + B[i][bj];
                    } else if (operation == "substract"){
                        C[i][j] = A[i][aj] - B[i][bj];
                    } else {
                        cout<<"Missing operation"<<endl; 
                    }
                }    
            }

            return C; 
        }
    
        /* Algoritmo principal, en el se realiza la multiplicación de 2 matrizes cuadradas con un orden
         * igual a una potencia de 2. Se utiliza el algoritmo de Strassen para realizar las operaciones. 
         * @param A: Primer matriz a ser considerada en la multiplicación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param a0: Indice de las filas de la primera matriz a partir de la cual se toma en cuenta una matriz (para ser dividida).
         * @param B: Segunda matric a ser considerada en la multiplicación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param b0: Indice de las filas de la segunda matriz a partir de la cual se toma en cuenta una matriz (para ser dividida).
         * @param n: Orden de las matrices (cantidad de filas/colummnas), forzosamente una potencia de 2. 
         */
        T** strassenAux(T **A, int a0, T **B, int b0, int N){
            //Se establece el número del elementos en las matrices resultantes de la división de matrices (para uso continuo)
            int n = N/2;
            //Se crea un apuntador a un apuntador para poder almacenar arreglos de 2 dimensiones 
            T **C = new T*[N];
            for (int i = 0; i < N; ++i) 
                C[i] = new int[N];
            //Se crean los arreglos en donde serán almacendas las soluciones parciales
            T ***p = new T**[7];
            T ***submatrix = new T**[4];
            for (int i = 0; i < 7; ++i) {
                p[i] = new T*[n];
                submatrix[i] = new T*[n];
                for (int j=0; j < n; ++j){
                    p[i][j] = new int[n];
                    submatrix[i][j] = new int[n];
                }
            }

            if (N==1) { //Caso base, la matriz consta de un elemento
                //Se realiza una multiplicación sencilla y se regresa ese valor
                C[0][0] = A[0][a0]*B[0][b0]; 
                return C;
            } else {
                //Se calculan todas las multiplicaciones necesarias recursivamente como es indicado por el "Algoritmo de Strassen"
                p[0] = strassenAux(A, a0, matrixOperation(B, b0+n, B+n, b0+n, n, "substract"), 0, n); 
                p[1] = strassenAux(matrixOperation(A, a0, A, a0+n, n, "sum"), 0, B+n, b0+n, n);
                p[2] = strassenAux(matrixOperation(A+n, a0, A+n, a0+n, n, "sum"), 0, B, b0, n);
                p[3] = strassenAux(A+n, a0+n, matrixOperation(B+n, b0, B, b0, n, "substract"), 0, n);
                p[4] = strassenAux(matrixOperation(A, a0, A+n, a0+n, n, "sum"), 0, matrixOperation(B, b0, B+n, b0+n, n, "sum"), 0, n);
                p[5] = strassenAux(matrixOperation(A, a0+n, A+n, a0+n, n, "substract"), 0, matrixOperation(B+n, b0, B+n, b0+n, n, "sum"), 0, n);
                p[6] = strassenAux(matrixOperation(A, a0, A+n, a0, n, "substract"), 0, matrixOperation(B, b0, B, b0+n, n, "sum"), 0, n);

                /* Se realizan las sumas correspondientes a cada una de las secciones de la matriz resultante con las operaciones
                 * anteriormente calculadas y siguiendo el algoritmo de Strassen */
                submatrix[0] = matrixOperation(matrixOperation(matrixOperation(p[4], 0, p[3], 0, n, "sum"), 0, p[1], 0, n, "substract"), 0, p[5], 0, n, "sum"); 
                submatrix[1] = matrixOperation(p[0], 0, p[1], 0, n, "sum");
                submatrix[2] = matrixOperation(p[2], 0, p[3], 0, n, "sum");
                submatrix[3] = matrixOperation(matrixOperation(matrixOperation(p[0], 0, p[4], 0, n, "sum"), 0, p[2], 0, n, "substract"), 0, p[6], 0, n, "substract");
            }

            //Se combinan las matrizes resultantes en una sola
            int j0, j1, j2, j3; 
            for (int i=0; i<N; ++i) {
                j0=0, j1=0, j2=0, j3=0; 
                for (int j=0; j<N; ++j) {
                    if (i<n && j<n) {
                        C[i][j] = submatrix[0][i][j0]; 
                        j0++; 
                    } else if (i<n && j>=n) {
                        C[i][j] = submatrix[1][i][j1]; 
                        j1++; 
                    } else if (i>=n && j<n) {
                        C[i][j] = submatrix[2][i-n][j2]; 
                        j2++; 
                    } else if (i>=n && j>=n) {
                        C[i][j] = submatrix[3][i-n][j3]; 
                        j3++; 
                    }
                }
            }

            return C; 
        }
    
    public: 
        /* Se imprime el contenido dentro de una matriz dada.
         * @param matriz: Matriz que se desea imprimir (Arreglo de 2 dimensiones como un apuntador a un apuntador).
         * @param size: Tamaño de la matriz a imprimir.
         */
        void printMatrix(T **matrix, int size){
            for (int i=0; i<size; ++i) {
                cout<<"|";
                for (int j=0; j<size; ++j) {
                    cout<<"  "<<matrix[i][j]<<"\t";
                }
                cout<<"|"<<endl; 
            }
        }

        /* Método axiliar del método "strassenAux", utilizado para evitar uso extra de numeros en las
         * llamadas dentro del método "main". Regresa un apuntador a un apuntador (Arreglo de 2 dimemsiones).
         * @param A: Primer matriz a ser considerada en la multiplicación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param B: Segunda matric a ser considerada en la multiplicación (Arreglo de 2 dimensiones como un apuntador a un apuntador). 
         * @param n: Orden de las matrices (cantidad de filas/colummnas), forzosamente una potencia de 2. 
         */
        T** strassen(T** A, T** B, int n) {
            return strassenAux(A, 0, B, 0, n);
        }
};