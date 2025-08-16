/*Adolfo Hernandez Ramirez
16-08-2025

Tarea #1 Evaluar si un numero es par o impar en un codigo en C.

*/
#include <stdio.h>
#include <math.h>

int main(){

  int numero;
  int opcion =1; /*esta variable es para registrar la respuesta del 
  usuario al preguntarle si quiere volver a evaluar otro numero*/


  printf("Este es un programa que te indica si un número es par o impar\n");
  
  while (opcion==1){

  printf("Por favor ingresa un número entero\n");
  scanf("%d",&numero);

  if(numero%2==0){
    printf("El numero %d es par\n",numero);

  } else{
    printf("El numero %d es impar\n",numero);

  }
    printf("¿Deseas ingresar un nuevo numero? Escribe 1=si o 0=no\n");
    scanf("%d",&opcion);

  }
  printf("El programa ha terminado :)\n");

}
