int ackermann(int a, int l)
{
  int k;
  if (a == 0)
    return l + 1;
  if ((a > 0) && (l == 0))
    return ackermann(a - 1, 1);
  if (a > 0 && l > 0)
  {
    k = ackermann(a, l - 1);
    return ackermann(a - 1, k);
  }
  return 1;
}

int main()
{
  int m, n;
  print_string("Input m : ");
  m = scanf();
  print_string("Input n : ");
  n = scanf();
  print_string("The Ackermann value is : ");
  print_int(ackermann(m, n));
  print_string("\n");
  return 0;
}
