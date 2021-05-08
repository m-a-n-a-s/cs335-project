int main()
{
    int list[1000];
    //int T ;
    int i, c, d, n, len, t, u, k = 1;
    int d_lim, c_lim;
    // print_string("Enter the number of test cases : ");
    // T = scanf();
    // while(T){
    // T = T-1;
    print_string("Enter the length of the array (<=1000) : ");
    len = scanf();
    for (i = 0; i < len; i = i + 1)
    {
        list[i] = scanf();
    }
    print_string("Sorting the array............ \n");

    c_lim = len - 1;
    for (c = 0; c < c_lim; c = c + 1)
    {
        d_lim = c_lim - c;
        d = 0;
        while (d < d_lim)
        {
            k = d + 1;
            t = list[d];
            u = list[k];
            if (t < u)
            {
                list[d] = u;
                list[k] = t;
            }
            d = d + 1;
        }
    }
    for (i = 0; i < len - 1; i = i + 1)
    {
        print_int(list[i]);
        print_string(" ");
    }
    print_int(list[i]);
    print_string("\n");
    //}
    return 0;
}
