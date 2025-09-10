/* Adolfo Hernández Ramírez
  09-09-2025

  Ejercicio de clase del martes 09 de septiembre. 
  En este codigo se aplica el método de bisección para encontrar las raíces de 
  cualquier función */

  #include <stdio.h>
  #include <math.h>

  /* Aqui declaro la función del problema*/
    
    float f(float c) {

      return (9.81*68.1)/c*(1-exp(-(c/68.1)*10))-40;

    }


  int main (){

    int iteraciones = 0;
    float a,b,k,kold, error_max, error;

    printf("Este es un programa para resolver el valor de c en la función F(c) = gm/c * (1 - e^{-ct/m}) - v \n");
    printf("Por favor ingresa el valor del error que deseas como limite para resolver este problema\n");
    scanf("%f",&error_max);
    
    //Se desconoce el valor de a y b, y dicho intervalo, por eso pedire al usuario que el los indique 

    printf("Ingresa los valores de a y b respectivamente\n");
    scanf("%f %f", &a, &b);

    if(f(a)*f(b)>=0){

      printf("No existe solución para encontrar las raices de este problema, por lo tanto el método de bisección no funciona\n");

      return 0;
    }

    //Consideramos que kold=a para la primera iteración 

      kold = a;

    //Hago un ciclo do-while para que minimo se ejecute una vez el porgrama y después se evalue la condición clave.

    printf("\n******************RESULTADOS*********************\n\n");
    printf("Iteraciones\t\t K \t\t Error\n");

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

      

      //En esta parte calculamos el error relativo

      if(iteraciones>1){

        error = fabs((k-kold)/k);
      
      } else {

      error = error_max +1;

      }

      kold = k;

      /*Se imprimen los resultados obtenidos*/

      printf("%d\t\t %f \t\t %f\n",iteraciones,k,error);

    }

    //La condicional es la siguiente

    while(error>error_max);

  }

  
  