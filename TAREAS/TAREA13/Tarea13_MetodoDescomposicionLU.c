/* 
  Adolfo Hernández Ramírez
  26-10-2025

  Tarea 13. Este código resuelve matrices de sistemas de ecuaciones lineales
  a partir del método de descomposición LU 

*/

  #include <stdio.h>
  #include <stdlib.h>

  //Declararemos funciones para imprimir y leer las matrices y vectores 

  //Función para imprimir una matriz 

  void imprimirMatriz(double **matriz, int n) {
    
    for(int i=0; i<n; i++){

        for(int j=0;j<n;j++){
          
          printf("%8.4f",matriz[i][j]);

        } 

        printf("\n");
    }
  }

  //Función para leer la matriz
  
  void LeerMatriz(double **matriz, int n){
    
    printf("Por favor, ingrese los elementos que conforman la matriz A (%dx%d):\n",n,n);
    
    for(int i=0; i<n;i++){
      
      for(int j=0; j<n; j++){

        //PEdimos y registramos los valores que ingrese el usuario para la matriz A
        printf("A[%d][%d] = ",i,j);
        scanf("%lf", &matriz[i][j]);

      }
    }
  }

  // Función para imprimir un vector

  void imprimirVector(double *vector, int n){
    
    for(int i=0; i<n; i++) {

      printf("%8.4f\n", vector[i]);

    }
  }

  // Función para leer un vector

  void LeerVector(double *vector, int n){

    printf("Por favor, ingrese los elementos del vector b (%d elementos): \n",n);

    for(int i=0; i<n; i++){

      //Aqui el ussuario ingresa lo valores de los elementos de b
      printf("b[%d] = ",i);
      scanf("%lf",&vector[i]);

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

      //Verificamos si U[k][k] es cero lo que implica que sea una matriz singular
      
      if(U[k][k] == 0){

        printf ("La matriz es singular, no es posible su descomposicion \n");

        return 0;

      }
      
      // Calculamos la columna k de L
      
      for(int i =k+1; i<n; i++){

        double suma =0;
        for(int p = 0; p<k; p++){

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

  //Funcion para el paso de la sustitución hacia atrás (Ux = y).

  void SustitucionAtras(double **U, double *y, double *x, int n){

    for(int i=n-1; i>=0; i--){

      double suma =0;

      for(int j=i+1; j<n; j++){

        suma += U[i][j]*x[j];

      }

      x[i] = (y[i]-suma)/U[i][i];

    }
  }

  int main() {

    int n;

    printf ("**************** MÉTODO DE DESCOMPOSICION LU ******************\n\n");

    //leer el tamaño de la matriz 

    printf("Ingrese el tamaño de la matriz(nxn): ");
    scanf("%d", &n);

    if(n<=0){ 
      
      printf("El tamaño de la matriz debe ser mayor a 0, repita nuevamente\n"); 
      return 1;
      
      }

    //De esta forma se reserva la memoria para matrices y vectores en c

    double **A = (double **)malloc(n * sizeof(double *));
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    double *b = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {

        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
   
    }

    //Leemos los datos de entrada para las matrices y vectores

    LeerMatriz(A,n);
    LeerVector(b,n);

    //A partir de aqui se representa la descomposición de LU

    if(!DescomposicionLU(A,L,U, n)){

      //liberamos la memoria para los casos de errores

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

    //REsolvemos el sistema
    SustitucionAdelante(L,b,y,n);
    SustitucionAtras(U,y,x,n);

    printf("**************** RESULTADOS ****************\n");

    printf("\n Matriz L: \n");
    imprimirMatriz(L,n);

    printf("\n Matriz U: \n");
    imprimirMatriz(U,n);

    printf("\n Vector y: \n");
    imprimirVector(y,n);

    printf("\n Solución x: \n");
    
    for(int i=0; i<n; i++){

      printf("x[%d] = %8.4f\n", i, x[i]);

    }

    //Verificamos que A*x sea igual a b

    for(int i=0; i<n; i++){

      double suma = 0;
      
      for(int j=0; j<n; j++){

        suma += A[i][j]*x[j];

      }

      printf("Resultado [%d] = %8.4f", i, suma);

    // Liberamos la memoria
    
    for (int i = 0; i < n; i++) {
        
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
    
    printf("\n************************ PROGRAMA TERMINADO *************************\n");
   
    

  }
  }