double Quadra(double x, int a, int b, int c)
{
    return (double)a * x * x + b * x + c;
}

double SimpleMax(int a, int b, int c, int x1, int x2)
{
    double max = 0;
    double y1 = Quadra(x1, a, b, c);
    double y2 = Quadra(x2, a, b, c);
    max =  y1 > y2 ? y1 : y2;
    return max;
}


double getQuadraMax(int a, int b, int c, int start, int end)
{
    //get the max(q(x, a, b, c))
    double max = 0;
    if(a > 0)
    {
        max = SimpleMax(a, b, c, start, end);
    }
    else
    {
        //开口向下
        double mid = - (double)1.0 * b / a / 2;
        if(start <= mid && mid <= end)
        {
            max = Quadra(mid, a, b, c); //抛物线顶点
        }
        else
        {
            max = SimpleMax(a, b, c, start, end);
        }
    }

    return max;
}


double SimpleMin(int a, int b, int c, int x1, int x2)
{
    double min = 0;
    double y1 = Quadra(x1, a, b, c);
    double y2 = Quadra(x2, a, b, c);
    min =  y1 < y2 ? y1 : y2;
    return min;
}


double getQuadraMin(int a, int b, int c, int start, int end)
{
    //get the max(q(x, a, b, c))
    double min = 0;
    if(a > 0) //开口向上
    {
        double mid = - (double)1.0 * b / a / 2;
        if(start <= mid && mid <= end)
        {
            min = Quadra(mid, a, b, c); //抛物线顶点
        }
        else
        {
            min = SimpleMin(a, b, c, start, end);
        }
    }
    else
    {
        //开口向下
        min = SimpleMin(a, b, c, start, end);
    }

    return min;
}