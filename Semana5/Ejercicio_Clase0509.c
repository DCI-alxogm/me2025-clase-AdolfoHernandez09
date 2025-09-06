//Ejercicio en clase del dia 05 de Septiembre del 2025
//Derivacion por diferencias finitas hacia adelante

//f(x) = x^3 -2x + 4

#include <stdio.h>
#include <math.h> 

float fx(float x); // Definiendo la funcion

int main(){

    float h = 0.25, a=-2, b=2;
    int n = (int) ((b-a)/h);
    int i=0;
    float x[n], fpa[n];

    //printf("%f %f\n",a,fx(a));
    //printf("%d", n);

    for(int i=0; i<n; i++) {

      x[i] = a + i*h;
      //printf("%f\n", x[i]);

    }

    for(int i=0; i<n; i++) {

      fpa[i] = ((fx(x[i+1])) - (fx(x[i])))/h;
      printf("%f %f\n", x[i], fpa[i]);

    }

   
  
   













    }

    float fx(float x) {
        float f;

        f = x*x*x -2*x +4;

        return f;
    }

