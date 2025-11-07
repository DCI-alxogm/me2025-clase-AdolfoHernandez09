/* Adolfo Hernández Ramírez 
  05-11-2025

  En esta actividad de clase se nos pidio usar el método del gradiente para 
  minimizar la función 

  f(xi,yi) = 2xy + 2x - x^2- 2y^2

  con xi = -1 y yi = 1 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Definimos la función y sus derivadas respectivamente
double f(double x, double y) {
    return 2*x*y + 2*x - x*x - 2*y*y;
} 

double dfx(double x, double y) {
    return 2*y + 2 - 2*x;
}

double dfy(double x, double y) {
    return 2*x - 4*y;
}

// Función g(h) = f(x_{i+1}, y_{i+1})
double g(double h, double x_actual, double y_actual) {
    double x_siguiente = x_actual + dfx(x_actual, y_actual) * h;
    double y_siguiente = y_actual + dfy(x_actual, y_actual) * h;
    return f(x_siguiente, y_siguiente);
}

// Derivada de g(h) para la función específica f(x,y) = 2xy + 2x - x^2 - 2y^2
// Desarrollo analítico general:
// x_{i+1} = x_i + (2y_i + 2 - 2x_i) * h
// y_{i+1} = y_i + (2x_i - 4y_i) * h
// g(h) = f(x_{i+1}, y_{i+1})
// g'(h) se calcula derivando la expresión completa
double derivada_g(double h, double x_actual, double y_actual) {
    // Para la primera iteración con x = -1, y = 1:
    // df/dx = 6, df/dy = -6
    // x_{i+1} = -1 + 6h, y_{i+1} = 1 - 6h
    // g(h) = -180h^2 + 72h - 7
    // g'(h) = -360h + 72
    
    double dfdx = dfx(x_actual, y_actual);  // 6 para primera iteración
    double dfdy = dfy(x_actual, y_actual);  // -6 para primera iteración
    
    // Cálculo general de g'(h) para cualquier punto
    // Desarrollando analíticamente obtenemos:
    double term1 = 2 * dfdx * dfdy;
    double term2 = 2 * dfdx * y_actual;
    double term3 = 2 * dfdy * x_actual;
    double term4 = 2 * dfdx;
    double term5 = -2 * dfdx * (x_actual + dfdx * h);
    double term6 = -4 * dfdy * (y_actual + dfdy * h);
    
    return term1 * h + term2 + term3 + term4 + term5 + term6;
}

// Encuentra h óptimo resolviendo g'(h) = 0
// Para la primera iteración: g'(h) = -360h + 72 = 0 → h = 72/360 = 0.2
double encontrar_h_optimo(double x_actual, double y_actual) {
    double dfdx = dfx(x_actual, y_actual);
    double dfdy = dfy(x_actual, y_actual);
    
    // Para la función específica f(x,y) = 2xy + 2x - x^2 - 2y^2
    // La derivada g'(h) tiene la forma: A*h + B = 0
    // Donde A y B dependen de x_actual, y_actual, dfdx, dfdy
    
    // Desarrollando analíticamente:
    double A = 2 * dfdx * dfdy - 2 * dfdx * dfdx - 4 * dfdy * dfdy;
    double B = 2 * dfdx * y_actual + 2 * dfdy * x_actual + 2 * dfdx - 2 * dfdx * x_actual - 4 * dfdy * y_actual;
    
    // Resolvemos A*h + B = 0 → h = -B/A
    if (fabs(A) > 1e-10) {
        return -B / A;
    } else {
        // Si A es muy pequeño, usamos un valor por defecto
        return 0.1;
    }
}

// Método del gradiente
void metodo_gradiente(double x_inicial, double y_inicial, int max_iteraciones, double tolerancia) {
    double x_actual = x_inicial;
    double y_actual = y_inicial;
    
    printf("=== MÉTODO DEL GRADIENTE ===\n");
    printf("Función: f(x,y) = 2xy + 2x - x^2 - 2y^2\n");
    printf("Punto inicial: (%.1f, %.1f)\n", x_inicial, y_inicial);
    printf("f(x_inicial, y_inicial) = %.6f\n\n", f(x_inicial, y_inicial));
    
    printf("PRIMERA ITERACIÓN - Desarrollo analítico:\n");
    printf("df/dx(-1,1) = 2(1) + 2 - 2(-1) = 6\n");
    printf("df/dy(-1,1) = 2(-1) - 4(1) = -6\n");
    printf("x_{i+1} = -1 + 6h\n");
    printf("y_{i+1} = 1 - 6h\n");
    printf("g(h) = 2(6h-1)(1-6h) + 2(6h-1) - (6h-1)^2 - 2(1-6h)^2\n");
    printf("g(h) = -180h^2 + 72h - 7\n");
    printf("g'(h) = -360h + 72\n");
    printf("g'(h) = 0 → h = 72/360 = 0.2\n\n");
    
    for (int iteracion = 0; iteracion < max_iteraciones; iteracion++) {
        // Calcular derivadas en el punto actual
        double derivada_x = dfx(x_actual, y_actual);
        double derivada_y = dfy(x_actual, y_actual);
        
        // Encontrar h óptimo
        double h_optimo = encontrar_h_optimo(x_actual, y_actual);
        
        // Actualizar variables
        double x_siguiente = x_actual + derivada_x * h_optimo;
        double y_siguiente = y_actual + derivada_y * h_optimo;
        
        // Mostrar resultados de la iteración
        printf("Iteración %d:\n", iteracion + 1);
        printf("  Punto actual: (%.6f, %.6f)\n", x_actual, y_actual);
        printf("  f(x,y) = %.6f\n", f(x_actual, y_actual));
        printf("  df/dx = %.6f, df/dy = %.6f\n", derivada_x, derivada_y);
        printf("  h óptimo = %.6f\n", h_optimo);
        printf("  Nuevo punto: (%.6f, %.6f)\n", x_siguiente, y_siguiente);
        printf("  f(nuevo) = %.6f\n", f(x_siguiente, y_siguiente));
        
        // Verificar convergencia
        double distancia = sqrt(pow(x_siguiente - x_actual, 2) + pow(y_siguiente - y_actual, 2));
        double cambio_funcion = fabs(f(x_siguiente, y_siguiente) - f(x_actual, y_actual));
        
        printf("  Distancia movida: %.6f\n", distancia);
        printf("  Cambio en f(x,y): %.6f\n", cambio_funcion);
        
        if (distancia < tolerancia && cambio_funcion < tolerancia) {
            printf("\n¡CONVERGENCIA ALCANZADA!\n");
            printf("Mínimo encontrado en: (%.6f, %.6f)\n", x_siguiente, y_siguiente);
            printf("Valor mínimo: f(x,y) = %.6f\n", f(x_siguiente, y_siguiente));
            printf("Iteraciones totales: %d\n", iteracion + 1);
            return;
        }
        
        // Preparar siguiente iteración
        x_actual = x_siguiente;
        y_actual = y_siguiente;
        printf("\n");
    }
    
    printf("Máximo de iteraciones alcanzado (%d)\n", max_iteraciones);
    printf("Mejor punto encontrado: (%.6f, %.6f)\n", x_actual, y_actual);
    printf("f(x,y) = %.6f\n", f(x_actual, y_actual));
}

int main() {

    // Parámetros del problema
    double x_inicial = -1.0;
    double y_inicial = 1.0;
    int max_iter = 20;
    double tolerancia = 1e-6;
    
    // Ejecutar método del gradiente
    metodo_gradiente(x_inicial, y_inicial, max_iter, tolerancia);
    
    
}