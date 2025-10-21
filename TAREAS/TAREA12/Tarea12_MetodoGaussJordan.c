/* Adolfo Hernández Ramírez 
  21 de Octubre del 2025

  Tarea 12. Realizar un código que resuelva matrices mediante el método de
  Gauss-Jordan, y que contenga lo siguiente:

  1. Leer la dimensión de la matriz de la linea de comandos.
  2. Leer los coeficientes de A y B de la linea de comandos.
  3. Evaluar la necesidad de cambiar filas(y realizarlo).
  4. Normalizar las filas si es necesario.
  5. Evaluar si el sistema esta bien condicionado.
  6. Imprimir la solución.

  */
 
 #include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Función para imprimir la matriz aumentada
void imprimirMatriz(double **matriz, int n) {
    printf("\nMatriz aumentada [A|B]:\n");
    for (int i = 0; i < n; i++) {
        // Imprimir coeficientes de A
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", matriz[i][j]);
        }
        // Imprimir separador y término independiente B
        printf(" | %8.3f\n", matriz[i][n]);
    }
}

// Función para intercambiar dos filas de la matriz
void intercambiarFilas(double **matriz, int fila1, int fila2, int n) {
    for (int j = 0; j < n + 1; j++) {
        double temp = matriz[fila1][j];
        matriz[fila1][j] = matriz[fila2][j];
        matriz[fila2][j] = temp;
    }
    printf("Se intercambiaron las filas %d y %d\n", fila1 + 1, fila2 + 1);
}

// Función para verificar si el sistema está bien condicionado
int GoodCondicionado(double **matriz, int n) {
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                suma += fabs(matriz[i][j]);
            }
        }
        // Verificar diagonal dominante
        if (fabs(matriz[i][i]) <= suma) {
            return 0; // No está bien condicionado
        }
    }
    return 1; // Está bien condicionado
}

// Función para leer datos interactivamente
void leerDatosInteractivo(double ***matriz, int *n) {
    printf("\n=== ENTRADA INTERACTIVA DE DATOS ===\n");
    
    // Leer dimensión de la matriz
    printf("Ingrese la dimension de la matriz (n): ");
    scanf("%d", n);
    
    // Validar la dimensión
    if (*n <= 0 || *n > 10) {
        printf("Error: La dimension debe estar entre 1 y 10\n");
        exit(1);
    }
    
    // Crear matriz aumentada [A|B]
    *matriz = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matriz)[i] = (double *)malloc((*n + 1) * sizeof(double));
    }
    
    printf("\nIngrese los coeficientes de la matriz A (%dx%d):\n", *n, *n);
    for (int i = 0; i < *n; i++) {
        printf("\nFila %d:\n", i + 1);
        for (int j = 0; j < *n; j++) {
            printf("  Coeficiente A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &(*matriz)[i][j]);
        }
    }
    
    printf("\nIngrese los terminos independientes B:\n");
    for (int i = 0; i < *n; i++) {
        printf("  Termino B[%d]: ", i + 1);
        scanf("%lf", &(*matriz)[i][*n]);
    }
}

// Función para leer datos desde línea de comandos
void leerDatosLineaComandos(double ***matriz, int *n, int argc, char *argv[]) {
    printf("\n=== LECTURA DESDE LINEA DE COMANDOS ===\n");
    
    // Leer dimensión desde primer argumento
    *n = atoi(argv[1]);
    printf("Dimension de la matriz: %dx%d\n", *n, *n);
    
    // Verificar que hay suficientes coeficientes
    int coeficientesNecesarios = *n * (*n + 1);
    if (argc < coeficientesNecesarios + 2) {
        printf("Error: Se necesitan %d coeficientes\n", coeficientesNecesarios);
        printf("Uso: %s <n> <a11> <a12> ... <a1n> <b1> <a21> ... <bn>\n", argv[0]);
        exit(1);
    }
    
    // Crear matriz aumentada [A|B]
    *matriz = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matriz)[i] = (double *)malloc((*n + 1) * sizeof(double));
    }
    
    // Leer coeficientes desde argumentos
    int indice = 2;
    printf("\nCoeficientes de la matriz A:\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            (*matriz)[i][j] = atof(argv[indice++]);
        }
    }
    
    // Leer términos independientes B
    for (int i = 0; i < *n; i++) {
        (*matriz)[i][*n] = atof(argv[indice++]);
    }
}

