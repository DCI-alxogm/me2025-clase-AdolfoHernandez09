//Adolfo Hernandez Ramirez
//14-10-2025
/* Ejercicio Clase Martes 14-10-2025 

Este còdigo implementa el método de eliminación gaussiana para una matriz 
aumentada de 3×4*/

#include <stdio.h>
#include <math.h> 

#define FILAS_A 3
#define COLS_A 4

int main(void) {

    // Matriz A (3x3)

    double A[FILAS_A][COLS_A] = {
        {4, 6, 7, -3},
        {0, 2, 3, 8},
        {2, 1, 6, 5},
    };

    printf("Matriz A (%dx%d):\n", FILAS_A, COLS_A);

    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }

    //Declaramos el pivote 
    /* Cambiado a double para coincidir con la matriz A y evitar conversiones */
    double pivot[FILAS_A];

    /* Simple y segura comprobación de pivotes nulos: 
       para cada fila i verificamos A[i][i] y, si es cero, intentamos intercambiarla
       con la siguiente fila (si existe). Esto evita accesos fuera de rango. */
    for (int i = 0; i < FILAS_A; i++) {
        if (i < FILAS_A && i < COLS_A) { /* i < COLS_A protege si la matriz no fuera cuadrada en coeficientes */
            if (A[i][i] == 0.0) {
                if (i + 1 < FILAS_A) {
                    /* intercambiar fila i con fila i+1 */
                    for (int k = 0; k < COLS_A; k++) {
                        pivot[k] = A[i][k];
                        A[i][k] = A[i + 1][k];
                        A[i + 1][k] = pivot[k];
                    }
                } else {
                    /* No hay fila para intercambiar: imprimimos aviso (no sale del programa) */
                    fprintf(stderr, "Advertencia: pivote A[%d][%d] = 0 y no se puede intercambiar fila.\n", i, i);
                }
            }
        }
    }

    printf("Matriz A tras pivoteo (%dx%d):\n", FILAS_A, COLS_A);
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }

    /* Eliminación hacia adelante (Gauss) */
    for (int k = 0; k < FILAS_A; k++) { 
        printf("Eliminando columna %d \n", k + 1);

        /* Comprobar que el pivote no sea cero antes de dividir */
        if (k >= COLS_A || A[k][k] == 0.0) {
            fprintf(stderr, "Advertencia: pivote A[%d][%d] = 0 o fuera de rango. Se omite la eliminación para esta columna.\n", k, k);
            continue;
        }

        for (int i = k + 1; i < FILAS_A; i++) {
            double factor = A[i][k] / A[k][k];

            for (int j = 0; j < COLS_A; j++) {
                A[i][j] = A[i][j] - factor * A[k][j];
            }
        }

        printf("Matriz A  (%d):\n", k + 1);
        for (int i = 0; i < FILAS_A; i++) {
            for (int j = 0; j < COLS_A; j++) {
                printf("%10.4f ", A[i][j]);
            }
            printf("\n");
        }
    }

}
