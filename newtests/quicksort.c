
int partition(int *arr, int start, int end)
{
  int pivot = arr[end];
  int i;
  int j = start - 1;
  int tmp;
  int k;
  for (i = start; i <= end - 1; i = i + 1)
  {
    if (arr[i] <= pivot)
    {
      j = j + 1;
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
    }
  }
  k = j + 1;
  tmp = arr[k];
  arr[k] = arr[end];
  arr[end] = tmp;
  return k;
}

int quicksort(int *arr, int start, int end)
{
  int p;
  if (start < end)
  {
    p = partition(arr, start, end);
    quicksort(arr, start, p - 1);
    quicksort(arr, p + 1, end);
  }
  return 1;
}

int main()
{ 
  int arr[100];
  int *a;
  int i,len, k;
  
  print_string("Input the length of the array : ");
  len = scanf();
  print_int(len);
  print_string("\n");
  print_string("Input the array elements :\n");
  for (i = 0; i < 6; i = i + 1)
  {
    arr[i]=scanf();
  }
  i = 0;
  a = &arr[i];
  quicksort(a, 0, len - 1);
  print_string("sorted array - \n");
  for (i = 0; i < len; i = i + 1)
  {
    k = arr[i];
    print_int(k);
    print_string(" ");
  }
  print_string("\n");

  return 0;
}
