/*Adolo Hernandez Ramirez
12-09-2023

Este es un código que usa el método de bisección para la función pow(c, 10) - 1;
*/

#include <stdio.h>
#include <math.h>

//Definimos la función 

float f(float c) {

    return pow(c, 10) - 1;

}

int main() {

  //Declaramos las variables para los errores permitidos y los intervalos

  float error_max = 0.0001f;
  float a_0 = 4, b_0 = 20, a = a_0, b=b_0;
  float k, fk, error, e_aprox, kold;

  int n=0;
  float e_aprox_teorico;

  printf("Iteraciones \t\t Raiz \t\t f(k) \t\t Eaproximado \t\t Erelativo \t\t Eaproximado Teórico\n");

  //Iniicializamos el valor de la kold

  //Ciclo do-while para ejecutar hasta que el error determinado sea menor que el error maximo definido.

  do {

    k = (a+b)/2.0f; //Asi se calcula el punto medio en el método de biseccion
    fk = f(k);
    n++; //Este es el contador de las iteraciones


    /*Método de bisección como se realizo en clases anteriores*/

    if(f(k)*f(a)< 0) {

      b = k;

    } else { 
      
      a=k;

    }

    e_aprox = fabs(k-kold);
    error = fabs(e_aprox/k);
    e_aprox_teorico = (b_0 - a_0) / pow(2,n);
    kold = k;

    //Imprimimos los resultados 

    printf(" %d \t\t %f \t\t %f \t\t %f \t\t %f \t\t %f\n", n, k,fk, e_aprox, error, e_aprox_teorico);

  } while (error > error_max);

    printf("\n La raíz aproximada es %f\n", k);
    printf("f(c_raiz) = %f\n", f(k));

}
