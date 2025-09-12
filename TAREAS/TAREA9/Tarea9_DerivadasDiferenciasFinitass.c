/* Adolfo Hernández Ramírez
  11/09/2025

  Este es un código que resuelve el siguiente problema. 

  Evaluar la 1er y 2da derivada en el intervalo [-2,2] con h=0.25. Usar las 
  aproximaciones en diferencias finitas hacia adelante, hacia atras y centrada. 
  Graficar las 3 aproximaciones junto con los valores exactos para la primera y 
  segunda derivada*/

  #include <stdio.h>
  #include <math.h> 

  //Definimos la función que otorga el programa.

  float fx (float x);

  //Esta es una función que describe la primera y segunda derivada de la funcion

  float dfx (float x);
  float d2fx (float x);


  int main(){

    //Declaramos las variables que utilizaremos para el problema.

    float a=-2, b=2, h=0.25;
    int n;

    n = (int)((b-a)/h); //Aqui se hace el calculo del numero de n que representa el numero de puntos que se toman en el intervalo de [-2,2]

    int i = 0; //esta i es para el contador del ciclo for de más adelnate.

    /* Declarando los arreglos tanto de los puntos de x como de las derivadas de la función evaluadas en dichos puntos*/

    float x[n], fpa[n], fpat[n], fpc[n], fprima[n];
    float fdpa[n], fdpat[n], fdpc[n], fdprima[n];  //fdpa[n] es para simbolizar la segunda derivada hacia adelante, atras y centrada, y fdprima es el valor exacto de la segunda deirvada para cada punto.


    for(int i=0; i<n; i++) {

      x[i] = a + i*h; //Con esta linea se especifica cada punto que se evaluara.

    }


    printf("Estos son los resultados para las primeras derivadas\n");
    printf("x[i]\t\t f'(x) Adelante \t\t f'(x) Atras \t\t f'(x) Centrada \t\t f' exacta\n");

    for(int i=0; i<n; i++) {

      fpa[i] = ((fx(x[i+1])) - (fx(x[i])))/h;
      fpat[i] = ((fx(x[i]))-fx(x[i-1]))/h;
      fpc[i] = ((fx(x[i+1]))-fx(x[i-1]))/h;

      fprima[i] = dfx(x[i]);


      printf("%f \t\t %f \t\t %f \t\t %f \t\t %f\n", x[i], fpa[i] , fpat[i], fpc[i], fprima[i]);

    }


    printf("\nEstos son los resultados para la segunda derivada\n");
    printf("x[i]\t\t f''(x) Adelante \t\t f''(x) Atras \t\t f''(x) Centrada \t\t f'' exacta\n");

    // Aqui calculo con las formulas de la segunda derivada.

    for(int j=0; j<n; j++) {

      fdpa[j] = ((fx(x[j+2])) - 2*(fx(x[j+1])) + (fx(x[j]))) / (h*h);
      fdpat[j] = ((fx(x[j-2])) - 2*(fx(x[j-1])) + (fx(x[j]))) / (h*h);
      fdpc[j] = ((fx(x[j+1])) - 2*(fx(x[j])) + (fx(x[j-1]))) / (h*h);

      fdprima[i] = d2fx(x[i]);


      printf("%f \t\t %f \t\t %f \t\t %f \t\t %f\n", x[i], fdpa[i] , fdpat[i], fdpc[i], fdprima[i]);

    }

    //asi es como se crea un archivo con los resultadis que se determinan en este codigo
    FILE *fp;
    fp = fopen("resultados.csv", "w");
    if(fp == NULL){
        printf("Error al crear el archivo.\n");
        return 1;
    }

    fclose(fp);

  }

    float fx(float x) {
        float f;

        f = x*x*x -2*x +4;

        return f; 

    }

    float dfx (float x) {

      float df;

      df = 3*x*x - 2;

      return df;


    }

    float d2fx (float x) {

      float df2;

      df2 = 6*x;

      return df2;

    }


