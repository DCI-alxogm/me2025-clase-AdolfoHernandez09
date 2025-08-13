#include <math.h>
#include <stdio.h>

int main()
{

  float a=3,b=4,c=5,d=7;
  float e1,e2,e3,e4;

    e1= (a+b)*c/d;
    e2= ((a+b)*c)/d;
    e3= a+(b*c)/d;
    e4 = a+b*c/d;

    printf("e = (a+b)*c/d = %f\n",e1);
    printf("e = ((a+b)*c)/d = %f\n",e2);
    printf("e = a+(b*c)/d = %f\n",e3);
    printf("e = a+b*c/d = %f\n",e4);

} 