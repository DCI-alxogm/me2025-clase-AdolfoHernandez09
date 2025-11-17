/* Adolfo Hernandez Ramirez
  16-Nov-2025

  Este codigo es para resolver el sistema de ecuaciones en el reactor catalítico 
  mediante el uso del metodo de gauss siedel*/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para imprimir la matriz aumentada
void imprimirMatriz(double **matriz, int n) {
    printf("\nMatriz del sistema [A]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir el vector de términos independientes
void imprimirVector(double *vector, int n) {
    printf("\nVector de terminos independientes [B]:\n");
    for (int i = 0; i < n; i++) {
        printf("%8.3f\n", vector[i]);
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
            return 0; // No está bien condicionado
        }
    }
    return 1; // Está bien condicionado
}

// Función para configurar el sistema del convertidor catalítico CORREGIDA
void configurarSistemaConvertidor(double ***A, double **b, int *n) {
    printf("\n=== CONFIGURANDO SISTEMA DEL CONVERTIDOR CATALITICO ===\n");
    
    *n = 5; // Sistema de 5 ecuaciones
    
    // Crear matriz A y vector b
    *A = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*A)[i] = (double *)malloc(*n * sizeof(double));
        for (int j = 0; j < *n; j++) {
            (*A)[i][j] = 0.0;
        }
    }
    
    *b = (double *)malloc(*n * sizeof(double));
    
    // Datos conocidos del problema
    double G1 = 4006.1;           // Flujo total de entrada (kg/dia)
    double xNH3_G1 = 0.1;         // Fracción de NH3 en entrada
    double xO2_G1 = 0.189;        // Fracción de O2 en entrada  
    double xN2_G1 = 0.711;        // Fracción de N2 en entrada
    double conversion = 0.95;     // Conversión del NH3
    
    printf("Variables del sistema:\n");
    printf("0: ξ1, 1: ξ2, 2: G2, 3: xO2,G2, 4: xN2,G2\n");
    printf("Datos conocidos: G1=%.2f, xNH3=%.3f, xO2=%.3f, xN2=%.3f, conversion=%.2f\n", 
           G1, xNH3_G1, xO2_G1, xN2_G1, conversion);
    
    // CORRECCIONES EN LAS ECUACIONES:
    
    // Ecuación 1: Balance de NH3 - 0.1*G1 - 4*ξ1 - 4*ξ2 = 0
    (*A)[0][0] = -4.0;  // ξ1
    (*A)[0][1] = -4.0;  // ξ2
    (*A)[0][2] = 0.0;   // G2 (no aparece)
    (*b)[0] = -xNH3_G1 * G1;  // -0.1*4006.1 = -400.61
    
    // Ecuación 2: Conversión del NH3 - 4*ξ1 = 0.95*(0.1*G1)
    (*A)[1][0] = 4.0;   // ξ1
    (*A)[1][1] = 0.0;   // ξ2
    (*A)[1][2] = 0.0;   // G2 (no aparece)
    (*b)[1] = conversion * xNH3_G1 * G1; // 0.95*0.1*4006.1 = 380.5795
    
    // Ecuación 3: Balance de O2 - xO2_G1*G1 - 5*ξ1 - 3*ξ2 + xO2_G2*G2 = 0
    (*A)[2][0] = -5.0;  // ξ1
    (*A)[2][1] = -3.0;  // ξ2  
    (*A)[2][2] = (*A)[2][3] = 1.0; // G2 * xO2,G2 (CORREGIDO: ambos deben aparecer)
    (*b)[2] = -xO2_G1 * G1; // -0.189*4006.1 = -757.1529
    
    // Ecuación 4: Balance de N2 - xN2_G1*G1 + 2*ξ2 + xN2_G2*G2 = 0
    (*A)[3][0] = 0.0;   // ξ1
    (*A)[3][1] = 2.0;   // ξ2
    (*A)[3][2] = (*A)[3][4] = 1.0; // G2 * xN2,G2 (CORREGIDO: ambos deben aparecer)
    (*b)[3] = -xN2_G1 * G1; // -0.711*4006.1 = -2848.3371
    
    // Ecuación 5: Suma de fracciones - xO2_G2 + xN2_G2 = 1 (CORREGIDO)
    (*A)[4][3] = 1.0;   // xO2,G2
    (*A)[4][4] = 1.0;   // xN2,G2
    (*A)[4][2] = 0.0;   // G2 (no aparece)
    (*b)[4] = 1.0;      // La suma de fracciones debe ser 1
    
    printf("Sistema configurado con %d ecuaciones y %d incognitas\n", *n, *n);
}

