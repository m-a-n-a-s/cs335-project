int main()
{
    int n = 2;
    int **a = &(&n);
    int b = **a;
    return 0;
}
