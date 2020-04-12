#include <iostream>
#include <stack> 
#include <algorithm> 
using namespace std;

template <class T>
class SubconjuntosSuma{
    private: 
        stack<T> s; 

        /* Se imprime el contenido dentro de la pila con las posibles soluciones.
         * @param s: La pila que se desea imprimir.
         */
        void printStack(stack <T> s) { 
            while (!s.empty()) { 
                cout << "  " << s.top(); 
                s.pop(); 
            } 
            cout<<endl;
        } 

        /* Se imprime el contenido dentro del arreglo dado.
         * @param array: Arreglo que se desea imprimir.
         * @param size: Tamaño del arreglo a imprimir.
         */
        void printArray(T *array, int size) {
            for (int i=0; i<size; ++i) {
                cout << "  " << array[i]; 
            }
            cout<<endl;
        }

        /* Algoritmo principal para la busqueda de subconjuntos que dan una
         * suma particular. Hace uso de llamadas recursivas para recorrer en 
         * profundidad todas las posibles combinaciones y descartar aquellas 
         * que ya no vale la pena recorrer. El arreglo que recibe debe estar
         * ordenado ascendentemente para su funcionamiento. 
         * @param w: arreglo/conjunto de números a partir de los cuales se buscan subconjuntos que sumen 'm'.
         * @param size: tamaño del arreglo/conjunto dado.
         * @param m: valor buscado como resultado de las sumas de los subconjuntos.
         * @param sol: solución actual (utilizada en llamadas recursivas).
         * @param i: indice actual en el arreglo (utilizado en llamadas recursivas).
         */
        void subconjuntosAux(T *w, int size, T m, T sol, int i){
            s.push(w[i]); //Se añade el número actual a la pila con las soluciones

            if (sol + w[i] == m) { //Caso base, la solución fue encontrada en esta posición
                //Se imprime el subconjunto, se elimina el valor de la pila y sale de esta llamada de la función
                cout<<"\tS: ";
                printStack(s); 
                s.pop();
                return; 
            } else if (i == size || sol + w[i] > m) { //Se ha llegado a la posición final o la suma sobrepasa el valor buscado (ya que está ordenado de forma ascendente)
                //Se elimina el valor de la pila y sale de esta llamada de la función
                s.pop(); 
                return; 
            } else { //En cualquier otro caso sigue la busqueda con el siguiente elemento del arreglo
                subconjuntosAux(w, size, m, sol+w[i], i+1); 
                s.pop();
            }

            if (i != size){ //Al terminar las llamadas recursivas, comienza a iterar sobre la siguiente rama
                subconjuntosAux(w, size, m, sol, i+1); 
            }
        }

    public:
        /* Función auxiliar para facilitar la llamada de la función 
         * "subconjuntosAux". También se encarga de imprimir alguna
         * información sobre el conjunto y valor sobre los cuales se
         * está buscando y de ordenar el arreglo ascendentemente en 
         * caso de que el usuario no lo haga. 
         * @param w: arreglo/conjunto de números a partir de los cuales se buscan subconjuntos que sumen 'm'.
         * @param size: tamaño del arreglo/conjunto dado.
         * @param m: valor buscado como resultado de las sumas de los subconjuntos.
         */
        void subconjuntos(T *w, int size, T m){
            cout<<"Subconjuntos del arreglo: "<<endl; 
            printArray(w, size); 
            cout<<"Con sumatoria igual a "<<m<<":"<<endl; 

            sort(w, w+size); //El arreglo se ordena ascendentemente
            subconjuntosAux(w, size, m, 0, 0);
        }
};

int main(){
    SubconjuntosSuma<int> subs; 
    int arreglo[] = {20, 3, 5, 6, 4, 10, 2}; //Se crea un arreglo de enteros (el cual usualmente debería tener orden ascendente)
    int valorBuscado = 15; //Se establece el valor de sumatoria buscado
    int tamano = sizeof(arreglo)/sizeof(arreglo[0]); //Se obtiene el tamaño del arreglo

    subs.subconjuntos(arreglo, tamano, valorBuscado); //Se busca el valor 15 con la función "subconjuntos"

    return 0; 
}