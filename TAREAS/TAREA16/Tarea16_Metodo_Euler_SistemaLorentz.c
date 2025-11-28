/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve las ecuaciones del sistema de lorentz usando
    el metodo de Euler.

      dx/dy=σ(y−x)
      dy/dt = x(ρ−z)−y
      dz/dt =xy−βz

    */

 #include <stdio.h>
#include <math.h>

// Estta funcion es para el Sistema de Lorenz
void f(double t, double y[], double dydt[]) {

    double sigma = 10.0;
    double rho = 28.0;
    double beta = 8.0 / 3.0;

    dydt[0] = sigma * (y[1] - y[0]);
    dydt[1] = y[0] * (rho - y[2]) - y[1];
    dydt[2] = y[0] * y[1] - beta * y[2];
}

//En esta funcion colocamos el metodo de euler para reesolver el sistema de Edo de Lorentz

void euler_sistema(double t0, double y0[], double h, int n, int dim) {

    double t = t0;
    double y[3];
    double dydt[3];

    // Copiamos condiciones iniciales
    for (int i = 0; i < dim; i++){
           y[i] = y0[i];

    printf("\n******************** Sistema de Lorenz ********************\n");
    printf("********************* Método de Euler *********************\n");
    printf("t \t\t x \t\t y \t\t z\n");
    printf("-----------------------------------------------------------\n");
    printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);

    // Este for es para las iteraciones del meétodo de Euler

    for (int paso = 0; paso < n; paso++) {

        // Evaluamos las derivadas
        f(t, y, dydt);

        // Actualizamos variables
        for (int i = 0; i < dim; i++)
            y[i] += h * dydt[i];

        t += h;

        printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);

    }
    }
}

int main() {

//Definimos los valores d elos parametros

    double t0 = 0.0;
    double y0[3] = {1.0, 1.0, 1.0}; //los coeficientes de x,y,z
    double h = 0.01;

    //Elegimos un numero apto de iteraciones
    int n = 1000;
    int dim = 3;

    //mandamos llamar a la funciín del metodo de euler

    euler_sistema(t0, y0, h, n, dim);

  
}
