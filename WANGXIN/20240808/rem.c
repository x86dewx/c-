int rem(int a,int b)
{
    return a % b;
}

int pow(int a,int b)
{
    int c =1;
    for(int i = 0;i < b;++i)
    {
        c *= a;
    }
    return c;
}
