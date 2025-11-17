/* Adolfo Hernandez Ramirez
  16-Nov-2025

  Este codigo es para resolver el sistema de ecuaciones en el reactor catalítico 
  mediante el uso del metodo de gauss-jordan*/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Función para imprimir la matriz aumentada
void imprimirMatriz(double **matriz, int n) {
    printf("\nMatriz aumentada [A|B]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", matriz[i][j]);
        }
        printf(" | %10.4f\n", matriz[i][n]);
    }
}

// Función para intercambiar dos filas de la matriz
void intercambiarFilas(double **matriz, int fila1, int fila2, int n) {
    for (int j = 0; j < n + 1; j++) {
        double temp = matriz[fila1][j];
        matriz[fila1][j] = matriz[fila2][j];
        matriz[fila2][j] = temp;
    }
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
        if (fabs(matriz[i][i]) <= suma) {
            return 0;
        }
    }
    return 1;
}

// Función para configurar el sistema linealizado del convertidor
void configurarSistemaLinealizado(double ***matriz, int *n) {
    printf("\n********** SISTEMA LINEALIZADO DEL CONVERTIDOR *************\n");
    
    *n = 5; // Sistema reducido con las variables principales
    
    // Crear matriz aumentada [A|B]
    *matriz = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matriz)[i] = (double *)malloc((*n + 1) * sizeof(double));
        for (int j = 0; j < *n + 1; j++) {
            (*matriz)[i][j] = 0.0;
        }
    }
    
    // Variables: ξ1, ξ2, G2, xO2,G2, xN2,G2
    // Con valores conocidos o estimados para G1 y composiciones de entrada
    
    printf("Variables: 0:ξ1, 1:ξ2, 2:G2, 3:xO2,G2, 4:xN2,G2\n");
    
    // DATOS CONOCIDOS DEL PROBLEMA:
    double G1 = 4006.1; // De ec. 7.17: 0.1*G1 = 400.61 => G1 = 4006.1
    double xNH3_G1 = 0.1; // 10% de NH3
    double xO2_G1 = 0.21 * 0.9; // 21% de O2 en el 90% restante (aire)
    double xN2_G1 = 0.79 * 0.9; // 79% de N2 en el 90% restante
    
    // ECUACIÓN 7.9: 0.1*G1 - 4*ξ1 - 4*ξ2 = 0
    (*matriz)[0][0] = -4.0;  // ξ1
    (*matriz)[0][1] = -4.0;  // ξ2
    (*matriz)[0][9] = -0.1 * G1; // B = -0.1*G1
    
    // ECUACIÓN 7.16: 4*ξ1 = 0.95*xNH3,G1*G1
    (*matriz)[1][0] = 4.0;   // ξ1
    (*matriz)[1][9] = 0.95 * xNH3_G1 * G1; // B
    
    // BALANCE DE OXÍGENO (simplificado)
    // O2 entrada - O2 consumido = O2 salida
    // xO2_G1*G1 - 5*ξ1 - 3*ξ2 = xO2,G2*G2
    (*matriz)[2][0] = -5.0;  // ξ1
    (*matriz)[2][1] = -3.0;  // ξ2
    (*matriz)[2][3] = -1.0;  // xO2,G2*G2
    (*matriz)[2][9] = -xO2_G1 * G1; // B
    
    // BALANCE DE NITRÓGENO
    // N2 entrada + N2 producido = N2 salida
    // xN2_G1*G1 + 2*ξ2 = xN2,G2*G2
    (*matriz)[3][1] = 2.0;   // ξ2 producido
    (*matriz)[3][4] = -1.0;  // xN2,G2*G2
    (*matriz)[3][9] = -xN2_G1 * G1; // B
    
    // BALANCE DE MASA TOTAL
    // G1 = G2 (asumiendo densidad constante)
    (*matriz)[4][2] = 1.0;   // G2
    (*matriz)[4][9] = G1;    // B = G1
    
    printf("Sistema configurado con 5 ecuaciones y 5 incognitas\n");
    printf("G1: %.2f kg/dia\n", G1);
}

// Función alternativa: sistema de prueba con solución conocida
void configurarSistemaPrueba(double ***matriz, int *n) {
    printf("\n********** SISTEMA DE PRUEBA CON SOLUCIÓN CONOCIDA **********\n");
    
    *n = 4;
    
    // Crear matriz aumentada [A|B]
    *matriz = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matriz)[i] = (double *)malloc((*n + 1) * sizeof(double));
    }
    
    // Sistema con solución: x1=1, x2=2, x3=3, x4=4
    double A[4][4] = {
        {2, 1, 1, 0},
        {1, 3, 1, 1},
        {1, 1, 4, 1},
        {0, 1, 1, 5}
    };
    
    double B[4] = {7, 14, 20, 25};
    
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            (*matriz)[i][j] = A[i][j];
        }
        (*matriz)[i][*n] = B[i];
    }
    
    printf("Sistema de prueba 4x4 con solucion conocida\n");
}

