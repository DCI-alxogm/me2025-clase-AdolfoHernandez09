#include<math.h>
#include<stdio.h>

int main(){

    float a,b,c;
    

    printf("Hola este es un programa para sumar y restar tres numeros\n");
    printf("Registra los tres numeros\n");
    scanf("%f %f %f",&a ,&b , &c);

    float suma = a + b + c;
    float resta = a - b - c;

    printf("La suma es %f \n",suma);
    printf("La resta es %f \n", resta);


}