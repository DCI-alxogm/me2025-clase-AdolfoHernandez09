/* Adolfo Hernández Ramírez 
  08-11-2025

  Tarea 16. Minimizar la función: 

  f(xi,yi) = 2xy + 2x - x^2- 2y^2

  con xi = -1 y yi = 1 
  
  Usando el método del gradiente, además de las aproximaciones de las derivadas
  por diferencias finitas centradas*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Definimos la funcion 

double f(double x, double y) {

    return 2*x*y + 2*x - x*x - 2*y*y;
} 

// Aquí calculamos la derivada parcial de f con respecto a x usando diferencias finitas centradas
//ya que hemos visto que centradas se aproxima más a la derivada real.

double dfx(double x, double y) {

    double h = 1e-6;  // Usaremos un paso pequeño para la derivada numérica

    //Regresa la derivada, usando la formula vista en clase

    return (f(x + h, y) - f(x - h, y)) / (2 * h);
}

// Ahora determinamos la derivada parcial de f con respecto a y.

double dfy(double x, double y) {

    double h = 1e-6; 
    return (f(x, y + h) - f(x, y - h)) / (2 * h);
}

// Declaramos la funcion g(h) = f(x_{i+1}, y_{i+1})

double g(double h, double x_actual, double y_actual) {

    double x_siguiente = x_actual + dfx(x_actual, y_actual) * h;
    double y_siguiente = y_actual + dfy(x_actual, y_actual) * h;
    return f(x_siguiente, y_siguiente);

}

// Determinamso la derivada de g(h) usando también diferencias finitas centradas

double derivada_g(double h, double x_actual, double y_actual) {

    double delta = 1e-6; 
    return (g(h + delta, x_actual, y_actual) - g(h - delta, x_actual, y_actual)) / (2 * delta);

}

// Esta funcion encontrara el h óptimo resolviendo g'(h) = 0 
//para ello usaremos el método de bisección.

double encontrar_h_optimo(double x_actual, double y_actual) {
    double h_bajo = -1.0;   // Límite inferior para h
    double h_alto = 1.0;   // Límite superior para h
    double h_medio;

    //aqui establezclo el maximo numero de iteraciones y la tolerancia de error para 
    //el método de bisección.

    int max_iter_biseccion = 50;
    double tol_biseccion = 1e-8;
    
    // Verificamos que haya cambio de signo en el intervalo

    double deriv_bajo = derivada_g(h_bajo, x_actual, y_actual);
    double deriv_alto = derivada_g(h_alto, x_actual, y_actual);
    
    //Aqui establecemos la condicion que se utiliza en el método
    if (deriv_bajo * deriv_alto > 0) {

        // Si no hay cambio de signo, usamos valor por defecto
        return 0.1;
    }
    
    // Metodo de biseccion para encontrar h donde g'(h) = 0

    for (int i = 0; i < max_iter_biseccion; i++) {
        h_medio = (h_bajo + h_alto) / 2.0;
        double deriv_medio = derivada_g(h_medio, x_actual, y_actual);
        
        if (fabs(deriv_medio) < tol_biseccion) {
            break;  // Si encontramos la raíz
        }
        
        if (deriv_bajo * deriv_medio < 0) {

            h_alto = h_medio;
            deriv_alto = deriv_medio;

        } else {

            h_bajo = h_medio;
            deriv_bajo = deriv_medio;

        }
    }
    
    return h_medio;
}

// Esta función es para resolver el problema con el Metodo del gradiente
void metodo_gradiente(double x_inicial, double y_inicial, int max_iteraciones, double tolerancia) {

    double x_actual = x_inicial;
    double y_actual = y_inicial;
    
    printf("******** MÉTODO DEL GRADIENTE ********\n");
    printf("Funcion: f(x,y) = 2xy + 2x - x^2 - 2y^2\n");
    printf("Punto inicial: (%.1f, %.1f)\n", x_inicial, y_inicial);
    printf("f(x_inicial, y_inicial) = %.6f\n\n", f(x_inicial, y_inicial));
    
    printf("Resolvemos el problema con Diferencias finitas centradas\n");
    printf("El paso para derivadas: h = 1e-6\n\n");
    
    for (int iteracion = 0; iteracion < max_iteraciones; iteracion++) {

        // Calculamos derivadas en el punto actual usando diferencias finitas

        double derivada_x = dfx(x_actual, y_actual);
        double derivada_y = dfy(x_actual, y_actual);
        
        // Encontramos el h óptimo resolviendo g'(h) = 0

        double h_optimo = encontrar_h_optimo(x_actual, y_actual);
        
        // Actualizamos las variables

        double x_siguiente = x_actual + derivada_x * h_optimo;
        double y_siguiente = y_actual + derivada_y * h_optimo;
        
        // se mostraran los resultados de la iteración

        printf("Iteración %d:\n", iteracion + 1);
        printf("  Punto actual: (%.6f, %.6f)\n", x_actual, y_actual);
        printf("  f(x,y) = %.6f\n", f(x_actual, y_actual));
        printf("  df/dx = %.6f, df/dy = %.6f\n", derivada_x, derivada_y);
        printf("  h óptimo = %.6f\n", h_optimo);
        printf("  Nuevo punto: (%.6f, %.6f)\n", x_siguiente, y_siguiente);
        printf("  f(nuevo) = %.6f\n", f(x_siguiente, y_siguiente));
        
        //  Calcularemos g(h) y g'(h) para mostrar el resultado en cada iteracion.

        double valor_g = g(h_optimo, x_actual, y_actual); //asociamos y guardamos el valor de las funciones en una variable
        double valor_derivada_g = derivada_g(h_optimo, x_actual, y_actual);
        printf("  g(h) = %.6f, g'(h) = %.6f\n", valor_g, valor_derivada_g);
        
        
        // Para la siguiente iteración
        x_actual = x_siguiente;
        y_actual = y_siguiente;
        
        printf("\n");

    }
    
    //mostramos los resultados finales 

    printf("Máximo de iteraciones alcanzado (%d)\n", max_iteraciones);
    printf("Mejor punto encontrado (x,y): (%.6f, %.6f)\n", x_actual, y_actual);
    printf("f(x,y) = %.6f\n", f(x_actual, y_actual));
}

int main() {

    // Declaramos las variables que son los parámetros del problema

    double x_inicial = -1.0;
    double y_inicial = 1.0;
    int max_iter = 20; //esto se puede cambiar por el ususraio pero lo dejo en 20
    //por que en el anterior ejercicio en clase fue suficiente con ese numero de iteracciones
    
    double tolerancia = 1e-6;

    //En el int main mandamos llamar a la funcion que resuelve el método,
    
    metodo_gradiente(x_inicial, y_inicial, max_iter, tolerancia);
    

}