// Función principal para el método de Gauss-Jordan
void gaussJordan(double **matriz, int n) {
    printf("\n=== APLICANDO METODO GAUSS-JORDAN ===\n");
    
    for (int k = 0; k < n; k++) {
        printf("\n--- ETAPA %d (Pivote en posición %d,%d) ---\n", k + 1, k + 1, k + 1);
        
        // PASO 1: Verificar y corregir pivote cero
        if (fabs(matriz[k][k]) < 1e-10) {
            printf("Pivote muy pequeño (%.6f), buscando fila para intercambiar...\n", matriz[k][k]);
            int filaIntercambio = -1;
            
            // Buscar una fila con pivote no cero
            for (int i = k + 1; i < n; i++) {
                if (fabs(matriz[i][k]) > 1e-10) {
                    filaIntercambio = i;
                    break;
                }
            }
            
            if (filaIntercambio != -1) {
                intercambiarFilas(matriz, k, filaIntercambio, n);
            } else {
                printf("Error: Sistema singular, no tiene solución única\n");
                return;
            }
        }
        
        // PASO 2: Normalizar la fila pivote (hacer pivote = 1)
        double pivote = matriz[k][k];
        printf("Pivote actual: %.3f\n", pivote);
        
        if (fabs(pivote - 1.0) > 1e-10) {
            printf("Normalizando fila %d (dividiendo por %.3f)\n", k + 1, pivote);
            for (int j = k; j < n + 1; j++) {
                matriz[k][j] /= pivote;
            }
        }
        
        // PASO 3: ELIMINACIÓN COMPLETA (Diferencia clave con Gauss simple)
        // En Gauss-Jordan eliminamos arriba y abajo del pivote
        for (int i = 0; i < n; i++) {
            if (i != k) {  // No procesar la fila del pivote
                double factor = matriz[i][k];
                if (fabs(factor) > 1e-10) {
                    printf("Eliminando elemento (%.3f) de fila %d\n", factor, i + 1);
                    for (int j = k; j < n + 1; j++) {
                        matriz[i][j] -= factor * matriz[k][j];
                    }
                }
            }
        }
        
        printf("Matriz después de la etapa %d:", k + 1);
        imprimirMatriz(matriz, n);
    }
}

int main(int argc, char *argv[]) {
    double **matriz;
    int n;
    
    // Decidir modo de entrada: línea de comandos o interactivo
    if (argc > 1) {
        // Modo línea de comandos
        leerDatosLineaComandos(&matriz, &n, argc, argv);
    } else {
        // Modo interactivo
        leerDatosInteractivo(&matriz, &n);
    }
    
    // Mostrar los datos ingresados
    printf("\n=== DATOS INGRESADOS ===\n");
    imprimirMatriz(matriz, n);
    
    // Aplicar método de Gauss-Jordan
    gaussJordan(matriz, n);
    
    // Verificar si el sistema está bien condicionado
    printf("\n--- ANALISIS DEL SISTEMA ---\n");
    if (GoodCondicionado(matriz, n)) {
        printf(" El sistema ESTA BIEN CONDICIONADO (diagonal dominante)\n");
    } else {
        printf(" El sistema NO ESTA BIEN CONDICIONADO (puede ser sensible a errores)\n");
    }
    
    // En Gauss-Jordan, la solución está directamente en la última columna
    printf("\n=== SOLUCION FINAL (METODO GAUSS-JORDAN) ===\n");
    printf("La matriz identidad se ha obtenido y la solución está en la última columna:\n");
    
    for (int i = 0; i < n; i++) {
        printf("x%d = %10.6f\n", i + 1, matriz[i][n]);
    }
    
    // Verificación: Mostrar la matriz final (debería ser [I|X])
    printf("\n=== MATRIZ FINAL [I|X] ===\n");
    imprimirMatriz(matriz, n);
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}