/* Adolfo Hernández Ramírez
04-Septiembre-2025

Este es un codigo en c que resuelve la derivacion numérica
de una función, cuyos valores de la función en diferentes puntos 
se conocen*/

#include <stdio.h>
#include <math.h>

int main(){

  //Primero defino las variables de x y las funciones

  float x_imenos1 = 0, x_i = 0.5, x_imas1=1;
  float f_ximenos1 = 1.2, f_xi = 0.925, f_ximas1 = 0.2;

  /* considerando que en la toma de los puntos x, siempre existe la misma distancia 
  h = 0.5, declaramos la variable para simplificar el cálculo*/

  float h = x_i-x_imenos1;

  //Formulas para la derivación númerica.

  //Diferencia hacia atras

  float df_atras = (f_xi - f_ximenos1)/(h);

  //Diferencia centrada

  float df_centrada = (f_ximas1-f_ximenos1)/(2*h);

  //Diferencia hacia adelante

  float df_adelante = (f_ximas1-f_xi)/h;

  //errores relativos;

  float df_real = -0.9215;

  float error_atras = (df_real-df_atras)/df_real;
  float error_centrada = (df_real-df_centrada)/df_real;
  float error_adelante = (df_real-df_adelante)/df_real;


  //Impresion de resultados 

  printf("\t\t **************** RESULTADOS *************** \n\n");
  printf("\t\t x\t\t f'(x)_Atras \t f'(x)_Centrada \t f'(x)_Adelante\n\n");
  printf("\t\t 0.5\t\t %0.2f \t\t %0.2f \t\t\t %0.2f\n\n", df_atras,df_centrada,df_adelante);
  printf("\t\tErrores\t\t %0.2f \t\t %0.2f \t\t\t %0.2f \n\n", error_atras,error_centrada,error_adelante);





}