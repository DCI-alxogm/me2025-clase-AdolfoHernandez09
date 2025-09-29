/*Adolfo Hernandez Ramirez 
28-09-2025

EJERCICIO 7.*/

#include <stdio.h>
#include <math.h>

// Función f(T) = ln(osf) - [ -139.34 + 1.575701e5/T - 6.642309e7/T^2 - 8.621949e11/T^4 ]
double funcion(double T, double osf) {
    double rhs = -139.34 + 1.575701e5/T - 6.642309e7/(T*T) - 8.621949e11/(T*T*T*T);
    return log(osf) - rhs;
}

int main() {
    double osf;
    double a, b, m;   // extremos y punto medio
    double fa, fb, fm;
    int i;

    printf("Metodo de biseccion para calcular la temperatura (°C)\n");
    printf("Introduce la concentracion de oxigeno disuelto (mg/L): ");
    scanf("%lf", &osf);

    // Intervalo de 0 a 40 °C en Kelvin
    a = 273.15; 
    b = 313.15;

    fa = funcion(a, osf);
    fb = funcion(b, osf);

    if (fa * fb > 0) {
        printf("No hay cambio de signo en el intervalo. Intenta otro valor.\n");
        return 0;
    }

    // Bisección
    for (i = 0; i < 100; i++) {
        m = (a + b) / 2.0;
        fm = funcion(m, osf);

        if (fa * fm < 0) {
            b = m;
            fb = fm;
        } else {
            a = m;
            fa = fm;
        }

        if (fabs(b - a) < 1e-6) break;
    }

    printf("\nTemperatura encontrada: %.4f K\n", m);
    printf("Equivalente en grados Celsius: %.4f °C\n", m - 273.15);

    }