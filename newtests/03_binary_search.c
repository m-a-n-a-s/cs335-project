int main()
{
   int c, first, last, middle, n, search, array[100];
 
   print_string("Enter number of elements:\n");
   n = scanf();
 
   print_string("Enter the elements:\n");
 
   for (c = 0; c < n; c=c+1){
      array[c] = scanf();
   }
   print_string("Enter value to find:\n");
   search = scanf();
 
   first = 0;
   last = n - 1;
   middle = (first+last)/2;
 
   while (first <= last) {
      if (array[middle] < search)
         first = middle + 1;    
      else if (array[middle] == search) {
         print_int(search);
         print_string(" found at location ");
         print_int(middle+1);
         print_string("\n");
         break;
      }
      else
         last = middle - 1;
 
      middle = (first + last)/2;
   }
   if (first > last){
      print_string("Not found! ");
      print_int(search);
      print_string(" is not present in the list.\n");
  }
 
   return 0;   
}
