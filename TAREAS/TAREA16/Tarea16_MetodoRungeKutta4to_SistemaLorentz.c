/*  Adolfo Hernández Ramírez 
    27/11/2025 
    
    Este es un código que resuelve las ecuaciones del sistema de lorentz usando
    el metodo de Runge Kutta de 4too Orden

      dx/dy=σ(y−x)
      dy/dt = x(ρ−z)−y
      dz/dt =xy−βz

    */ 


    #include <stdio.h>
#include <math.h>

// Sistema de ecuaciones: Lorenz
void f(double t, double y[], double dydt[]) {
    double sigma = 10.0;
    double rho = 28.0;
    double beta = 8.0/3.0;
    
    dydt[0] = sigma * (y[1] - y[0]);
    dydt[1] = y[0] * (rho - y[2]) - y[1];
    dydt[2] = y[0] * y[1] - beta * y[2];
}

//Funcion del metodo de Runge Kutta de 4to ORden
void  Runge_Kuttak_4to_sistema(double t0, double y0[], double h, int n, int dim) {

    double t = t0;
    double y[dim], k1[dim], k2[dim], k3[dim], k4[dim];
    double y_temp[dim];
    
    // Copiamos las condiciones iniciales
    for (int i = 0; i < dim; i++) {

        y[i] = y0[i];

    }
    
    printf("\n******************** Sistema de Lorenz ********************\n");
    printf("***************** Método Runge-Kutta 4° Orden **************\n");
    printf("t \t\t x \t\t y \t\t z\n");
    printf("-----------------------------------------------------------\n");
    printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);

    //ciclo for del metodo
    
    for (int paso = 0; paso < n; paso++) {

        // k1 = h * f(t, y)
        f(t, y, k1);

        for (int i = 0; i < dim; i++) {

            k1[i] = h * k1[i];

        }
        
        // k2 = h * f(t + h/2, y + k1/2)
        for (int i = 0; i < dim; i++) {

            y_temp[i] = y[i] + 0.5 * k1[i];

        }

        f(t + h/2, y_temp, k2);

        for (int i = 0; i < dim; i++) {

            k2[i] = h * k2[i];

        }
        
        // k3 = h * f(t + h/2, y + k2/2)

        for (int i = 0; i < dim; i++) {

            y_temp[i] = y[i] + 0.5 * k2[i];

        }

        f(t + h/2, y_temp, k3);

        for (int i = 0; i < dim; i++) {

            k3[i] = h * k3[i];

        }
        
        // k4 = h * f(t + h, y + k3)

        for (int i = 0; i < dim; i++) {

            y_temp[i] = y[i] + k3[i];

        }

        f(t + h, y_temp, k4);

        for (int i = 0; i < dim; i++) {

            k4[i] = h * k4[i];

        }
        
        // Actualizamos la solución

        for (int i = 0; i < dim; i++) {

            y[i] = y[i] + (k1[i] + 2*k2[i] + 2*k3[i] + k4[i])/6;

        }

        t = t + h;
        
        if (paso % 10 == 0) {  // Imprime cada 10 pasos
        
            printf("%.6f\t%.6f\t%.6f\t%.6f\n", t, y[0], y[1], y[2]);
        }
    }
}

int main() {

  //Declaramos las variables 

    double t0 = 0.0;
    double y0[3] = {1.0, 1.0, 1.0};  // [x, y, z]
    double h = 0.01;
    int n = 1000;
    int dim = 3;
    
  Runge_Kuttak_4to_sistema(t0, y0, h, n, dim); //mandamos llamar a la función

    
}