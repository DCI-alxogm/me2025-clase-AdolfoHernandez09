/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve ecuaciones diferenciales ordinarias usando
    el método de Runger Kutta de cuarto orden

    La ecuación diferencial que he elegido es 
    y' = y - t^2 + 1.

    */

    #include <stdio.h>
    #include <math.h>

   //Se  define la misma funcion de la misma manera

    double f(double t, double y) {
    
    return y - t*t + 1;

}

//Definimos la funcion para el metodo de Ranger Kutta de 4to orden

void Range_Kutta4to (double t0, double y0, double h, int n){

double t =t0;
double y=0;

//ahora definimos las 4 k's

double k1,k2,k3,k4;

printf("********************** Metodo de Range-Kkutta de 4to Orden *************************\n");
printf("t \t \t y\n");
printf("************************************************************\n");
printf("%.6f \t %.6f\n", t, y);

for(int i=0; i<n; i++) {

  //Definimos los valores de cada k
  k1 = h * f(t, y);
  k2 = h * f(t + h/2, y + k1/2);
  k3 = h * f(t + h/2, y + k2/2);
  k4 = h * f(t + h, y + k3);


 //Definios los bnuevos valores de y y t

  y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
  t = t + h;

  printf("%.6f \t %.6f\n", t, y);



}

}

int main() {

  double t0 = 0;
  double y0 = 0.5;
  double h = 0.1;
  int n=20;

  Range_Kutta4to(t0,y0,h,n);

}

