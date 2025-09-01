/* Adolfo Hernández Ramírez
   31-agosto-2024.

   Este es un programa que realiza las series de taylor para 5 diferentes
   funciones las cuales son las siguientes:

   1. Sen(x) 
   2. Cos(x) 
   3. e^-x
   4. Exp^2x. 
   5. Arctan(x). 

  Además se determina el error y el residuo de la serie. Es importante comentar
  que nuestra limitación sera de n<10; ya que solo consideraremos 10 derivadas 
  para cada función*/

#include <stdio.h>
#include <math.h>

//Tomando como base mi pseudocódigo, comenzaré por definir las 5 funciones de
//la siguiente manera.

double f1 (double x) {return sin(x);} //Función 1 es para el sen(x)
double f2 (double x) {return cos(x);} //Función 2 es para el cos(x)
double f3 (double x) {return exp(-x);} //Función 3 es para el exp^-x
double f4 (double x){return exp(2*x);}  //función 4 es la del exp^2x
double f5 (double x){return atan(x);} //atan es como se simboliza arctan

/******************** 10 DERIVADAS DE LAS FUNCIONES ******************************/

/********************* Sen(x) *****************************************/
double f1_d0 (double x){return sin(x);}
double f1_d1 (double x){return cos(x);}
double f1_d2 (double x){return -sin(x);}
double f1_d3 (double x){return -cos(x);}
double f1_d4 (double x){return sin(x);}
double f1_d5 (double x){return cos(x);}
double f1_d6 (double x){return -sin(x);}
double f1_d7 (double x){return -cos(x);}
double f1_d8 (double x){return sin(x);}
double f1_d9 (double x){return cos(x);}
double f1_d10 (double x){return -sin(x);}

/********************* cos(x) *****************************************/
double f2_d0 (double x){return cos(x);}
double f2_d1 (double x){return -sin(x);}
double f2_d2 (double x){return -cos(x);}
double f2_d3 (double x){return sin(x);}
double f2_d4 (double x){return cos(x);}
double f2_d5 (double x){return -sin(x);}
double f2_d6 (double x){return -cos(x);}
double f2_d7 (double x){return sin(x);}
double f2_d8 (double x){return cos(x);}
double f2_d9 (double x){return -sin(x);}
double f2_d10 (double x){return -cos(x);}


/********************* e^-x *****************************************/
double f3_d0 (double x){return exp(-x);}
double f3_d1 (double x){return -exp(-x);}
double f3_d2 (double x){return exp(-x);}
double f3_d3 (double x){return -exp(-x);}
double f3_d4 (double x){return exp(-x);}
double f3_d5 (double x){return -exp(-x);}
double f3_d6 (double x){return exp(-x);}
double f3_d7 (double x){return -exp(-x);}
double f3_d8 (double x){return exp(-x);}
double f3_d9 (double x){return -exp(-x);}
double f3_d10 (double x){return exp(x);}

/********************* e^2x *****************************************/
double f4_d0 (double x){return exp(2*x);}
double f4_d1 (double x){return 2*exp(2*x);}
double f4_d2 (double x){return 4*exp(2*x);}
double f4_d3 (double x){return 8*exp(2*x);}
double f4_d4 (double x){return 16*exp(2*x);}
double f4_d5 (double x){return 32*exp(2*x);}
double f4_d6 (double x){return 64*exp(2*x);}
double f4_d7 (double x){return 128*exp(2*x);}
double f4_d8 (double x){return 256*exp(2*x);}
double f4_d9 (double x){return 512*exp(2*x);}
double f4_d10 (double x){return 1024*exp(2*x);}

/********************* arctan(x) *****************************************/
double f5_d0 (double x){return atan(x);}
double f5_d1 (double x){return (1/(1+x*x));}
double f5_d2 (double x){return -2*x / pow(1 + x*x, 2);}
double f5_d3 (double x){return (6*x*x - 2) / pow(1 + x*x, 3);}
double f5_d4 (double x){return (-24*x*x*x + 24*x) / pow(1 + x*x, 4);}
double f5_d5 (double x){return (120*pow(x,4) - 240*x*x + 24) / pow(1.0 + x*x, 5);}
double f5_d6 (double x){return (-720*pow(x,5) + 2160*pow(x,3) - 720*x) / pow(1 + x*x, 6);}
double f5_d7 (double x){return (5040*pow(x,6) - 20160*pow(x,4) + 15120*x*x - 720) / pow(1 + x*x, 7);}
double f5_d8 (double x){return (-40320*pow(x,7) + 241920*pow(x,5) - 241920*pow(x,3) + 40320*x) / pow(1 + x*x, 8);}
double f5_d9 (double x){return (362880*pow(x,8) - 2721600*pow(x,6) + 5443200*pow(x,4) - 3225600*x*x + 40320) / pow(1 + x*x, 9);}
double f5_d10 (double x){return (-3628800*pow(x,9) + 36288000*pow(x,7) - 90720000*pow(x,5) + 72576000*pow(x,3) - 14515200*x) / pow(1 + x*x, 10);}

/*Aqui declarare la función factorial para calcular los factoriales presentes
en la serie de Taylor*/

double factorial(int n){
  double f = 1;  //inicializó la variable en 1
  for(int i = 1; i <= n; i++) { //declaramos i para el contador
  f *= i;
  }
    return f;

}

