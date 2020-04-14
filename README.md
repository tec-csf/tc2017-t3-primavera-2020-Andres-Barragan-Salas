# Tarea *3*. *Técnicas de Diseño de Algoritmos*

---

##### Integrantes:
1. *Andrés Barragán Salas* - *A01026567* - *CSF*


---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución

#### Los subconjuntos de suma dada
La pregunta 4 nos presenta el siguiente problema: *Sea W un conjunto de enteros no negativos y M un número entero positivo. El problema consiste en diseñar un algoritmo para encontrar todos los posibles subconjuntos de W cuya suma sea exactamente M*. Basándonos en la información anterior sabemos que el resultado que debe presentado es un conjunto de *n-tuplas* con las cuales se exprese cada uno de los posibles resultados. Además, al buscar todos los subconjuntos que cumplan cierta característica dentro de un conjunto *W* más grande estamos hablando de un recorrido en profundidad de todas las posibles combinaciones que se generan a partir de los elementos de *W*. Por las razones anteriores está claro que el algoritmo que resolverá el problema es de *Vuelta atrás* o *Backtracking*. Con un algoritmo de dicha naturaleza se recorrerán todos los subconjuntos del conjunto presentado a manera de un árbol en profundidad (tomando cada una de sus opciones como posibles ramificaciones de dicho árbol), determinando su suma al ir avanzando e imprimiendo el subconjunto actual si es que se encuentra una solución. Para optimizar el algoritmo y evitar recorridos innecesarios el subconjunto *W* deberá estar ordenado ascendentemente, de manera que si en una actual ramificación el número en cuestión sobrepasa la suma *M* buscada este regrese para continuar por otro camino. 

Dentro del código con la implementación la función principal se llama “*subconjuntosAux*” y para su llamada recursiva, en cualquiera de los casos, la variable que se ve modificada es el índice *i* actual del elemento del arreglo (conjunto) que se está analizando, esta variable siempre se incrementa en uno. De esta manera, a pesar de que realmente no se está reduciendo el número de elementos en el conjunto, siempre se recorre un elemento menos en cada llamada recursiva. Por esta razón, para el análisis de la complejidad de este código se establece que en cada llamada recursiva la cantidad de elementos se reduce en uno, siendo *T(n-1)* y la condición de parada cuando *n = 0* o *T(0)* lo cual se cumple cuando *i = n* o el índice es igual al número de elementos en el arreglo y por tanto su análisis a llegado a una conclusión.  En cuanquiera de los casos, si es que el subconjunto actual representa una solución, imprimirá dicho subconjunto y dejará de recorrer las siguientes posibilidades de esa ramificación, pero el algoritmo no se detendrá ahí, si no que continuará con el resto de las posibilidades. 

La complejidad del algoritmo recién explicado es de **O(n)=2<sup>n</sup>**, cuyo análisis completo esta detallado a profundidad en el archivo *TC_T3_AndresBarraganSalas* ubicado en la carpeta raíz de este repositorio.


#### Algoritmo de strassen
La pregunta 7 nos presenta el siguiente problema: *Si se desea implementar el algoritmo de Strassen para multiplicar dos matrices*. Para encontrar un algoritmo apto para implementar aquel de Strassen es importante primero entender el analizar el algoritmo de Strassen mismo. El algoritmo de Strassen sirve para la multiplicación de matrices cuadradas de orden *n*x*n* cuando *n* es una potencia de 2, al tener una de estas matrices, el algoritmo se encarga de dividirla en cuatro matrices de orden (*n/2*)x(*n/2*) y realizar 7 multiplicaciones a partir de las 4 submatrices (aumentando cantidad de sumas requeridas) sustituyendo las usuales 8 multiplicaciones realizadas y por tanto reduciendo la complejidad normal de *n<sup>3</sup>*. Para realizar las multiplicaciones si hace uso de las siguientes formulas tomando en cuenta dos matrices *a* y *b*:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>1</sub>=(a<sub>12</sub>-a<sub>22</sub>)(b<sub>21</sub>+b<sub>22</sub>)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>2</sub>=(a<sub>11</sub>+a<sub>22</sub>)(b<sub>11</sub>+b<sub>22</sub>)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>3</sub>=(a<sub>11</sub>-a<sub>21</sub>)(b<sub>11</sub>+b<sub>12</sub>)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>4</sub>=(a<sub>11</sub>+a<sub>12</sub>)b<sub>22</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>5</sub>=a<sub>11</sub>(b<sub>12</sub>-b<sub>22</sub>)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>6</sub>=a<sub>22</sub>(b<sub>21</sub>-b<sub>11</sub>)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;m<sub>7</sub>=(a<sub>21</sub>+a<sub>22</sub>)b<sub>11</sub>  

