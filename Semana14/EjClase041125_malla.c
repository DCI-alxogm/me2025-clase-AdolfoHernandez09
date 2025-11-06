/* Adolfo Hernández Ramírez 

  04-11-2025

  Busqueda en malla para encontrar el máximo de una función
  de dons dimensiones. 

  f(x,y) = y -x -2x^2 -2xy -y^2

  */

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>

  //declaramos la funcion objetivo de la misma manera que con la busqueda aleaoria

  double evaluar(double xx, double yy){
      
    return (yy-xx) - (2*xx*xx) - (2*xx*yy) - (yy*yy);
  
  }

  int main() {

    //declaramos las variables para la busqueda

    double x = -1; //puntos iniciales
    double y = 1.5;
    double mejorX = x; //guardamos el mejor valor de x encontrado
    double mejorY = y;
    double mejorVal;

    double delta = 0.25; //este es el tamaño inicial del paso

    double tolerancia = 1e-5; //este es el criterio de paro
    int maxIter = 600; // numero maximo de iteraciones
  
    //calculaos la evaluacion inicial en el punto depatida

    mejorVal = evaluar(mejorX,mejorY);

    //definimos los desplazamientos unitarios para los 4 vecinos, después usamos factories y multiplicamos por delta

    double direcciones[4][2] = {

      (1,0),
      (-1,0),
      (0,1),
      (0,-1)


    };

    //este for es para la exploración de la malla

    for(int iter = 0; iter<maxIter;++iter){
      int hubomejora=0;
      double candidatoX = mejorX;
      double candidatoY = mejorY;

      //Exloramos los 4 vecinos alrededor del punto actual

      for(int k=0; k<4; ++k){

        //generamos coordenadas del vecino multiplicando la direccion por delta

        double xn = mejorX + delta*direcciones[k][0];
        double yn = mejorY + delta * direcciones[k][1];

        //evaluamos la funcion en el vecino (xn, yn)

        double val = evaluar(xn,yn);

        //si encontramos un valor mayor, actualizamos al candidato
          if (val > mejorVal) {
            
            mejorVal = val;
            candidatoX = xn;
            candidatoY = yn;
                
            hubomejora = 1;

            }   

        //si encontramos un vecino mejor, movemos el cengtro de la malla a dicho vecino

        if(hubomejora) {

          mejorX = candidatoX;
          mejorY = candidatoY;

        } else { 

          //si no hay mejor, reducimos el tamaño del paso 

          delta *= 0.3; //cambiamos delta

          //si el paso se reduce por debajo de la tolerancia, se terminan las iteraciones 
         
          if(delta<tolerancia) {

            break;

          }


        }

      }

    } 

    printf("Maximo aproximado encontrado (malla):\n");
    printf("  x = %.6f\n", mejorX);
    printf("  y = %.6f\n", mejorY);
    printf("  f(x,y) = %.6f\n", mejorVal);
    printf("  paso final = %.8f\n", delta); 
   

  } 

  


