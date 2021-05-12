int main()
{
    int arr[20];
    int i, c, d, n, len, t, u, k = 1;
    int d_lim, c_lim;
    int temp,j;
    print_string("Length of array : ");
    len = scan_int();
    print_int(len);
    print_string("\nEnter elements : ");
    i = 0;
    while(i < len){
        arr[i] = scan_int();
        i = i+1;
    }

    for (i = 0; i < len-1; i= i +1)  
        for (j = 0; j < len-i-1; j = j+1)
            if (arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        
    for (i = 0; i < len ; i = i + 1)
    {
        print_int(arr[i]);
        print_string(" ");
    }
    print_string("\n");
    return 0;
}
