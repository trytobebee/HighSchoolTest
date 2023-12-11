#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

double Quadra(double x, int a, int b, int c)
{
    return (double)a * x * x + b * x + c;
}

double SequencialSearch(int start, int end, int *a, int *b, int *c, int m, double& xVal)
{
    //针对这些函数从start-end进行评估
    double result = 1e10; //save the min value of max_Si
    double x = start;
    double search_interval = 0.1;
    double *y = new double[m];

    //sequencial search with limited precision
    while(x < end)
    {
        double s; //s = max(y_i)
        int pickedOne;

        for(int k = 0; k < m; k++)
        {
            y[k] = Quadra(x, a[k], b[k], c[k]);
        }

        s = y[0];
        pickedOne = 0;
        for(int k = 0; k < m; k++)
        {
            if(s < y[k])
            {
                s = y[k];
                pickedOne = k;
            }
        }
        //cout << pickedOne << " ";
        
        if(result > s)
        {
            result = s;
            xVal = x;
        }    

        x += search_interval;
    }
    return result;
}

double computeMaxSi(double x, int *a, int *b, int *c, int m)
{
    double *y = new double[m];
    double s; //s = max(y_i)
    for(int k = 0; k < m; k++)
    {
        y[k] = Quadra(x, a[k], b[k], c[k]);
    }

    s = y[0];
    for(int k = 0; k < m; k++)
    {
        if(s < y[k])
        {
            s = y[k];
        }
    }
    delete[] y;
    y = NULL;

    return s;
}

double Qua_Split_Search(int start, int end, int *a, int *b, int *c, int m, double &xVal)
{
    //针对这些函数从0-1000进行评估
    double result; //save the min value of max_Si   
    double left = start; //三分查找左右
    double right = end;
    double mid, leftmid, rightmid;
    double leftVal, rightVal, midVal, leftmidVal, rightmidVal;
    
    //sequencial search with limited precision
    while(true)
    {
        //计算左值
        leftVal = computeMaxSi(left, a, b, c, m);
        //计算右值
        rightVal = computeMaxSi(right, a, b, c, m);
        
        if(abs(left - right) < 1e-6 && abs(leftVal - rightVal) < 1e-8) //满足足够精度就结束了
        {
            result = leftVal;
            xVal = left;
            break;
        }

        //计算中位置
        mid = (left + right)/2;

        //计算左中值
        leftmid = (left + mid)/2;
        leftmidVal = computeMaxSi(leftmid, a, b, c, m);

        //计算右中值
        rightmid = (right + mid)/2;
        rightmidVal = computeMaxSi(rightmid, a, b, c, m);

        //裁定，更新左右，进入下一个循环
        if(leftmidVal < rightmidVal)
        {
            //舍弃右边的，因为右边的大，不应该是最小值所在的区域
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    return result;
}

double Tri_Split_Search(int start, int end, int *a, int *b, int *c, int m, double &xVal)
{
    //针对这些函数从0-1000进行评估
    double result; //save the min value of max_Si   
    double left = start; //三分查找左右
    double right = end;
    double leftTri, rightTri;
    double leftVal, rightVal, leftTriVal, rightTriVal;
    
    //sequencial search with limited precision
    while(true)
    {
        //计算左值
        leftVal = computeMaxSi(left, a, b, c, m);
        //计算右值
        rightVal = computeMaxSi(right, a, b, c, m);
        
        if(abs(left - right) < 1e-6 && abs(leftVal - rightVal) < 1e-8) //满足足够精度就结束了
        {
            result = leftVal;
            xVal = left;
            break;
        }

        //计算三分位点
        leftTri = left + (right-left)/3;
        leftTriVal = computeMaxSi(leftTri, a, b, c, m);

        //计算右中值
        rightTri = left + 2 * (right-left)/3;
        rightTriVal = computeMaxSi(rightTri, a, b, c, m);

        //裁定，更新左右，进入下一个循环
        if(leftTriVal < rightTriVal)
        {
            //舍弃右边的，因为右边的大，不应该是最小值所在的区域
            right = rightTri;
        }
        else
        {
            left = leftTri;
        }
    }
    return result;
}

int testTriSearch()
{
    int n; //组的数目
    cin >> n;
    double *min = new double[n];
    double *x = new double[n];

    for(int i =0 ; i < n; i++)
    {
        int m; //这组里面有多少个函数
        cin >> m;
        int * a = new int[m];
        int * b = new int[m];
        int * c = new int[m];
       

        for(int j = 0; j < m; j++)
        {
            cin >> a[j] >> b[j] >> c[j];
        }

        //show parameters
        // if(i == 5)
        // {
        //     for(int j = 0; j < m; j++)
        //     {
        //         cout << a[j] << " " << b[j] << " " << c[j] << " ";
        //     }
        // }
        //min[i] = SequencialSearch(0, 1000, a, b, c, m, x[i]);
        //min[i] = Qua_Split_Search(0, 1000, a, b, c, m, x[i]);
        min[i] = Tri_Split_Search(0, 1000, a, b, c, m, x[i]);
    }

    for(int i =0; i < n; i++)
    {
        printf("%.4f\n", min[i]);
    }
    
    return 0;
}