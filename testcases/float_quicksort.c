void swap(float* a, float* b){
    float t = *a;
    *a = *b;
    *b = t;
    return;
}

int partition(float *arr, int start, int end){
  float pivot = arr[end];
  int i;
  int j = start - 1;
  float tmp;
  int k;
  float *ptr1, *ptr2;
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
  //swap(&arr[k], &arr[end]);
  return k;
}

void quicksort(float *arr, int start, int end){
  int p;
  if (start < end){
    p = partition(arr, start, end);
    quicksort(arr, start, p - 1);
    quicksort(arr, p + 1, end);
  }
  return;
}

int main()
{ 
  float arr[100];
  float *a;
  int i,len;
  float k;
  
  print_string("Input the length of the array : ");
  len = scan_int();
  print_int(len);
  print_string("\n");
  print_string("Input the array elements :\n");
  i=0;
  while(i<len){
    arr[i] = scan_float();
    i = i+1;
  }
  // for (i = 0; i < len; i = i + 1)
  // {
  //   arr[i]=scan_int();
  // }
  i = 0;
  a = &arr[i];
  quicksort(a, 0, len - 1);
  print_string("sorted array - \n");
  for (i = 0; i < len; i = i + 1)
  {
    k = arr[i];
    print_float(k);
    print_string(" ");
  }
  print_string("\n");

  return 0;
}