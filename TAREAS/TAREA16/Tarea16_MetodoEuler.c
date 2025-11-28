/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve ecuaciones diferenciales ordinarias usando
    el método de Euler

    La ecuación diferencial que he elegido es 
    y' = y - t^2 + 1.

    */

    #include <stdio.h>
    #include <math.h>


    //Esta función define la EDO: dy/dt = f(t,y)

    double f(double t, double y) {

      return y - t*t + 1;

    }

    //En esta función se realiza el método de Euler

    void euler (double t0, double y0, double h, int n) {

      double t = t0;
      double y = y0; //Los valores inicials antes de la iteración

      printf("********** METODO DE EULER************** \n");
      printf("t \t \t y \n");
      printf("*******************************************\n");
      printf("%.6f \t %.6f\n",t,y);


      //Ciclo for en donde ocurren las iteraciones necesarias para el método
      //y para encontrar la solución a la EDO

      for (int i=0; i<n; i++){

        y = y + h*f(t,y);
        t = t + h;
        
        printf("%.6f \t %.6f \n", t,y);

      }
    }

    int main() { 

      //Declaramos los valores iniciales de las variablesentre ellas el tamaño
      //del paso

      double t0 = 0; //valor inicial de t
      double y0 = 0.5;
      double h = 0.1; //valor del tamaño del paso

      int n = 20; //Numero de pasos

      //mando a llamar a la función donde se encuentra el metodo de euler

      euler(t0, y0, h, n);


    }

