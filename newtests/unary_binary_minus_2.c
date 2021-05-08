int main() {
  int n;
  n = -1;     // -1
  n *= -1;    //  1
  n = n + 5;  //  6
  n = -n;     // -6
  n = n / -2; //  3
  n = n + -1; //  2
  print_string("n = ");
  print_int(n);
  print_string("\n");
  if (n == 2) {
    print_string("Test successful\n");
  } else {
    print_string("Test failed\n");
  }
  return 0;
}
