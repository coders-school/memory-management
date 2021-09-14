int foo()
{
    double x[1'048'576];
    x[0] = 10;
    return 0;
}

int main()
{
    foo();
    return 0;
}