// Método de Gauss-Jordan mejorado
void gaussJordan(double **matriz, int n) {
    printf("\n************** APLICANDO METODO GAUSS-JORDAN **********\n");
    
    for (int k = 0; k < n; k++) {
        // Búsqueda de pivote máximo para estabilidad numérica
        int max_fila = k;
        double max_val = fabs(matriz[k][k]);
        
        for (int i = k + 1; i < n; i++) {
            if (fabs(matriz[i][k]) > max_val) {
                max_val = fabs(matriz[i][k]);
                max_fila = i;
            }
        }
        
        // Intercambiar si es necesario
        if (max_fila != k) {
            intercambiarFilas(matriz, k, max_fila, n);
        }
        
        // Verificar si el sistema es singular
        if (fabs(matriz[k][k]) < 1e-15) {
            printf("ERROR: Sistema singular o mal condicionado en fila %d\n", k + 1);
            return;
        }
        
        // Normalizar fila pivote
        double pivote = matriz[k][k];
        for (int j = k; j < n + 1; j++) {
            matriz[k][j] /= pivote;
        }
        
        // Eliminación hacia adelante y atrás
        for (int i = 0; i < n; i++) {
            if (i != k) {
                double factor = matriz[i][k];
                for (int j = k; j < n + 1; j++) {
                    matriz[i][j] -= factor * matriz[k][j];
                }
            }
        }
    }
}

// Resolver sistema específico del convertidor
void resolverSistemaConvertidor() {
    printf("\n********** RESOLVIENDO SISTEMA DEL CONVERTIDOR PASO A PASO **********\n");
    
    // DATOS CONOCIDOS
    double G1 = 4006.1; // kg/dia
    double NH3_alimentado = 0.1 * G1; // 400.61 kg/dia
    
    printf("Datos conocidos:\n");
    printf("G1 = %.2f kg/dia\n", G1);
    printf("NH3 alimentado = %.2f kg/dia\n", NH3_alimentado);
    printf("Aire alimentado = %.2f kg/dia\n", 0.9 * G1);
    
    // BALANCE DE AMONIACO
    // NH3 consumido = NH3 alimentado (se consume totalmente)
    double NH3_R1 = 0.95 * NH3_alimentado; // Reacción 1
    double NH3_R2 = 0.05 * NH3_alimentado; // Reacción 2
    
    // CALCULAR GRADOS DE AVANCE
    // De estequiometría: 4 moles NH3 producen 4 moles NO (R1)
    //                   4 moles NH3 producen 2 moles N2 (R2)
    
    // Asumiendo pesos moleculares para convertir a kg
    double PM_NH3 = 17.0;
    double ξ1 = NH3_R1 / PM_NH3; // moles/dia
    double ξ2 = NH3_R2 / PM_NH3; // moles/dia
    
    printf("\nResultados calculados:\n");
    printf("ξ1 (grado avance reaccion 1) = %.2f moles/dia\n", ξ1);
    printf("ξ2 (grado avance reaccion 2) = %.2f moles/dia\n", ξ2);
    printf("NH3 consumido en R1 = %.2f kg/dia\n", NH3_R1);
    printf("NH3 consumido en R2 = %.2f kg/dia\n", NH3_R2);
}

int main(int argc, char *argv[]) {
    double **matriz;
    int n;
    
    printf("********** RESOLUCION DEL SISTEMA DEL CONVERTIDOR CATALITICO **********\n");
    
    int opcion;
    printf("\nSeleccione el modo:\n");
    printf("1. Sistema linealizado del convertidor\n");
    printf("2. Sistema de prueba con solucion conocida\n");
    printf("3. Resolucion directa por balances\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    switch(opcion) {
        case 1:
            configurarSistemaLinealizado(&matriz, &n);
            break;
        case 2:
            configurarSistemaPrueba(&matriz, &n);
            break;
        case 3:
            resolverSistemaConvertidor();
            // Liberar memoria y salir
            for (int i = 0; i < n; i++) {
                free(matriz[i]);
            }
            free(matriz);
            return 0;
        default:
            printf("Opcion no valida\n");
            return 1;
    }
    
    // Mostrar sistema
    printf("\n********** SISTEMA A RESOLVER ************\n");
    imprimirMatriz(matriz, n);
    
    // Resolver
    gaussJordan(matriz, n);
    
    // Mostrar resultados
    printf("\n********* SOLUCION **********\n");
    char *nombres[] = {"ξ1", "ξ2", "G2", "xO2,G2", "xN2,G2"};
    
    for (int i = 0; i < n; i++) {
        printf("%s = %12.6f\n", nombres[i], matriz[i][n]);
    }
    
    // Verificar condición
    printf("\n************ ANALISIS NUMERICO **********\n");
    if (GoodCondicionado(matriz, n)) {
        printf("Sistema bien condicionado\n");
    } else {
        printf("Sistema mal condicionado - resultados pueden ser inexactos\n");
    }
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    
}