// A program to convert  from decimal

int main()
{
  int n=10,k=1;

  
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

  return 0;
}

