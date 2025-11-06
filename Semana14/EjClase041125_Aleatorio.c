/* Adolfo Hernández Ramírez 

  04-11-2025

  Busqueda aleatoria para encontrar el máximo de una función
  de dons dimensiones. 

  f(x,y) = y -x -2x^2 -2xy -y^2

  */
   
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <time.h> //esta nos sirve para la semilla que sea varaible en la busqueda de numeros aleatorios

    //definimos la funcion objetivo que devuelve el valor de f evaluado en x y y

    double evaluar(double xx, double yy){
      
      return (yy-xx) - (2*xx*xx) - (2*xx*yy) - (yy*yy);

    }

    int main(){

      //declaramos las variables para los puntos y evaluaciones

      double rx, ry; //valores aleatorios
      double valorf; //es el valor actual de la función evaluada en los valores random
      double mejorX = 0; //esta es la variable que almacena donde se encontrara el mejor valor de x
      double mejorY = 0; //lo mismo que lo anterior pero para y
      double mejorVal = -1e9; //mejor valor encontrado.

      int iter = 20000;  
      
      //inicializacion de la semilla para generar numeros alaertorios

      srand(42);

      //este ciclo for es para el muestreo aleatorio

      for ( int i=0; i<iter; ++i) {

        //primero generamos dos numeros aleatorios uniformes en el ranfo de [0,1)

        double r1 = (double)rand()/(double)RAND_MAX;
        double r2 = (double)rand() / (double)RAND_MAX;

        /*Mapeamos r1 y r2 a los intervalos deseados
                      x ∈ [-2, 2]   
                      y ∈ [1, 3]  
        */

        rx = -2 + 4*r1;
        ry = 1 + 2*r2;

        //evaluamos la funcion en f(rx, ry)
        valorf = evaluar(rx,ry);

        //si el valor actual es mejor que el anterior, se realiza lo siguienye

        if(valorf<mejorVal){

          mejorVal = valorf;
          mejorX = rx;
          mejorY = ry;

        }

      }

        //Imprimimos los resultados
        
        printf("Maximo aproximado encontrado (muestreo aleatorio):\n");
        printf("  x = %.6f\n", mejorX);
        printf("  y = %.6f\n", mejorY);
        printf("  f(x,y) = %.6f\n", mejorVal);
      
      }
