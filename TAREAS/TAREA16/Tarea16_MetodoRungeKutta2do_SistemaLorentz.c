/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve las ecuaciones del sistema de lorentz usando
    el metodo de Runge Kutta de 2do Orden

      dx/dy=σ(y−x)
      dy/dt = x(ρ−z)−y
      dz/dt =xy−βz

    */ 

 #include <stdio.h>
#include <math.h>

// Función para el sistema de Lorenz
void f(double t, double y[], double dydt[]) {

    double sigma = 10.0;
    double rho = 28.0;
    double beta = 8.0 / 3.0;

    dydt[0] = sigma * (y[1] - y[0]);
    dydt[1] = y[0] * (rho - y[2]) - y[1];
    dydt[2] = y[0] * y[1] - beta * y[2];
}


// Funcion del metodo de RungeKutta.
void RungeKutta2_sistema(double t0, double y0[], double h, int n, int dim) {

    double t = t0;
    double y[dim], k1[dim], k2[dim], y_temp[dim];

    // Copiamos las condiciones iniciales
    for (int i = 0; i < dim; i++)
        y[i] = y0[i];

    printf("\n******************** Sistema de Lorenz ********************\n");
    printf("***************** Método Runge-Kutta 2° Orden **************\n");
    printf("t \t\t x \t\t y \t\t z\n");
    printf("-----------------------------------------------------------\n");
    printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);

    // Ciclo del método Runger Kutta de 2do orden 

    for (int paso = 0; paso < n; paso++) {

        // k1 = h * f(t, y)
        f(t, y, k1);
        for (int i = 0; i < dim; i++)
            k1[i] *= h;

        // y_temp = y + k1
        for (int i = 0; i < dim; i++)
            y_temp[i] = y[i] + k1[i];

        // k2 = h * f(t + h, y + k1)
        f(t + h, y_temp, k2);
        for (int i = 0; i < dim; i++)
            k2[i] *= h;

        // y = y + (k1 + k2)/2
        for (int i = 0; i < dim; i++)
            y[i] += 0.5 * (k1[i] + k2[i]);

        t += h;

        if (paso % 10 == 0) 
        //va de 10 en 10 el oaso
            printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);
    }
}


int main() {

  //Declaramos los valores de los parametros 

    double t0 = 0.0;
    double h = 0.1;
    int n = 1000;
    int dim = 3;
    double y0_lorenz[3] = {1.0, 1.0, 1.0};

    //mandamos a llamar a la funcion

    RungeKutta2_sistema(t0, y0_lorenz, h, n, dim);

   
}
