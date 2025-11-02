/*  Adolfo Hernandez Ramirez
    Actividad en clase. hacer el código en c del método de Interolación cuadrática 
    para hallar un maximo o minimo

    En este caso mi funcion será 
    x^3 - 4x 
    donde en el rango de [-2,0] existe un máximo y en el rango de 0 a 2 un minimo

    29-10-2025 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definimos la función

double f(double x) {

    return pow(x, 3) - 4*x;
}

int main() {

    double x0, x1, x2, x_opt, f_opt;
    int iter = 0;
    int opcion = 0;

    printf("Quieres hallar (1 = máximo, 2 = mínimo): ");
    scanf("%d", &opcion);

    // Definición de intervalos iniciales

    if (opcion == 1) { // máximo

        printf("Encontraremos el máximo de la función x^3 - 4x\n");

        x0 = -2;
        x1 = -1;   // valor intermedio arbitrario
        x2 = 0;

    } else { // mínimo

        printf("\nEncontraremos el mínimo de la función x^3 - 4x\n");

        x0 = 0;
        x1 = 1;    // valor intermedio arbitrario
        x2 = 2;
    }

    printf("Intervalo inicial: [%.6f , %.6f , %.6f]\n", x0, x1, x2);

    // Esgte será el ciclo principal de interpolación cuadrática

    do {
        iter++;

        // Calculamos los coeficientes de la interpolación cuadrática

        double f0 = f(x0);
        double f1 = f(x1);
        double f2 = f(x2);

        double numerator = (pow(x1,2)-pow(x2,2))*f0 + (pow(x2,2)-pow(x0,2))*f1 + (pow(x0,2)-pow(x1,2))*f2;
        double denominator = (x1-x2)*f0 + (x2-x0)*f1 + (x0-x1)*f2;

        x_opt = 0.5 * (numerator / denominator); //de aqui saldrá el dos de la fórmula vista en clase

        f_opt = f(x_opt);

        // Actualizamos los puntos para la siguiente iteración siguiendo el método

        if ((opcion == 1 && x_opt > x1) || (opcion == 2 && x_opt < x1)) {

            x0 = x1;
            x1 = x_opt;

        } else {

            x2 = x1;
            x1 = x_opt;
        }

    } while (fabs(f(x_opt) - f(x1)) > 0.001);


    if(opcion==1) {

        printf("\n***** RESULTADO MÁXIMO *****\n");

    } else {

        printf("\n***** RESULTADO MÍNIMO *****\n");
    }

    printf("Iteraciones: %d\n", iter);
    printf("x_opt ≈ %.6f\n", x_opt);
    printf("f(x_opt) ≈ %.6f\n", f_opt);

    return 0;
}
