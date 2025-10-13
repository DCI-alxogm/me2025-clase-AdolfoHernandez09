//Este es elcodigo de gauss que se presento en clase 
//El dia viernes 10-10-2025

//Adolfo Hernandez Ramirez

#include <stdio.h>
 
int main() {
  double A[3][3]={
    {3, -0.1, -0.2},
    {0.1, 7, -0.3},
    {0.3, 0.2, 10}
  };
  double B[3]={7.85, -19.3, 71.4};
  double X[3];
  double factor, suma;
  int n, m, k;

  for (k=0; k<2; k++) {
    for (n=k+1; n<3; n++) {
        factor=A[n][k]/A[k][k];
        for (m=k; m<3; m++) {
            A[n][m]=A[n][m]-factor*A[k][n];
        }
        B[n]=B[n]-factor*B[k];
      }
    }
 
  for (n=2; n>=0; n--) {
      suma=0;
      for (m=n+1; m<3; m++) {
          suma+=A[n][m]*X[m];
      }
      X[n]=(B[n]-suma)/A[n][n];
    }
  printf("Soluciones del sistema:\n");
    for (n=0; n<3; n++) {
      printf("X%d = %.6f\n", n+1, X[n]);
    }

}