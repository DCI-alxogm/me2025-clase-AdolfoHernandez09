/* Adolfo Hernández Ramírez
 Clase 10-09-2025 

f(x) = sen(x) - cos(x)
en el ranfo de x=3 a x=5;

con un error relativo máximo entre iteraciones de er,max=0.001

Determinar si la relacion e_a = (Ax)i / 2^n,

 */


#include <stdio.h>
#include <math.h>
    
    float f(float x) {

      return sin (10*x) - cos(3*x);;

    }


  int main (){

    int iteraciones = 0;
    float a = 3,b = 5,k,kold=0, error_max = 0.0001, error;

    

    if(f(a)*f(b)>=0){

      printf("No existe solución para encontrar las raices de este problema, por lo tanto el método de bisección no funciona\n");

      return 0;
    }

    error = INFINITY;

    //Hago un ciclo do-while para que minimo se ejecute una vez el porgrama y después se evalue la condición clave.

    printf("\n******************RESULTADOS*********************\n\n");
    printf("Iteraciones\t\t K \t\t Error Relativo \t\t f(k) \t\t Error Aproximado\n");

    do{

      //Contador de las iteraciones

      iteraciones++;

      //Hago el calaculo del punto medio

      k = (a+b)/2;

      

        if(f(a)*f(k)<0){ //Evaluamos la condicional que nos pide el método de biseccion


          b = k;

        } else {

              a = k;

        }

      


        float error_aprox = k-kold;

        if(iteraciones==1){

            error = INFINITY;

        } else{

          error = fabs((k-kold)/k);

        }

    

     kold = k;



      printf("%d\t\t %f \t\t %f\t\t %f \t\t %f\n",iteraciones,k,error,f(k),error_aprox);

    }

    //La condicional es la siguiente

    while(error>error_max); 

    e_aproxfinal = error_aprox;

    float e_a = (b-a)/(2^iteraciones);

    if(e_aproxfinal == e_a){

        printf("La relación e_a = error_aprox\n");
      

    }

    else {

      printf("No se cumple la relación\n");

    }
  }
