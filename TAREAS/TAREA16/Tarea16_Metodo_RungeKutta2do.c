/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve ecuaciones diferenciales ordinarias usando
    el método de Runger Kutta

    La ecuación diferencial que he elegido es 
    y' = y - t^2 + 1.

    */

    #include <stdio.h>
    #include <math.h>

   //Se  define la misma funcion de la misma manera

    double f(double t, double y) {
    
    return y - t*t + 1;

}

    //Definimos una funcion donde almacenamos el procedimiento del metodo
    //de Runger Kutta tal como lo hicimos con el metodo de euler

    void Runger_kutta_2doOrden (double t0,  double y0, double h, int n){

      double t = t0; //definimos los valores de t y  y oara las iteraciones 
      double y = y0;
      
      //definimos kas variables de k1 y k2 que son necesarias en el metodo

      double k1, k2;

      printf("************************** Método de Runge Kutta de 2do Orden ************************\n");
      printf("t \t \t y\n");
      printf("**************************************************************************************\n");
      printf("%.6f \t %.6f \n",t,y);

      //Ciclo For donde se realizan las iteraciones del método de runger kutta de 
      //2do ORden

      for (int i=0; i<n; i++){

        k1 = h * f(t,y);
        k2 = h * f(t+h/2, y + k1/2);

        //Aqui se definen los nuevos valores de t y y, tomando en cuenta
        //los valores de h y del parametro k1

        y = y +k2;
        t =t +h;

        printf("%.6f \t %.6f\n", t,y);

      }


    }

    int main() {

      //Declaramos los valores iniciales

      double t0 = 0;
      double y0 = 0.5;
      double h = 0.1;
      int n = 20;


      //mandamos a llamar a la funion

      Runger_kutta_2doOrden (t0,y0,h,n);
   
    }

