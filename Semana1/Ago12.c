/*Agosto 12 2025
Adolfo Hernández Ramirez*/

#include <stdio.h>
#include <math.h>

int main ()

{
  
   int numero[5];
   float resultados[5];

    numero[0] = 1;
    numero[1] = 2;
    numero[2] = 3;
    numero[3] = 4;
    numero[4] = 5;

 //la sintaxis de un ciclo for es la siguiente:
    //printf("x\t x^\t log(x+1)\t exp(x)+cos(x)\n");

    int i; //i simboliza index que representa un indice

    for(i=0; i<5; i++)

    {

    //printf("%d %d\n",numero[i],numero[i]%2);
    if(numero[i]%2 == 0){

      resultados[i]=log10(numero[i]+1);

      printf("x=%d log10= %f\n",numero[i],log10(numero[i]+1));
 
  
    } else {

      resultados[i]=exp(numero[i])+cos(numero[i]);

          printf("x=%d exp(x)+cos(x) = %f\n", numero[i],exp(numero[i])+cos(numero[i]));

    }
 
    }

    printf("Resultados\n");

    for(i=0; i<5; i++)
    
    {
      printf("%f\n", resultados[i]);
    }

    printf("pi+pi = %.12lf\n",3.14159265346 + 3.14159265346);


}