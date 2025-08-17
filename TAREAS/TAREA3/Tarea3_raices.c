/*Adolfo Hernandez Ramirez
16-08-2025

Tarea #3 Encontrar las raices de un polinomio de la forma
ax^2+ bx + c 

*/

#include <stdio.h>
#include <math.h>

int main(){

  int opcion = 1; //esta variable es para el ciclo while para la parte de repetir 
  // el programa si el usuario lo desea.

  double a,b,c;
  double x1,x2,xi,xr; //en este caso xi es la raíz imaginaria y xr es la parte real de la raiz
  double discr; //discr es el discriminante.

  printf("Este es un programa que determina las raíces de un polinomio de la forma ax^2 + bx +c\n");

  while (opcion==1){

      printf("Ingresa el valor de las variables a, b y c del polinomio en ese orden\n");
      scanf("%lf %lf %lf",&a,&b,&c);

      if(a==0){
        if(b==0){
          printf("La solución es trivial\n");
        } else{
          x1 = -c/b;
          printf("Solo existe una raíz x=%0.2f\n",x1);
        }


      } else{

        discr = b*b-4*a*c;

        if(discr>=0){

          x1 = (-b + sqrt(discr))/(2*a);
          x2 = (-b - sqrt(discr))/(2*a);

          printf("Las dos raíces son x1 = %0.2f y x2=%0.2f\n",x1,x2);

        } else {

          printf("Las raices son complejas\n");
          xi = sqrt(-discr)/2*a;
          xr = -b/2*a;

          printf("La raiz compleja es la siguiente considerando la parte real y la imaginaria\n");
          printf("x1 = %0.2f + %0.2fi \n",xr,xi);
          printf("x2 = %0.2f - %0.2fi \n",xr,xi);



        }


      }

    printf("Si deseas calcular más raices de otros polinomios\n");
    printf("\nIngresa Si=1 o No=0\n");
    scanf("%d",&opcion);

  } 
    printf("El programa ha terminado\n\n");
 
}