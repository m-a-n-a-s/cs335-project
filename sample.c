// int foo(float x){
//     print_float(x);
//     print_string("\n");
//     return 1;
// }
// int main()
// {   
//     float arr[3];
//     float b=scan_float();
//     float a=1+1.2+b;
//     print_float(a);
//     // b=-7.9;
//     //  print_string("\n");
//     // print_float(b);
//     // print_string("\n");
//     // for(a=0;a<3;a=a+1){
//     //     arr[a]=scan_float();
//     // }
//     // for(a=0;a<3;a=a+1){
//     //     print_float(arr[a]);
//     //     print_string(" ");
//     // }
//     // print_string("\n");
//     // b=(1.1*(arr[0]+arr[1]-arr[2]))/3.14;
//     // //b=1.1+3.1;
//     // print_float(b);
//     // print_string("\n");
//     // if(3.14>6.6){
//     //     a=foo(1.0);
//     // }
//     // else{
//     //     a=foo(2.0);
//     // }
//     //print_float(a);
//     return 0;
// }

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
  len = scanf();
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
  //   arr[i]=scanf();
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
