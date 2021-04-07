void bubble(char *items, int count)
{
  int i, j;
  char t;

  for(i = 1; i < count; ++i)
    for( j = count-1; j >= i; --j) {
      if(items[j - 1] > items[ j ]) {
        /* exchange elements */
        t = items[j - 1];
        items[j - 1] = items[ j ];
        items[ j ] = t;
      }
    }
}

int main(void)
{
  char s[255];

  //printf("Enter a string:");
  //gets(s);
  bubble(s, strlen(s));
  //printf("The sorted string is: %s.\n", s);

  return 0;
}



