int f10(int a, int b, int c, int d, int e,
    int f, int g, int h, int i, int j) {
  return a+b+c+d+e+f+g+h+i+j;
}

int f9(int a, int b, int c, int d,
    int e, int f, int g, int h, int i) {
  return a+b+c+d+e+f+g+h+i;
}

int f8(int a, int b, int c, int d,
    int e, int f, int g, int h) {
  return a+b+c+d+e+f+g+h;
}

int main() {
  print_string("f8(1,2,3,4,5,6,7,8) = \n");
  print_int( f8(1,2,3,4,5,6,7,8));
  print_string("\nf9(1,2,3,4,5,6,7,8,9) = \n");
  print_int( f9(1,2,3,4,5,6,7,8,9));
  print_string("\nf10(1,2,3,4,5,6,7,8,9,10) = \n");
  print_int( f10(1,2,3,4,5,6,7,8,9,10));
  return 0;
}
