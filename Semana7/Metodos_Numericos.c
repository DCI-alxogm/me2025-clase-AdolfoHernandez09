/*Adolfo Hernandez Ramirez
  22-09-2025

  Este es un programa que resuelve las raices de dos funciones con distintos 
  métodos numericos:

  - Método de Punto Fijo
  - Método Newton Rapshon
  - Método de Newton Rapshon Modificado
  - Método de la Secante 

  */

  #include <stdio.h>
  #include <math.h>

  //Funciones y derivadas

  //Funcion 1: f(x) = e^-x + x.

  double f1(double x){

      return exp(-x) + x;
  }

  // determinamos la derivada de la funcion 
  double f1_prima(double x){

      return -exp(-x) + 1;

  }

  // Necesitamos g1 para el método del punto fijo

  double g1(double x){

      return -exp(-x);

  }

  //Funcion 2: f(x) = x^3 -5x^2 -7x -3 

  double f2(double x){

      return x*x*x - 5*x*x - 7*x -3;

  }

  // Derivada de la funcion 2

  double f2_prima(double x){

      return 3*x*x -10*x -7;

  }

 // g(x) para el Método del punto fijo.

  double g2(double x){

      return cbrt(5*x*x + 7*x + 3); //Cbrt es la raíz cubica 
  }

  // Derivada numerica de g para el método del punto fijo

  double g_deriv_num(double (*g)(double), double x){

      double h = 0.000001; //Valor de h muy pequeño para mejorar la precision

      return (g(x+h) - g(x-h)) / (2*h); //Formula para la derivada central

  }

  // Método del punto fijo
  /***************************************************************************/

  void punto_fijo(int opcion, double x0, double tol, int maxIter){

      double (*g)(double) = (opcion==1)? g1 : g2;  //Declaramos un puntero a funcion
      double (*f)(double) = (opcion==1)? f1 : f2;

      double x = x0;
      double x_next; 

      /*inicializamos la variable x_prev con el valor inicial x0 que el usuario 
      ingresó.
      x_prev se usa para almacenar el valor de x de la iteración anterior en el 
      método de punto fijo.
      x_next;Declara otra variable x_next de tipo double sin inicializar, 
      que se usará para almacenar el nuevo valor de x en la iteración actual.*/

      //Damos el formato de la tabla final 

      printf("\nMETODO DEL PUNTO FIJO\n");
      printf("Iter  x_n           |x_n+1 - x_n|   |f(x_n)|   |g'(x)|\n");
      printf("--------------------------------------------------------\n");

      for(int i=1; i<=maxIter; i++){

          x_next = g(x); // Calcula x_{n+1} = g(x_n)
          double diff = fabs(x_next - x); // Diferencia entre iteraciones
          double res = fabs(f(x_next)); // Valor absoluto de la función en x_{n+1}
          double gpr = fabs(g_deriv_num(g, x)); // |g'(x_n)| aproximada

          printf("%3d   %12.8lf  %12.3e  %12.3e  %10.5f\n", i, x_next, diff, res, gpr);


      // Esta es la condicion de convergencia.

          if(diff < tol || res < tol){

              printf("Raiz aprox = %.8lf\n", x_next);

              return;
          }
    // Actualizamos el valor de x para la siguiente iteración
          
          x = x_next;

      }

      //Este mensaje aparece en dado caso que no converga considerando la condicion inicial

      printf("No convergio en %d iteraciones. Ultimo x = %.8lf\n", maxIter, x);
  }

  //Metodo Newton-Raphson
  /***************************************************************************/

  void newton(int opcion, double x0, double tol, int maxIter){

      double (*f)(double) = (opcion==1)? f1 : f2;
      double (*fp)(double) = (opcion==1)? f1_prima : f2_prima;

      double x = x0;
      double x_new;

      printf("\nMETODO DE NEWTON-RAPHSON\n");
      printf("Iter  x_n           |x_n+1 - x_n|   |f(x_n)|   |f'(x_n)|\n");
      printf("---------------------------------------------------------\n");

      for(int i=1; i<=maxIter; i++){

          double fx = f(x);
          double fpx = fp(x);

         // Aqui evitamos la division por cero

          if(fabs(fpx) < 1e-14){

              printf("Derivada cerca de 0, paro.\n");

              return;

          }

      // Newton: x_{n+1} = x_n - f(x_n)/f'(x_n)
          x_new = x - fx/fpx;

          double diff = fabs(x_new - x);
          double res = fabs(f(x_new));

          printf("%3d   %12.8lf  %12.3e  %12.3e  %12.5e\n", i, x_new, diff, res, fpx);

          if(diff<tol || res<tol){
              printf("Raiz aprox = %.8lf\n", x_new);
              return;
          }

          x = x_new;
      }
  }

  //Newton Modificado (multiplicidad m)
   /***************************************************************************/

  void newton_mod(int opcion, double x0, double tol, int maxIter, double m){

      double (*f)(double) = (opcion==1)? f1 : f2;
      double (*fp)(double) = (opcion==1)? f1_prima : f2_prima;

      double x = x0;
      double x_new;

      printf("\nMETODO DE NEWTON MODIFICADO (m=%.1lf)\n", m);
      printf("Iter  x_n           |x_n+1 - x_n|   |f(x_n)|   |f'(x_n)|\n");
      printf("---------------------------------------------------------\n");

      for(int i=1; i<=maxIter; i++){

          double fx = f(x);
          double fpx = fp(x);

          if(fabs(fpx) < 1e-14){

              printf("Derivada cerca de 0, paro.\n");
              return;
          }

          x_new = x - m*(fx/fpx); //Multiplicamos por el factor de multiplicidad

          double diff = fabs(x_new - x);
          double res = fabs(f(x_new));

          printf("%3d   %12.8lf  %12.3e  %12.3e  %12.5e\n", i, x_new, diff, res, fpx);

          if(diff<tol || res<tol){

              printf("Raiz aprox = %.8lf\n", x_new);
              return;
          }
          //Actualizamosx para una nueva iteracion

          x = x_new;
      }
  }

  //Metodo de la Secante
   /**************************************************************************/

  void secante(int opcion, double x0, double x1, double tol, int maxIter){

      double (*f)(double) = (opcion==1)? f1 : f2;

      double x_prev = x0;
      double x = x1;
      double x_next;

      printf("\nMÉTODO DE LA SECANTE\n");
      printf("Iter  x_n           |x_n+1 - x_n|   |f(x_n)|\n");
      printf("---------------------------------------------\n");

      for(int i=1; i<=maxIter; i++){

          double f_prev = f(x_prev);
          double f_curr = f(x);

          //Evita la disvision por cero

          if(fabs(f_curr - f_prev)<1e-14){

              printf("Division por 0, paro.\n");
              return;

          }

          x_next = x - f_curr*(x - x_prev)/(f_curr - f_prev);

          double diff = fabs(x_next - x);
          double res = fabs(f(x_next));

          printf("%3d   %12.8lf  %12.3e  %12.3e\n", i, x_next, diff, res);

          if(diff<tol || res<tol){

              printf("Raiz aprox = %.8lf\n", x_next);
              return;
          }
        //Actualizamos los valores correspondientes para una nueva iteracion.

          x_prev = x;
          x = x_next;
      }
  }

  int main(){

    //Declaracion de las variables necesarias para los metodos numericos

      int opcion;
      double x0, x1, tol;
      int maxIter;
      double m;

      printf("Funciones disponibles:\n");
      printf("1) e^-x + x  (sugerido x0=0.5)\n");
      printf("2) x^3-5x^2-7x-3  (sugerido x0=0 o 4)\n");

      //Aqui le pregunto al usuario que funcion quiere evaluar

      printf("Elija funcion (1 o 2): ");
      scanf("%d", &opcion);

      if(opcion==1){

      //Pedimos los valores de x0 si asi lo desea el usuario.

          x0=0.5;
          printf("Valor inicial x0 (Actualmente es 0.5 pero puedes cambiarlo xd): ");
          scanf("%lf", &x0);

      }else{

          printf("Ingrese valor inicial x0: ");
          scanf("%lf", &x0);
      }
    
    //Seguimos pidiendo valores necesarios d evariables importante de los metodos

      printf("Ingrese segundo valor x1 para secante: ");
      scanf("%lf", &x1);

      printf("Ingrese tolerancia: ");
      scanf("%lf", &tol);

      printf("Ingrese maximo de iteraciones: ");
      scanf("%d", &maxIter);

      printf("Ingrese multiplicidad m para Newton modificado: ");
      scanf("%lf", &m);

      // Con esta linea de codigo llamo directamente a todos los codifos o metodos
      //al int main

      punto_fijo(opcion, x0, tol, maxIter);
      newton(opcion, x0, tol, maxIter);
      newton_mod(opcion, x0, tol, maxIter, m);
      secante(opcion, x0, x1, tol, maxIter);


  }
