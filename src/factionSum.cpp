#include <iostream>
#include "mathfunc.h"
using namespace std;

//b1/a1 + b2/a2
int FractionSum(int a1, int b1, int a2, int b2)
{
    int factor1, factor2;
    if(a1 == a2)
    {
        factor1 = factor2 = 1;
    }
    else
    {
        factor1 = a2; 
        factor2 = a1;
    }

    int A, B;
    A = b1 * factor1 + b2 * factor2;
    B = a1 * factor1;

    int C; //整数部分
    C = A / B;

    A = A - C * B; //真分子
    
    //如果有则输出整数部分
    if(C > 0)
    {
        cout << C;
        if(A > 0)
            cout << "+";
    }    
    
    if(A == 0)
        return 0;

    //分子、分母求最大公因子并约分
    int cofactor = mathfunc::GetMaxCofactor(A, B);
    
    cout << A/cofactor << "/" << B/cofactor;
    return 0;
}