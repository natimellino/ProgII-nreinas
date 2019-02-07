# TRABAJO PRÁCTICO FINAL: "Las n-reinas"
# Observaciones:
#   -) Representación del tablero y las posiciones de las reinas:
#       Las posiciones de cada reina son marcadas en una lista L donde cada índice 'i'
#       representa el número de una columna, y el elemento en la posición L[i],
#       representa el número de una fila. Entonces, la posición (fila, columna) de una
#       reina será (L[i], i). Por ejemplo:
#       L=[0,2,3,1] --> Filas
#          0 1 2 3 -->Índices/Número de columna
#       En este ejemplo, la cantidad N de reinas es N=len(L)=4, y éstas se ubican en las
#       posiciones: (0,0), (1,2), (3,2) y (1,3).
#   -) El programa recibe como entrada un número N, que indica la cantidad de reinas que
#      se quieran ubicar en el tablero, y genera como salida un archivo indicando las
#      cantidad de reinas en la primera línea, y en las siguientes N líneas la ubicación
#      'fila columna' de cada reina. En caso de que no haya solución, dicho archivo no es
#       creado y se imprime un mensaje por pantalla indicando que no se pudo hallar la solución.

# vAbs: Int Int --> Int
# vAbs: dados dos enteros x e y devuelve el valor absoluto de x-y.

def vAbs(x,y):
    if x>y:
        return x-y
    else:
        return y-x

# Testing de la función 'vAbs',

def test_vAbs():
    assert vAbs(1,2)==1
    assert vAbs(0,0)==0
    assert vAbs(5,2)==3


# verificar: List Int --> Boolean
# verificar: dada una lista de posiciones y un entero que representa el número de una columna k,
# devuelve True si el tablero con las reinas que están ubicadas hasta la columna k (inclusive),
# con k<longListaDePosiciones, es válido. Caso contrario, devuelve False. Debido a la representación
# elegida para el tablero, no es necesario verificar que haya dos o más reinas en la misma columna, por lo
# tanto, sólo resta verificar que no haya dos o más reinas en la misma fila ni en la misma diagonal.

def verificar(arr, columna):
    verificado=True
    i=0
    while i<=columna and verificado:
        j=i+1
        while j<=columna and verificado:
            if arr[i]==arr[j] or vAbs(arr[i],arr[j])==vAbs(i,j):
                verificado=False
            j+=1
        i+=1
    return verificado

# Testing para la función 'verificar',

def test_verificar():
    assert verificar([0,3,1,2], 2)==True
    assert verificar([0,3,1,2], 3)==False
    assert verificar([0,3,2,2], 1)==True
    assert verificar([0,3,2,2], 2)==False


# reinas: List Int Int --> Boolean
# reinas: dada una lista de posiciones, un número de columna y una cantidad n de reinas,
# ubica, si es posible, las n reinas en un tablero de ajedrez de modo que ninguna se amenace.
# El algoritmo comienza con todos los números de fila de la lista de posiciones en -1. A partir
# de allí a la fila listaDePosiciones[columna] le sumamos 1, y comprobamos (mediante la funcion verificar) si ese numero de fila
# en esa columna lleva a una solución, llamando recursivamente a la funcion reinas(listaPosiciones, columna+1, n).
# Se repite el mismo proceso para columna+1 y en caso de que no resulte en una solución, volvemos a listaPosiciones[columna],
# le asignamos otra fila y vemos si así podemos llegar a una solución.
# Una vez que llegamos a una solución, retornamos True y en la listaPosiciones tendremos los números de fila donde deben
# ubicarse las reinas. En caso de que sea imposible hallarla devolvemos False y la listaPosiciones tendra todos sus elementos
# iguales a -1.

def reinas(arr, col, n):
    ok=False
    if col==n:
        return True
    else:
        while arr[col]<n-1 and not ok:
            arr[col]+=1 # 1) Le asignamos a la reina un número de fila.
            if verificar(arr,col): # Si la posición es validada llamamos recursivamente a la función tratando de colocar la siguiente reina y vemos si nos lleva a una solución.
                ok=reinas(arr,col+1,n)   # Si ok es False ese número de fila no lleva a una solución y debemos volver al paso 1).
        if ok==False:
            arr[col]=-1
        return ok

# Testing para la función 'reinas'.

def test_reinas():
    assert reinas([-1], 0, 1)==True
    assert reinas([-1,-1], 0, 2)==False
    assert reinas([-1,-1,-1], 0, 3)==False
    assert reinas([-1,-1,-1,-1,-1], 0, 5)==True


# nreinas: None --> None
# nreinas: Recibe un número n ingresado por el usuario, llama a la funcion 'reinas'
# que se encarga de crear la solución al problema de ubicar las n reinas en un
# tablero de ajedrez sin que se ataquen. Una vez hallada la solución, si es que esta existe,
# se escribe en un archivo con la cantidad de reinas y las posiciones 'fila columna' de cada
# una de ellas. Si no existe solución, el archivo no se crea y se le informa al usuario por
# pantalla que no ha sido posible hallar una solución.

def nreinas():
    n=int(input("Ingrese la cantidad n de reinas: "))
    solucion=[-1]*n
    sol=reinas(solucion,0,n)
    if sol==False:
        print("No se pudo encontrar solución.")
    else:
        # Escribimos la solución en un archivo preparado para ser usado como entrada en el programa de C.
        solReinas=open("solucionReinas.txt", "w")
        solReinas.write(str(n)+'\n') #Cantidad de reinas.
        for i in range(0, n): # Escribimos en el archivo la fila y columna de cada reina separadas por un espacio.
            solReinas.write(str(solucion[i])+' '+str(i)+'\n')
        print("¡Solución guardada en 'solucionReinas.txt'!")

nreinas()
