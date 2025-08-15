#include <stdio.h>
#include <math.h>

int main(){

  int x1,x2,xi1,xi2,a,b,c;
  xi1 = 0;
  xi2 = 0;
  float discr;

  printf("Este es un código donde puedes encontrar las raices de un trinomio ax^2 + bx +c =0\n");
  printf("Ingresa los valores de a,b y c");
  scanf("%d %d %d\n",&a,&b,&c);

    if(a==0){
      if(b==0){
        printf("La solución es trivial\n");
      
      } else{
        x1=-c/b;
        printf("X = %d",x1);
      }
    } else {
      discr = b*b -4*a*c;

          if(discr>=0){

            x1 = (b+sqrt(discr))/2*a;
            x2 = (b-sqrt(discr))/2*a;

          } else {
            printf("Las raices son complejas\n");
            
            float x1r = b/2*a; //esta es la parte real de la solución
            xi1 = sqrt(abs(discr));

            printf("La raíz es %f + %fi",x1r,xi1);

        

          } 
    }


}