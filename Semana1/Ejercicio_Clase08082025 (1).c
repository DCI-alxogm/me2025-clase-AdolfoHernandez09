//08 Agosto 2025
//Adolfo Hernandez Ramirez
/*Hacer un programa que imprime 5 numeros flotantes 
y el valor de las siguientes funciones*/


#include<stdio.h>
#include<math.h>

int main()
{
  float valores[5];

  valores[0] = 12.3;
  valores[1] = 4.12;
  valores[2] = 1.28;
  valores[3] = 3.15;
  valores[4] = 4.28;

  
  printf("Los valores flotantes son: %f %f %f %f %f\n", valores[0],valores[1],valores[2],valores[3],valores[4]);


  /*Ahora imprimiremos las siguientes funciones
  
  f(x) = x^2
  f(x) = log(x+1)
  f(x) = exp(x) + cos(x)
  */

float x;
x = 18.032024;


printf("f(x) = x^2 = %f \n", x*x);
printf("f(x) = log(x+1) = %f \n", log(x+1));
printf("f(x) = (exp(x) + cos(x)) = %f \n", (exp(x)+ cos(x)));


}
