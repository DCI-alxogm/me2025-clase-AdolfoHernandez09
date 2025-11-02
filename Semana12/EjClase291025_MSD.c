/* Adolfo Hernandez Ramirez
    Actividad en clase. hacer el código en c del método de la sección dorada para hallar un maximo o minimo

    En este caso mi funcion será 
    x^3 - 4x 
    donde en el rango de [-2,0] existe un máximo y en el rango de 0 a 2 un minimo

    29-10-2025 */

    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>

    //declaramos las funciones

    double f (double x){

      return pow(x,3) - 4*x;

    }


    int main() {

        float d = 0.61803; //este es el número "dorado"
        double xu, xL,x1,x2;
        int iter = 0;
        int opcion = 0;

        printf("Quieres hallar (1 = máximo, 2 = mínimo): ");
        scanf("%d", &opcion);
        
         // Definir intervalos según opción
        if (opcion == 1) {   // máximo

         printf ("Encontraremos el máximo de la función x3-4x\n");

            xL = -2;
            xu = 0;

        printf("En el intervalo inicial: [%.6f , %.6f]\n", xL, xu);



        } else {             // mínimo

         printf ("Encontraremos el mínimo de la función x3-4x\n");
        
            xL = 0;
            xu = 2;

        printf("En el intervalo inicial: [%.6f , %.6f]\n", xL, xu); 

        }


        //Definire los valores de x1 y x2

        x1 = xL + d*(xu-xL);
        x2 = xu -d*(xu-xL);


        //hacemos el condicional con un ciclo while.

        while (fabs(x1-x2)>0.001){

          iter++;

          if ((opcion == 1 && f(x1) > f(x2)) || (opcion == 2 && f(x1) < f(x2))) {
            xL = x1;
        } else {
            xu = x2;
        }

          
            x1 = xL + d*(xu-xL);
            x2 = xu -d*(xu-xL);

          }

          double x_opt= (xL + xu) / 2.0;
          double f_opt = f(x_opt);

          if(opcion==1) {

             printf("\n***** RESULTADO MÁXIMO *****\n");

          } else { 

             printf("\n***** RESULTADO MINIMO *****\n");

          }

      printf("Iteraciones: %d\n", iter);
      printf("Intervalo final: [%.6f , %.6f]\n", xL, xu);
      printf("x_opt ≈ %.6f\n", x_opt);
      printf("f(x_opt) ≈ %.6f\n", f_opt);

  }

   