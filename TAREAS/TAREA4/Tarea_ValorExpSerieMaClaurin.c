/*Adolfo Hernández Ramírez
22-Agosto-2025

Este es un programa en c donde se determina el valor 
de e^x, en este programa el usuario da el valor de x
y en un proceso iterativo se calcula el valor de e^x
con la serie Maclaurin, hasta donde el error aproximado 
sea menor a 0.01% y además se imprime una tabla donde se
proyecta cada iteración y el valor de e^x, n y el error 
aproximado*/

#include <stdio.h>
#include <math.h>

int main(){

  double x, aprox_actual,aprox_anterior, error_aprox;
  error_aprox = 1; //iniciamos el error con un valor grande para el proceso iterativo en el ciclo while
  aprox_actual = 0;

  int n=0; //declaro aqui la variable n para la parte de la formula de la serie.

  printf("Este programa calcula el valor de e^x usando la serie de Maclaurin\n");
  printf("Ingresa el valor de x que deseas calcularle su exponencial\n");
  scanf("%lf",&x);

//Esta linea de codigo es para los encabezados de la tabla que imprimiremos al final

  printf("\n n\t e^x aproximado \tError\n");
  printf("\n--------------------------------\n");

  //Usamos do-while para que el ciclo se ejecute al menos una vez antes de evaluar la condición.
  do {

    double factorial = 1;

    //El siguiente ciclo es para calcular los factoriales que estan en la formula de la seriee.

    for(int f=1; f<=n; f++){

      factorial *= f; //En esta linea podemos calcular la parte del factorial
      //ya que 2! = 2*1 y en este ciclo for con esta linea de codigo seguimod ese principio

  

    }

    double Exponente = pow(x,n)/factorial; //en esta variable se guarda el valor de e^x

    aprox_anterior = aprox_actual;
    aprox_actual += Exponente; 


    //Usamos un condicional if-else para calcular el error

    if(n==0){

      error_aprox = 1; //Es 1 por que en n=0 e^x es 1 y usando ese valor en la formula del error considerando que el valor 
      //anterior era 0 entonces el error es del 100%
    } else {
      error_aprox = fabs((aprox_actual-aprox_anterior)/aprox_actual);

      //El fabs es para tomar el valor absoluto.
    
    }

    printf("%d\t %lf\t %lf\t\n",n,aprox_actual,error_aprox*100);
    
    n++; //Esto es para aumentar el valor de n 1 en 1 hasta llegar al menor error posible

} 
    while (error_aprox > 0.0001 || n==0); 
    /*esta es la condicion donde proponemos que el se realice lo del ciclo hasta que el error_aproximado 
    sea menor que 0.0001, además con n== 0 garantizamos que el primer término de la serie se calcule, 
    ya que esto es necesario para que la aproximación comience*/

}