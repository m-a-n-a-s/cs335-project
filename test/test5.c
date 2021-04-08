// A program to convert  from decimal

int main()
{
  int n,k=1;

  //n = 69420; // Binary of the number n would be stored in binary array

  char binary[32];

  int c;
  for (c = 31; c >= 0; c--)
  {
    k = n >> c;

    if (k & 1)
      binary[31-c] = '1';
    else
      binary[31-c] = '0';
  }

//   for(int i = 0 ; i < 32 ; i++) printf("%c",binary[i]);
  
  return 0;
}


/* A program to find 
roots of a quadratic equation */
 
// Prints roots of quadratic equation ax*2 + bx + x
// void findRoots(int a, int b, int c){
    
//     int D = (int)pow((double)b,2.0) - 4*a*c;
//     double sqrt_val = sqrt(abs(D));
//     if (a == 0) {
//         printf("It is not a Quadratic Equation\n");
//         return;
//     }
 
//     if(D > 0){
//         printf("Roots are real and different \n");
//         printf("%f\n%f\n", (double)(-b + sqrt_val) / (2 * a), (double)(-b - sqrt_val) / (2 * a));
//     }
//     else if (D == 0) {
//         printf("Roots are real and same \n");
//         printf("%f\n", -(double)b / (2 * a));
//     }
//     else // D < 0
//     {
//         printf("Roots are complex \n");
//         printf("%f + i%f\n%f - i%f\n", -(double)b / (2 * a), sqrt_val, -(double)b / (2 * a), sqrt_val);
//     }
// }
 
// int main()
// {
//     int a,b,c;
//     printf("Give the three coefficients :\n");
//     scanf("%d %d %d", &a, &b, &c);
//     findRoots(a, b, c);
//     return 0;
// }

