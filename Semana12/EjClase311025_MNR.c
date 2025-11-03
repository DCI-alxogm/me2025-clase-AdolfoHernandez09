/*  Adolfo Hernandez Ramirez
    Actividad en clase. hacer el código en c del método de Newton.-Raphson
    para hallar un maximo o minimo

    En este caso mi funcion será 
    f(x)= 2*sin(x)-x^2/10
    donde en el rango de [0,2.75] existe el máximo global y en el rango de 4 a 6 existe un minimo local
    ya que en la función existen mas minimos en un rango más elevado de x, tomaremos ese minimo como el minimo
    global

    31-10-2025 */

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>

  //Definimos la función y sus derivadas

  double f(double x){

    return 2*sin(x)-x*x/10;

  }

  double df(double x){

    return 2*cos(x)- x/5;

  } 

  double df2(double x){

    return -2*sin(x)-1/5; 

  }

  int main() {

    double x0, x_opt, f_opt;
    int iter = 0;
    int opcion = 0;

    printf("Quieres hallar (1 = máximo, 2 = mínimo): ");
    scanf("%d", &opcion);
    
     // Definimos el punto inicial según la opción que el usuario elija

    if (opcion == 1) {  // Para el máximo
        
        printf("Encontraremos el máximo de la función 2*sin(x)-x*x/10\n");

        x0 = 1.0;  // punto inicial que sabemos que esta cercano al máximo

    } else { // Para el mínimo

        printf("Encontraremos el mínimo de la función 2*sin(x)-x*x/10\n");

        x0 = 4.0;   // punto inicial que sabemos que esta cercano al mínimo
   
    }

    printf("Punto inicial: x0 = %.6f\n", x0);

    //El siguiente ciclo do-while realizara las iteraciones necesarias para el método

    do { 

        iter++;

        //Formula del método de newton raphson

        x_opt = x0 - df(x0)/df2(x0);

        x0 = x_opt; //esto es para la siguiente iteracion

    }

    while (df(x_opt)>0.0001);

    //donde el valor del 0.0001 es la tolerancia que deseamos, se puede colocar manualmente
    //o pedirselo al usuario

    f_opt = f(x_opt);
    
    if(opcion==1) {

        printf("\n***** RESULTADO MÁXIMO *****\n");

    } else {

        printf("\n***** RESULTADO MÍNIMO *****\n");

    }

    printf("Iteraciones: %d\n", iter);
    printf("x_opt ≈ %.6f\n", x_opt);
    printf("f(x_opt) ≈ %.6f\n", f_opt);

    
}
