/* Adolfo Hernández Ramírez
 Clase 10-09-2025 


Este es el código de la clase anterior solo que ahora agregamos el valor del
error de las raices, la evaluacion de la funcion en la k new, y el valor del 
numero de iteraciones necesarias para que el error sea el minimo. */


#include <stdio.h>
#include <math.h>
    
     float f(float c) {

      return (9.81*68.1)/c*(1-exp(-(c/68.1)*10))-40;

    }



  int main (){

    int iteraciones = 0;
    float a = 4,b = 20,k,kold=0, error_max = 0.001, error;

    

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
   
  }

  
