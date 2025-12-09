/* Adolfo Hernández Ramírez
  08-12-2025

  Para una reacción que puede modelarse como A+B ---> 2B 

  El modelo cinético que describe la concentración del producto se describe 
  mediante la ecuación logistca

  dC/dt= k C(t) (Cmax - C(t)) 

  donde C(t) es la concentración del producto
  k la constante cinética 
  Cmax la concentración máxima alcanzada 

  Para un reactor con C(0)= 0.02 mol/L , con parámetros cinéticos 
  k=0.45 L*mol^-1*min^-1 y Cmax= 1 mol/L  

  
  Predice la concentración de producto como función del tiempo en el intervalo 
  de 0 a 25 min, usando un método de Runge Kutta de cuarto orden con \delta 
  t =0.1 compara tu resultado con el método de segundo orden.


  */

  //Declaración de las bibliotecas que usaremos
  #include <stdio.h>
  #include <math.h>


  //Declaramos los parámetros del modelo logístico
  double k = 0.45; //constante cinetica
  double C_max = 1.0; //Concentración máxima alcanzada

  //Ahora definimos la función logística del problema
  double f(double t, double C){
    
    return k * C * (C_max-C);
  
  }

  /*Declaro una función para que almacene todo el procedimiento
  o algoritmo corresponfdiente al métod de Runge Kutta de 2do ORden
  */
  
  /*************** RK 2do Orden **********************************/

  void RK_2do (double t0, double C_0,  double h, int n){

  //Declaramos t,C,k1 y k2

  double t=t0;
  double C = C_0;
  double k1,k2;


  printf("Resultados usando el método de Runger Kutta de 2do Orden\n");
  printf("\nConcentración de Producto como Función del Tiempo en Intervalos de 0 a 25 min\n");
  printf("t(min)\t\tC(t) mol/L\n");
  printf("------------------------------------------------------------\n");

  printf("%.4f\t\t%.6f\n", t, C);
  
  /*Ciclo for que sirve para calcular k1, k2 y posteriormente C y t usando el
  método de Runger-Kutta*/

  for(int i=0; i<n; i++){

    //Cálculo de k1 y k2
    k1 = h * f(t,C);
    k2 = h * f( t + h/2, C + k1/2);

    //determinación de C y t
    C = C + k2;
    t = t + h;

    printf("%.4f\t\t%.6f\n", t, C);

  }

  }

   /*************** RK 2do Orden **********************************/
   void RK_4to(double t0, double C_0, double h, int n) {

    //Definimos los parametros que son necesarios para el uso del método

    double t = t0;
    double C = C_0;
    double k1,k2,k3,k4; 

    printf("\nResultados usando el método de Runger Kutta de 4to Orden\n");
    printf("\nConcentración de Producto como Función del Tiempo en Intervalos de 0 a 25 min\n");
    printf("t(min)\t\tC(t) mol/L\n");
    printf("------------------------------------------------------------\n");

    printf("%.4f\t\t%.6f\n", t, C);


    /*De igual manera se necesita de u ciclo for para llevar
    a cabo el método*/

    for(int i = 0; i<n; i++){

      //Cálculo de las k´s
      
      k1 = h * f(t, C);
      k2 = h * f(t + h/2.0, C + k1/2.0);
      k3 = h * f(t + h/2.0, C + k2/2.0);
      k4 = h * f(t + h, C + k3);
      
      //Deyterminamos los valores de C y t.
      
      C = C + (k1 + 2*k2 + 2*k3 + k4)/6.0;
      t = t + h;

      printf("%.4f\t\t%.6f\n", t, C);
      
    }

   }


   int main(){
    

    double t0 = 0.0;
    double C_0 = 0.02; //Declaramos el valor de la concentración inicial.
    double h = 0.1;

    int n = (25.0 / 0.1);   // pasos para llegar a 25 min

    // Ejecutar ambos métodos
    RK_2do(t0, C_0, h, n);
    RK_4to(t0, C_0, h, n);



     /*******************BÚSQUEDA DEL \deltat NECESARIO PARA QUE RK2 ≈ RK4****** */

    printf("\n\nBuscando deltat necesario para que RK2 coincida con RK4\n");

    double h_test = 0.1;
    double t_final = 25.0;

    // Cálculo RK4 con h=0.1 (referencia)

    double C_RK4_ref = C_0;
    double t_temp = t0;
    for(int i=0; i<n; i++){

        //Calculamos k´s con el C de referencia
        double k1 = h * f(t_temp, C_RK4_ref);
        double k2 = h * f(t_temp + h/2.0, C_RK4_ref + k1/2.0);
        double k3 = h * f(t_temp + h/2.0, C_RK4_ref + k2/2.0);
        double k4 = h * f(t_temp + h,     C_RK4_ref + k3);

        C_RK4_ref = C_RK4_ref + (k1 + 2*k2 + 2*k3 + k4)/6.0;
        t_temp = t_temp + h;
    }

    

    while(h_test > 1e-6){  // Reduciremos deltat mientras sea mayor a 0.000001

        double C_RK2_test = C_0;
        double t_aux = t0;
        int pasos = (int)(t_final / h_test);

        for(int i=0; i<pasos; i++){

            double k1 = h_test * f(t_aux, C_RK2_test);
            double k2 = h_test * f(t_aux + h_test/2.0, C_RK2_test + k1/2.0);
            C_RK2_test = C_RK2_test + k2;
            t_aux = t_aux + h_test;

        }

        double error = fabs(C_RK2_test - C_RK4_ref);

        printf("deltat = %.6f   error = %.10f\n", h_test, error);

        // Si el error es suficientemente pequeño, ya encontramos el Δt adecuado

        if(error < 1e-5){

            printf("\n deltat necesario para que RK2 coincida con RK4 es: %.6f\n", h_test);
            break;
        }

        h_test /= 2.0; //Si aún no es asi vamos reduciendo el paso
    }

   }

   
