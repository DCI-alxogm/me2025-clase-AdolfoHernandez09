/* Adolfo Hernández Ramírez
   14-09-2025.

   Este es un código que utiliza el método de bisección para encontrar las raices
   de la función f(x) = Sin (10x) - Cos(3x) 
   en el rango de x=3 a x=5, con un error relativo máximo entre iteraciones de 
   Er=0.001. 
   Determina si la relación Ea=\delta x/2^n  se satisface para cada raíz encontrada.

   */

#include <stdio.h>
#include <math.h>

// Definición de la función f(x)

float fx(float x) {

    return sin(10* x) - cos(3 * x);
}

int main() {

    // Definimos las variables que se usaran.

    /*Debido a que se conoce la función, se esperan 6 raices en lugar de una 
    entonces, se propone encontrar raices en pequeños subintervalos de la función 
    Por lo tanto usare arreglos para almacenar los diferentes valores de a y b. 
    Propongo incrementos de 0.2*/


    float error_max = 0.001;
    int intervalos = 11;  //Son los números de intervalos que tomaremos para el analisis
    float k[intervalos];  

    // Intervalos y el incremento a utilizar.

    float a_0 = 3;
    float b_0 = 5;
    float inc = 0.2;

    //Calculamos el numero de subintervalos a partir de la siguiente instrucción:

    int N = (int) ((b_0 - a_0) / inc);

    if (N > intervalos) N = intervalos; // De esta forma se evitan los desbordamientos de arreglos

    float a[intervalos];
    float b[intervalos];


    /* Determinamos los pequeños intervalos a evaluar */

    for (int i = 0; i < N; i++) {

        a[i] = a_0 + i * inc;
        b[i] = a[i] + inc;
        k[i] = 0; // inicializamos el valor de k
    
    }

    printf("i\t a\t b\t raiz\t\t  f(raiz)\t  Error \n");
    printf("----------------------------------------------------------------\n");

    //Con este ciclo for evaluamos las funcion para cada subintervalo

    for (int i = 0; i < N; i++) {

        float fa = fx(a[i]);
        float fb = fx(b[i]);

        // Criterio de cambio de signo

        if (fa * fb > 0) {

            printf("%2d\t %.4f\t %.4f\t\t\t  --\t\t   --\t\t   0 No hay cambio de signo\n",
                   i, a[i], b[i]);

            continue;
        }

        //Método de bisección en el subintervalo [a[i], b[i]]

        float a_new = a[i]; //Nos ayuda en la localizacion del punto a evaluar en la grafica ya sea hacia la izquierda, derecha o centro dentro del intervalo
        float b_new = b[i];
        float k_new = 0;
        float fk_new; 
        int iteraciones = 0;
        float error = 1.0;

        while (error > error_max) {

            k_new = (b_new + a_new) / 2; //Esto seria como la k de las anteriores versiones del codigo 
            fk_new = fx(k_new); //esto es el analogo a f(k)

            if (fa * fk_new < 0) { 

                b_new = k_new;
                fb = fk_new;

            } else {

                a_new = k_new;
                fa = fk_new;
            }

            error = fabs(b_new - a_new);
            iteraciones++;
        }

        k[i] = k_new;
        printf("%2d\t %.4f\t %.4f\t %.6f\t %.6f\t %0.4f\n",iteraciones, a[i], b[i], k[i], fx(k[i]), error);

    }

  ///imprimo las raices encontradas

    printf("\n\nLas raíces encontradas son las siguientes:\n\n");
    for (int i = 0; i < N; i++) {

        if (k[i] != 0) { // si se encontró raíz en ese intervalo

            printf("x = %.6f\t f(x) = %.6f\n", k[i], fx(k[i]));
        }
    }

}