Y a partir de los valores anteriores se realizan las siguientes sumas para agrupar en las posiciones de una matriz resultante *c*:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c<sub>11</sub>=m<sub>1</sub>+m<sub>2</sub>-m<sub>4</sub>+m<sub>6</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c<sub>12</sub>=m<sub>4</sub>+m<sub>5</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c<sub>21</sub>=m<sub>6</sub>+m<sub>7</sub>  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c<sub>22</sub>=m<sub>2</sub>-m<sub>3</sub>+m<sub>5</sub>-m<sub>7</sub>  

Todos los valores anteriormente expresados son submatrices de las matrices *A*, *B*, y *C*, y al estar reduciendo una matriz con un orden igual a una potencia de 2 en 4 submatrices eventualmente se llegará a matrices de orden *1*x*1*, en donde la operación a realizar será una simple multiplicación.

Al entender el funcionamiento del algoritmo de Strassen y saber que el problema se divide en 4 partes iguales con cada recursión del mismo es fácil distinguir que se trata de un algoritmo de *divide y vencerás*. Con un algoritmo de dicha naturaleza se utilizarán llamadas recursivas para analizar en cada recursión una cuarta parte de las matrices originales y al llegar al caso base, multiplicar e ir combinando los resultados hasta regresar al tamaño de las matrices originales.

Dentro del código con la implementación la función principal se llama “*strassen*” y para su llamada recursiva las variables que se modifican son las posiciones dentro las matrices para un análisis individual de sus secciones (en las posiciones *0*, *N/2* y *N*) utilizando las propiedades de apuntadores para cambiar el índice inicial de *i* y un número entero para modificar aquel de *j*. De esta manera, se reduce cada vez el orden de las matrices de *N*x*N* a (*N/2*)x(*N/2*) y eventualmente esta reducción nos llevará al caso base donde *N = 1*, y siendo esta una matriz de 1 elemento. Entonces, la operación efectuada será una simple multiplicación y a partir de ella los resultados obtenidos serán combinados en cada paso de las llamadas recursivas hasta regresar a las matrices originales. Existen secciones del código para  la declaración de matrices cuadradas como apuntadores a apuntadores que son necesarias para que la función pueda  recibir matrices de cualquier orden dado a pesar de que estas lineas de código utilizan varias operaciones elementales, pero por el momento no he podido encontrar una mejor manera de declarar dichas variables. De igual manera este tipo de declaración debe de ser utilizado en el main para poder mandar matrices de tipo *int\*\**.  

La complejidad del algoritmo recién explicado es de **O(n)=n<sup>2.807</sup>**, cuyo análisis completo esta detallado a profundidad en el archivo *TC_T3_AndresBarraganSalas* ubicado en la carpeta raíz de este repositorio.

### 2.1 Pasos a seguir para utilizar la aplicación
Lo primero que se debe realizar para utilizar las clases implementadas es clonar el repositorio de *GitHub*, para realizar dicha acción, el usuario se deberá colocar en el directorio donde desea almacenar el repositorio y ahí deberá llamar el siguiente comando:

    $ git clone https://github.com/tec-csf/tc2017-t3-primavera-2020-Andres-Barragan-Salas.git

Una vez clonado el repositorio, el usuario deberá ingresar a él, utilizando el siguiente comando:

    $ cd tc2017-t3-primavera-2020-Andres-Barragan-Salas

Al estar dentro del repositorio, lo único que falta por hacer es compilar los archivos utilizados y ejecutar el *main* (el cual contiene algunos ejemplos que pueden ser utilizados y sirve de guía para reemplazarlos por nuevos), con los siguientes dos comandos:

    $ g++ sources/main.cpp sources/Strassen.cpp sources/SubconjuntosSuma.cpp

    $ ./a.out

---
Si es que se desea observar el funcionamiento de cada algoritmo por separado, se recomienda acceder a los codigos en la carpeta *examples* corriendo cada una de las clases por separado (en este caso ya contienen su propio *main*). Para ver el funcionamiento del algoritmo de **subconjuntos de una suma dada** se correrían lo siguientes comandos:

    $ g++ example/SubconjuntosSuma_ejemplo.cpp

    $ ./a.out

Y para ver el funcionamiento del **algoritmo de Strassen** se correrían los siguientes comandos:

    $ g++ example/Strassen_ejemplo.cpp

    $ ./a.out

## 3. Referencias

\[1\] Guerequeta, R., Vallecido, A. (1998) “Técnicas de Diseño de Algoritmos” \[PDF\] Servicio de Publicaciones de la Universidad de Malaga. Obtenido de: http://www.lcc.uma.es/~av/Libro/  
\[2\] Cubells, V. (2020). “Complejidad y Notación Asintótica” \[Power Point\] (Presentación de Clase).  
\[3\] Cubells, V. (2020). “Análisis de Algoritmos Recursivos” \[Power Point\] (Presentación de Clase).