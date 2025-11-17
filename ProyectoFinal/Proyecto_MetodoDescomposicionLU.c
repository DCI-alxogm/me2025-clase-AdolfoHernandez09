/* Adolfo Hernandez Ramirez
  16-Nov-2025

  Este codigo es para resolver el sistema de ecuaciones en el reactor catalítico 
  mediante el uso del metodo de factorización LU*/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para imprimir una matriz
void imprimirMatriz(double **matriz, int n) {
    for(int i=0; i<n; i++){
        for(int j=0;j<n;j++){
            printf("%12.6f",matriz[i][j]);
        } 
        printf("\n");
    }
}

// Función para imprimir un vector
void imprimirVector(double *vector, int n){
    for(int i=0; i<n; i++) {
        printf("%12.6f\n", vector[i]);
    }
}

// Función para el uso del método de descomposicion LU
int DescomposicionLU(double **A, double **L, double **U, int n){
    //Inicializamos las matrices L y U
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j){
                L[i][j]=1;
            } else {
                L[i][j]=0;
            }
            U[i][j]=0;
        }
    }
    
    //Descomposicion LU 
    for(int k=0; k<n; k++){
        //Calculamos la fila k de U 
        for(int j=k; j<n; j++){
            double suma = 0;
            for(int p=0; p<k; p++){
                suma += L[k][p]*U[p][j];
            }
            U[k][j]=A[k][j]-suma;
        }

        if(fabs(U[k][k]) < 1e-12){
            printf("La matriz es singular, no es posible su descomposicion \n");
            return 0;
        }
        
        // Calculamos la columna k de L
        for(int i=k+1; i<n; i++){
            double suma =0;
            for(int p=0; p<k; p++){
                suma+=L[i][p]*U[p][k];
            }
            L[i][k]=(A[i][k]-suma)/U[k][k];
        }
    }
    return 1; 
}

//Funcion para el paso de la sustitucion hacia adelante (Ly = b)
void SustitucionAdelante(double **L, double *b, double *y, int n){
    for(int i=0; i<n; i++){
        double suma =0;
        for(int j=0; j<i; j++){
            suma += L[i][j]*y[j];
        }
        y[i] = (b[i]-suma)/L[i][i];
    }
}

//Funcion para el paso de la sustitución hacia atrás (Ux = y)
void SustitucionAtras(double **U, double *y, double *x, int n){
    for(int i=n-1; i>=0; i--){
        double suma =0;
        for(int j=i+1; j<n; j++){
            suma += U[i][j]*x[j];
        }
        x[i] = (y[i]-suma)/U[i][i];
    }
}

// Función para configurar el sistema del convertidor catalítico
void configurarSistemaConvertidor(double ***A, double **b, int *n) {
    *n = 5;
    
    *A = (double **)malloc(*n * sizeof(double *));
    for(int i=0; i<*n; i++){
        (*A)[i] = (double *)malloc(*n * sizeof(double));
    }
    
    *b = (double *)malloc(*n * sizeof(double));
    
    double G1 = 4006.1;
    
    // Inicializar matriz A
    for(int i=0; i<*n; i++){
        for(int j=0; j<*n; j++){
            (*A)[i][j] = 0.0;
        }
    }
    
    // Configurar sistema de ecuaciones
    (*A)[0][0] = -4.0;
    (*A)[0][1] = -4.0;
    (*b)[0] = -400.61;
    
    (*A)[1][0] = 4.0;
    (*b)[1] = 380.5795;
    
    (*A)[2][0] = -5.0;
    (*A)[2][1] = -3.0;
    (*A)[2][2] = 1.0;
    (*A)[2][3] = 1.0;
    (*b)[2] = -757.1529;
    
    (*A)[3][1] = 2.0;
    (*A)[3][2] = 1.0;
    (*A)[3][4] = 1.0;
    (*b)[3] = -2848.3371;
    
    (*A)[4][3] = 1.0;
    (*A)[4][4] = 1.0;
    (*b)[4] = 1.0;
}

int main() {
    printf("************ RESOLUCION SISTEMA CONVERTIDOR CATALITICO - METODO LU ***************\n");

    double **A, **L, **U, *b, *y, *x;
    int n;
    
    configurarSistemaConvertidor(&A, &b, &n);
    
    L = (double **)malloc(n * sizeof(double *));
    U = (double **)malloc(n * sizeof(double *));
    y = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    
    for(int i=0; i<n; i++){
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
    }

    printf("\n************ DATOS DEL SISTEMA *************\n");
    printf("Matriz A:\n");
    imprimirMatriz(A, n);
    printf("\nVector b:\n");
    imprimirVector(b, n);

    if(!DescomposicionLU(A,L,U,n)){
        for(int i=0; i<n; i++){
            free(A[i]);
            free(L[i]);
            free(U[i]);
        }
        free(A);
        free(L);
        free(U);
        free(b);
        free(y);
        free(x);
        return 1;
    }

    SustitucionAdelante(L,b,y,n);
    SustitucionAtras(U,y,x,n);

    printf("\n************ RESULTADOS ************\n");
    printf("\nMatriz L:\n");
    imprimirMatriz(L,n);
    
    printf("\nMatriz U:\n");
    imprimirMatriz(U,n);
    
    printf("\nVector intermedio y:\n");
    imprimirVector(y,n);
    
    printf("\nSolucion del sistema:\n");
    char *nombres[] = {"ξ1", "ξ2", "G2", "xO2,G2", "xN2,G2"};
    for(int i=0; i<n; i++){
        printf("%-8s = %12.6f\n", nombres[i], x[i]);
    }

    printf("\n************ VERIFICACION ************\n");
    for(int i=0; i<n; i++){
        double suma = 0;
        for(int j=0; j<n; j++){
            suma += A[i][j]*x[j];
        }
        printf("Ecuacion %d: A*x = %12.6f, b = %12.6f\n", i+1, suma, b[i]);
    }

    for(int i=0; i<n; i++){
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);
    
    printf("\n************ PROGRAMA TERMINADO ***************\n");
    
}