/* Adolfo Hernández Ramírez

  Ejercicio Clase 05-11-2025. Realizar un código en c para resolver la función

  f(x,y) = 2xy + 2x -x^2 - 2y^2

  mediante el método del gradiente.

  */

  //Declaramos las derivadas parciales

  double parcialfx (double x, double y) {

    return 2*y +2 -2*x;

  }

  double parcialfy (double x, double y){

    return 2*x-4*y;

  }

  //Declaramos la función g(h)

  double g (double x, y) {

    return 2*x*y +2*x - x*X -2*y*y;

  }

  int main(){

    //declaro variables 

    double xi = -1, yi = 1;
    double ximas1, yimas1; 
    double h;

    do { 

      ximas1 = xi + parcialfx(xi,yi) * h;
      yimas1 = yi + parcialfy(xi,yi)*h;

      //despues los cvalores de ximas1 y yimas1 los colocamos en la funcion g que depende h 
      
      //esa funcion le sacmos la derivada y donde g´(h) = 0 entonces ese valor de h vuelve a la primera formula de xi+1 y yi+1 y realizamos lo mismos pasos hasta que h sea igual o cercano a 0 

    }
  }