int main(){
  int repetir; //Esta variable sirve para que el usuario ejecute el programa mas de una vez

  do {

    int opcion; //Esta variable es para elegir la funcion deseada
    int n_lim; //n_lim es para que el usuario pueda meter el valor de n y que no rebase a 10;
    double x,x_i,h; //x es la funcion en la x que se desea evaluar y xi es igual 
  //al punto alrededor del cual se desarrolla la serie.

    printf("Este es un programa que determina las series de taylor de 5 funciones\n");
    printf("\n Selecciona una función f(x) \n");
    printf("1. Sen(x) \n");
    printf("2. Cos(x) \n");  
    printf("3. e^-x \n");
    printf("4. e^2x \n");
    printf("5. Arctan(x)\n");
    scanf("%d",&opcion);

    //Pedimos los valores de x y xi
    printf("Ingrese el valor de x\n");
    scanf("%lf",&x);
    printf("Ingrese el valor de xi\n");
    scanf("%lf",&x_i);

    h = x-x_i; //Definimos h como vimos en clase.

  /*Aqui pido que el usuario ingrese el valor de n*/

  printf("Ingresa el valor de n\n");
  scanf("%d",&n_lim);

  if(n_lim>=10){
    printf("La onceava derivada no esta considerada en este programa por lo tanto se usaran terminos hasta n=9.\n");
            n_lim = 9; //Declaramos que el valor limite de n_lim es hasta 9 derivadas
  }

  double (*df[11])(); //Recordamos que son 10 derivadas y el areglo sera con 11 elementos
  double(*funcion)(double); //Aqui declaré un arreglo para que funcion sea un arreglo 
  // que apunte a cualquier funcion de las 5 presentes

  switch(opcion){
  case 1: 
                df[0]=f1_d0; 
                df[1]=f1_d1; 
                df[2]=f1_d2; 
                df[3]=f1_d3; 
                df[4]=f1_d4;
                df[5]=f1_d5; 
                df[6]=f1_d6; 
                df[7]=f1_d7; 
                df[8]=f1_d8; 
                df[9]=f1_d9; 
                df[10]=f1_d10;
                funcion = f1;
                break;
            case 2:
                df[0]=f2_d0; 
                df[1]=f2_d1; 
                df[2]=f2_d2; 
                df[3]=f2_d3; 
                df[4]=f2_d4;
                df[5]=f2_d5; 
                df[6]=f2_d6; 
                df[7]=f2_d7; 
                df[8]=f2_d8; 
                df[9]=f2_d9; 
                df[10]=f2_d10;
                funcion = f2;
                break;
            case 3:
                df[0]=f3_d0; 
                df[1]=f3_d1; 
                df[2]=f3_d2; 
                df[3]=f3_d3; 
                df[4]=f3_d4;
                df[5]=f3_d5; 
                df[6]=f3_d6; 
                df[7]=f3_d7; 
                df[8]=f3_d8; 
                df[9]=f3_d9; 
                df[10]=f3_d10;
                funcion = f3;
                break;
            case 4:
                df[0]=f4_d0; 
                df[1]=f4_d1; 
                df[2]=f4_d2; 
                df[3]=f4_d3; 
                df[4]=f4_d4;
                df[5]=f4_d5; 
                df[6]=f4_d6; 
                df[7]=f4_d7; 
                df[8]=f4_d8; 
                df[9]=f4_d9; 
                df[10]=f4_d10;
                funcion = f4;
                break;
            case 5:
                df[0]=f5_d0; 
                df[1]=f5_d1; 
                df[2]=f5_d2; 
                df[3]=f5_d3; 
                df[4]=f5_d4;
                df[5]=f5_d5; 
                df[6]=f5_d6; 
                df[7]=f5_d7; 
                df[8]=f5_d8; 
                df[9]=f5_d9; 
                df[10]=f5_d10;
                funcion = f5;
                break;
            default:
                printf("Opcion invalida\n");
                continue;
  }

  double fx = funcion(x);
  double termino_n = 0; //esta variable simboliza el valor de f(x) usando la serie de 
  //Taylor inicial.

  printf("\nTABLA DE RESULTADOOOOOOOOOOOOOSSSSSSSSSS:\n");
  printf("n\tValor de f(x)\t f(x)_Aproximada\t\tResiduo\t\tError |f(x)-f(x)_aprox|\n");

  double x_e = (x + x_i)/2; //esta variable se usa para la formula del residuo 
  //donde se evalua la derivada en un punto medio entre x y x_i

  /*este ciclo for es para ir sumando los terminos de la serie de taylr*/
  for (int n = 0; n < 10; n++) {
            double termino_i = df[n](x_i) * pow(h, n) / factorial(n); 
            /*termino_i es el valor de los terminos correspondientes
            al numero de n*/
            termino_n += termino_i;

            //Usamos el residuo de lagrange tal y como se vio en clae
            double residuo = df[n+1](x_e) * pow(h, n+1) / factorial(n+1);
            double error = fabs(fx - termino_n);

            printf("%d\t%.8lf\t%.8lf\t\t%.8lf\t\t%.8lf\n", n, fx, termino_n, residuo, error);
        /*Este condicional permite que si el error alcanzo un valor de 0.000001 
        la serie de taylor se detenga automaticamente*/

            if(error < 1e-6){
                printf("El error menor a 1e-6 fue alcanzado en n=%d\n", n);
                break;
        }
  }

    printf("\n¿Deseas realizar otro calculo? (1=Si / 0=No)");
    if (scanf("%d", &repetir) != 1) repetir = 0; //si el usuario coloca 0 o cualquier numero que no sea 1, la condicional evalua el valor como 0
 
  }

  while (repetir ==1); 

  printf("El programa ha finalizadoooo \n");


}