// Método de Gauss-Seidel mejorado
void gaussSeidel(double **A, double *b, double *x, int n, int max_iter, double tolerancia) {
    double *x_ant = (double *)malloc(n * sizeof(double));
    double error;
    int iter;
    
    // Inicializar vector solución con valores razonables
    for (int i = 0; i < n; i++) {
        x[i] = 1.0; // Valores iniciales más razonables
        x_ant[i] = 1.0;
    }
    
    printf("\n*************** APLICANDO METODO GAUSS-SEIDEL ************\n");
    printf("Iter 0: Valores iniciales: ");
    for (int i = 0; i < n; i++) {
        printf("x[%d]=%.3f ", i, x[i]);
    }
    printf("\n");
    
    // Iteraciones principales
    for (iter = 0; iter < max_iter; iter++) {
        // Guardar solución anterior
        for (int i = 0; i < n; i++) {
            x_ant[i] = x[i];
        }
        
        // Actualizar cada variable
        for (int i = 0; i < n; i++) {
            double suma = 0.0;
            
            // Sumar términos con valores ya actualizados
            for (int j = 0; j < i; j++) {
                suma += A[i][j] * x[j];
            }
            
            // Sumar términos con valores anteriores
            for (int j = i + 1; j < n; j++) {
                suma += A[i][j] * x_ant[j];
            }
            
            // Calcular nuevo valor (evitar división por cero)
            if (fabs(A[i][i]) > 1e-12) {
                x[i] = (b[i] - suma) / A[i][i];
            }
        }
        
        // Calcular error máximo
        error = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(x_ant[i]) > 1e-12) { // Error relativo para evitar división por cero
                double dif = fabs((x[i] - x_ant[i]) / x_ant[i]);
                if (dif > error) {
                    error = dif;
                }
            }
        }
        
        // Mostrar progreso cada 5 iteraciones
        if ((iter + 1) % 5 == 0) {
            printf("Iteracion %d - Error: %.8f\n", iter + 1, error);
        }
        
        // Verificar convergencia
        if (error < tolerancia) {
            printf("Convergencia alcanzada en %d iteraciones\n", iter + 1);
            break;
        }
    }
    
    if (iter == max_iter) {
        printf("Se alcanzo el maximo de iteraciones (%d)\n", max_iter);
    }
    
    free(x_ant);
}

int main() {
    double **A, *b, *x;
    int n;
    int max_iter = 200;  // Aumentado para mayor seguridad
    double tolerancia = 1e-8;
    
    printf("************ RESOLUCION SISTEMA CONVERTIDOR CATALITICO - GAUSS SEIDEL ***************\n");
    
    // Configurar sistema automáticamente
    configurarSistemaConvertidor(&A, &b, &n);
    
    // Reservar memoria para solución
    x = (double *)malloc(n * sizeof(double));
    
    // Mostrar datos del sistema
    printf("\n************ DATOS DEL SISTEMA *************\n");
    imprimirMatriz(A, n);
    imprimirVector(b, n);
    
    // Verificar condicionamiento
    printf("\n************** ANALISIS DEL SISTEMA ***********\n");
    if (GoodCondicionado(A, n)) {
        printf("El sistema ESTA BIEN CONDICIONADO (diagonal dominante)\n");
    } else {
        printf("El sistema NO ESTA BIEN CONDICIONADO\n");
        printf("Se intentara resolver de todas formas...\n");
    }
    
    // Aplicar Gauss-Seidel
    gaussSeidel(A, b, x, n, max_iter, tolerancia);
    
    // Mostrar resultados
    printf("\n************ SOLUCION FINAL (METODO GAUSS-SEIDEL) ************\n");
    char *nombres[] = {"ξ1", "ξ2", "G2", "xO2,G2", "xN2,G2"};
    
    for (int i = 0; i < n; i++) {
        printf("%-8s = %12.6f\n", nombres[i], x[i]);
    }
    
    // Verificación de la solución
    printf("\n************ VERIFICACION DE LA SOLUCION ************\n");
    double error_max = 0.0;
    for (int i = 0; i < n; i++) {
        double residuo = 0.0;
        for (int j = 0; j < n; j++) {
            residuo += A[i][j] * x[j];
        }
        residuo = fabs(residuo - b[i]);
        printf("Ecuacion %d: |residuo| = %12.8f\n", i + 1, residuo);
        if (residuo > error_max) {
            error_max = residuo;
        }
    }
    printf("Error maximo de verificacion: %12.8f\n", error_max);
    
    // Interpretación de resultados
    printf("\n************ INTERPRETACION DE RESULTADOS ************\n");
    printf("ξ1 = Grado de avance de la reaccion 1: %.6f kmol/dia\n", x[0]);
    printf("ξ2 = Grado de avance de la reaccion 2: %.6f kmol/dia\n", x[1]);
    printf("G2 = Flujo de salida del reactor: %.6f kg/dia\n", x[2]);
    printf("xO2,G2 = Fraccion de O2 en salida: %.6f\n", x[3]);
    printf("xN2,G2 = Fraccion de N2 en salida: %.6f\n", x[4]);
    printf("Suma fracciones salida: %.6f\n", x[3] + x[4]);
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    
    printf("\n************ PROGRAMA TERMINADO ***************\n");
    return 0;
}