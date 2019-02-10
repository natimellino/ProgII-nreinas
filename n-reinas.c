#include <stdio.h>
#include <math.h>

/* TRABAJO PRÁCTICO FINAL: "Las n-reinas"

Observaciones:

1) Ingreso de la cantidad y posiciones de las reinas:
    la cantidad N de reinas y las posiciones de las mismas serán leídas desde un archivo '.txt'.
    en la primera línea del archivo se colocará la cantidad N de reinas, y en las siguientes N
    líneas la fila y columna de cada reina separadas por UN solo espacio. Por ejemplo:

               4   --> Cantidad N de reinas.
      fila <-- 0 0 --> columna
               2 1
               3 3
               1 2

    La entrada anterior nos índica en la primera línea que hay 4 reinas y en las siguientes
    4 líneas está la posición 'fila columna' de cada reina, (primero se escribe la fila y separado
    de un espacio, la columna). De todos modos, hay un archivo adjunto 'ejemploPosiciones' que sirve como 
    ejemplo para ver la forma de indicar la cantidad y posiciones de las reinas.


2) Representación del tablero y de las posiciones:
    Las posiciones de las reinas en el tablero son representadas en una matriz bidimensional 
    de tamaño Nx2. Sea i<N, entonces el elemento de la matriz[i][0], representa el número
    de fila de la reina 'i' y el elemento matriz[i][1] representa el número de columna
    de la reina 'i'. Por ejemplo:

    m[4][2]={{0,0},{2,1},{3,3},{1,2}}

    Siguiendo el ejemplo mencionado en el punto 1) el array 'm' nos dice que tenemos 4 reinas
    y éstas se ubican en las posiciones: ({fila, columna}) {0,0}, {2,1}, {3,3} y {1,2}.

3) Una vez leídas las posiciones desde el archivo, verificamos el tablero con la función 'verificaTablero',
   y mostramos por pantalla un mensaje indicando si la solución propuesta es válida o no.


*/


// verificaTablero: Array Int --> Int
// verificaTablero: recibe un array con las posiciones de las n-reinas en el tablero
// y la cantidad de reinas, devuelve 1 si las reinas no se amenazan entre ellas 
// (esto es si ninguna reina está en la misma fila, columna o diagonal).
// En caso contrario devuelve 0 y muestra por pantalla un mensaje indicando
// cuáles son las reinas que se están amenazando entre sí.

int verificaTablero(int listaPosiciones[17][2], int cantReinas){
    int i=0;
    int verificado=1;
    while(i<cantReinas && verificado==1){
        int j;
        j=i+1;
        while(j<cantReinas && verificado==1){
            if(listaPosiciones[i][0]==listaPosiciones[j][0] || //Verifica si hay dos filas iguales.
                listaPosiciones[i][1]==listaPosiciones[j][1] ||  //Verifica si hay dos columnas iguales.
                fabs(listaPosiciones[i][0]-listaPosiciones[j][0])==fabs(listaPosiciones[i][1]-listaPosiciones[j][1])){ //Verifica que no estén en la misma diagonal

                verificado=0;
                if(listaPosiciones[i][0]==listaPosiciones[j][0]){ // Hay dos reinas en la misma fila.
                    printf("El tablero no es correcto, las reinas (%d,%d) y (%d,%d), se encuentran en la misma fila.\n", listaPosiciones[i][0],listaPosiciones[i][1],listaPosiciones[j][0],listaPosiciones[j][1]);
                }
                if(listaPosiciones[i][1]==listaPosiciones[j][1]){ //Dos reinas en la misma columna
                    printf("El tablero no es correcto, las reinas (%d,%d) y (%d,%d), se encuentran en la misma columna.\n", listaPosiciones[i][0],listaPosiciones[i][1],listaPosiciones[j][0],listaPosiciones[j][1]);
                }
                if(fabs(listaPosiciones[i][0]-listaPosiciones[j][0])==fabs(listaPosiciones[i][1]-listaPosiciones[j][1])){ // Hay dos reinas en la misma diagonal
                    printf("El tablero no es correcto, las reinas (%d,%d) y (%d,%d), se encuentran en la misma diagonal.\n", listaPosiciones[i][0],listaPosiciones[i][1],listaPosiciones[j][0],listaPosiciones[j][1]);
                }
            }
            j++;
        }
        i++;
    }
    if(verificado==1){
      printf("¡La solución es válida! :)\n");
    }
    return verificado;
}


// En la función 'main' pedimos el ingreso del nombre del archivo, leemos los datos y almacenamos las ubicaciones de las reinas
// en el array 'listaPosiciones'. Una vez cerrado el archivo, llamamos a la función que verificará las 
// posiciones almacenadas en el array y devolverá un mensaje por pantalla indicando si la solución es correcta
// o no (en caso de no serlo, se detalla el por qué).

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo con '.txt':\n");
    scanf("%s", nombreArchivo);

    // Abrimos el archivo.
    FILE *archivo;
    archivo=fopen(nombreArchivo, "r");
    // En la primera línea del archivo leemos la cantidad n de reinas.
    int cantReinas;
    fscanf(archivo, "%d", &cantReinas);
    int listaPosiciones[cantReinas][2];
    // En las restantes n lineas del archivo leemos las posiciones 'fila columna' de las reinas
    // y las agregamos al array de enteros.
    int linea=0;
    int error=0;
    while (linea<=cantReinas && error==0){ //Si alguna fila o columna está fuera de rango mostramos el error en pantalla.
        int fila, columna;
        fscanf(archivo, "%d %d", &fila, &columna);
        if(fila>=cantReinas || fila<0){
            printf("Error en el archivo: el número de fila: %d es incorrecto.\n", fila);
            error=1;
        }
        if(columna>=cantReinas || columna<0){
            printf("Error en el archivo: el número de columna: %d es incorrecto.\n", columna);
            error=1;
        }
        else{
            listaPosiciones[linea][0]=fila;
            listaPosiciones[linea][1]=columna;
            linea++;
        }
        
    }
    fclose(archivo);

    // Llamamos a la función que realiza la verificación y mostrará el resultado por pantalla 
    // si no hubo error alguno en el ingreso de los números de filas.
    if(error!=1){
        verificaTablero(listaPosiciones, cantReinas);
    }

    return 0;
}
