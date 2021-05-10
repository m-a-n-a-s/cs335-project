int ack(int var1, int var2){
  int k;
  if (var1 == 0) return var2 + 1;
  else if ((var1 > 0) && (var2 == 0)) return ack(var1 - 1, 1);
  else if (var1 > 0 && var2 > 0){
    k = ack(var1, var2 - 1);
    return ack(var1 - 1, k);
  }
}

int main()
{
  int var = ack(1, 2);
  if(var == 4) print_string("ackermann working!!!\n");
  else print_string("ackermann not working\n");
  return 0;
}
