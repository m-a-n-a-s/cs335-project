int main()
{
   int index;
   int start;
   int end;
   int mid;
   int len;
   int num;
   int arr[20];
   int res = -1;
 
   print_string("Length of arr :\n");
   len = scan_int();
 
   print_string("Enter the elements:\n");
   index= 0;
   while(index < len){
      arr[index] = scan_int();
      index = index + 1;
   }

   print_string("Enter a number:\n");
   num = scan_int();
 
   start = 0;
   end = len - 1;
   mid = (start+end)/2;

   while (start <= end) {
      if (arr[mid] < num)
         start = mid + 1;    
      else if (arr[mid] == num) {
         res = mid;
         break;
      }
      else
         end = mid - 1;
 
      mid = (start + end)/2;
   }

   if(res == -1) print_string("Not found\n");
   else{
      print_string("Found at index : ");
      print_int(res);
      print_string("\n");
   }
 
   return 0;   
}
