/*Adolo Hernandez Ramirez
12-09-2023

Este es un código que usa el método de bisección para la función f(c) = (9.81 * 68.1) / c * (1 - exp(-(c / 68.1) * 10)) - 40
*/

#include <stdio.h>
#include <math.h>

//Definimos la funcion

float f(float c){
  return pow(c,10)-1;
}

int main(){
    float Err_max=0.0001;
    float a=0,b=1.3,error,kold=INFINITY,k, fk, Erroraprox; //Declaramos las variables.
    printf("raiz\t f(k)\t Error_aproximado \t Error\n");

    do{
        k=((f(b)*a)-(f(a)*b))/(f(b)-f(a));
        fk=f(k);
        
        if (f(k)*f(a)<0){

          b=k;

        }else{

          a=k;

        }
        
        Erroraprox=k-kold;
        error=fabsf(Erroraprox)/k;
        
        kold=k;
        printf("%f\t %f\t %f\t %f\n", k, fk, Erroraprox, error);

    } while (error>Err_max);

    printf("nLa ráiz aproximada es:%f\n", k);
    printf("f(c_raíz)=%f\n", f(k));
    
}

