    /*
      Adolfo Hernández Ramírez
      26-10-20205

      Tarea 13. Este código resuelve matrices de sistemas lineales usando el 
      método de Gauss Siedel.

    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    // Función para imprimir una matriz

    void imprimirMatriz(double **matriz, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%8.4f ", matriz[i][j]);
            }
            printf("\n");
        }
    }

    // Función para imprimir un vector

    void imprimirVector(double *vector, int n) {
        for (int i = 0; i < n; i++) {
            printf("%8.4f\n", vector[i]);
        }
    }

    // Función para leer una matriz

    void leerMatriz(double **matriz, int n) {
        printf("Ingrese los elementos de la matriz A (%dx%d):\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("A[%d][%d] = ", i, j);
                scanf("%lf", &matriz[i][j]);
            }
        }
    }

    // Función para leer un vector
    
    void leerVector(double *vector, int n) {
        printf("Ingrese los elementos del vector b (%d elementos):\n", n);
        for (int i = 0; i < n; i++) {
            printf("b[%d] = ", i);
            scanf("%lf", &vector[i]);
        }
    }

    // Función para verificar si la matriz es diagonalmente dominante

    int esDiagonalDominante(double **A, int n) {
        for (int i = 0; i < n; i++) {
            double suma = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    suma += fabs(A[i][j]);
                }
            }
            if (fabs(A[i][i]) <= suma) {
                return 0; // No es diagonalmente dominante
            }
        }
        return 1; // Es diagonalmente dominante
    }

    // Método de Gauss-Seidel

    void gaussSeidel(double **A, double *b, double *x, int n, int max_iter, double tolerancia) {
        double *x_ant = (double *)malloc(n * sizeof(double));
        double error;
        int iter;
        
        // Inicializar vector solución con ceros
        for (int i = 0; i < n; i++) {
            x[i] = 0.0;
            x_ant[i] = 0.0;
        }
        
        // Verificar si la matriz es diagonalmente dominante

        if (esDiagonalDominante(A, n)) {
            printf("La matriz es diagonalmente dominante lo que indica que existe convergencia garantizada.\n");

        } else {
            printf("La matriz NO es diagonalmente dominante.\n");
            printf("La convergencia no esta garantizada.\n");
        }
        
        printf("\n=*****************INICIANDO ITERACIONES *****************\n");
        
        // Iteraciones del método de Gauss-Seidel

        for (iter = 0; iter < max_iter; iter++) {

            // Copiar solución actual a anterior
            for (int i = 0; i < n; i++) {
                x_ant[i] = x[i];
            }
            
            // Actualizar cada componente de x
            for (int i = 0; i < n; i++) {
                double suma = 0.0;
                
                // Suma de A[i][j] * x[j] para j < i (valores actualizados)
                for (int j = 0; j < i; j++) {
                    suma += A[i][j] * x[j];
                }
                
                // Suma de A[i][j] * x_ant[j] para j > i (valores anteriores)
                for (int j = i + 1; j < n; j++) {
                    suma += A[i][j] * x_ant[j];
                }
                
                // Calcular nuevo x[i]
                x[i] = (b[i] - suma) / A[i][i];
            }
            
            // Calcular error.
            error = 0.0;
            for (int i = 0; i < n; i++) {
                double error_actual = fabs(x[i] - x_ant[i]);
                if (error_actual > error) {
                    error = error_actual;
                }
            }
            
            // Mostrar información de la iteración
            printf("\n****** Iteracion %d ******\n", iter + 1);
            printf("Error: %.6f\n", error);
            printf("Solucion actual:\n");
            for (int i = 0; i < n; i++) {
                printf("  x[%d] = %8.6f\n", i, x[i]);
            }
            
            // Verificar convergencia
            if (error <= tolerancia) {
                break;
            }
        }
        
        // Mostrar resultados finales

        printf("\n*************** RESULTADOS FINALES ***************\n");

        if (error <= tolerancia) {

            printf("CONVERGENCIA ALCANZADA\n");
            printf("Iteraciones necesarias: %d\n", iter + 1);

        } else {
            printf("MAXIMO DE ITERACIONES ALCANZADO\n");
            printf("Iteraciones realizadas: %d\n", max_iter);
        }
        printf("Error final: %.10f\n", error);
        
        free(x_ant);
    }

    // Función para verificar la solución

    void verificarSolucion(double **A, double *b, double *x, int n) {
        printf("\n*************** VERIFICACION DE LA SOLUCION ********************\n");
        printf("Calculando A*x - b:\n");
        
        double error_max = 0.0;
        for (int i = 0; i < n; i++) {
            double residuo = 0.0;
            for (int j = 0; j < n; j++) {
                residuo += A[i][j] * x[j];
            }
            residuo -= b[i];
            printf("  Residuo[%d] = %12.10f\n", i, residuo);
            
            if (fabs(residuo) > error_max) {
                error_max = fabs(residuo);
            }
        }
        printf("Error maximo en la verificacion: %12.10f\n", error_max);
    }

    int main() {
        int n, max_iter;
        double tolerancia;
        
        printf("******************+ METODO DE GAUSS-SEIDEL ********************\n\n");
        
        // Leer parámetros

        printf("Ingrese el tamaño de la matriz (n): ");
        scanf("%d", &n);
        
        printf("Ingrese el numero maximo de iteraciones: ");
        scanf("%d", &max_iter);
        
        printf("Ingrese la tolerancia que desea para este método: ");
        scanf("%lf", &tolerancia);
        
        // Validar parámetros

        if (n <= 0 || max_iter <= 0 || tolerancia <= 0) {
            printf("Error: Todos los parametros deben ser positivos.\n");
            return 1;
        }
        
        // Reservar memoria
        double **A = (double **)malloc(n * sizeof(double *));
        double *b = (double *)malloc(n * sizeof(double));
        double *x = (double *)malloc(n * sizeof(double));
        
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(n * sizeof(double));
        }
        
        // Leer datos
        leerMatriz(A, n);
        leerVector(b, n);
        
        // Mostrar datos ingresados

        printf("\n********************DATOS INGRESADOS ****************\n");
        printf("Matriz A:\n");
        imprimirMatriz(A, n);
        printf("\nVector b:\n");
        imprimirVector(b, n);
        printf("\nParametros: n=%d, max_iter=%d, tolerancia=%.6f\n", n, max_iter, tolerancia);
        
        // Aplicar método de Gauss-Seidel

        gaussSeidel(A, b, x, n, max_iter, tolerancia);
        
        // Mostrar solución final

        printf("\n******************* SOLUCION FINAL **********************\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %12.8f\n", i, x[i]);
        }
        
        // Verificar solución

        verificarSolucion(A, b, x, n);
        
        // Liberar memoria

        for (int i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
        free(b);
        free(x);
        
        printf("\n************************** PROGRAMA TERMINADO ****************************\n");
        
      
    }