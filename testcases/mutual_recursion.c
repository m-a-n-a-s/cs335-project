int odd(int n) {}
int even(int n) {}

int main()
{

  int n;

  print_string("Enter number:\n");
  n = scan_int();
  print_string("odd: ");
  print_int(odd(n));
  print_string("\n");
  print_string("even: ");
  print_int(even(n));
  print_string("\n");

  return 0;
}

int even(int n)
{
  if (n == 0)
    return 1;
  else
    return odd(n - 1);
}

int odd(int n)
{
  if (n == 0)
    return 0;
  else
    return even(n - 1);
}
