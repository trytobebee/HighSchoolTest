#include<iostream>
#include<cstdio>
#include<cstring>
#include "largeNum.h"
using namespace std;

bool isBiggerB(char* a, char* b, int lenA, int lenB)
{
    //确定一下是否b比a大
    bool biggerB = false;
    if(lenA == lenB)
    {
        string stra(a);
        string strb(b);
        if(stra == strb)
        {
            cout << 0; 
            return 0;
        }
        
        biggerB = strb > stra;
    }
    else
    {
        //a < b, 那么就用 b-a
        biggerB = lenB > lenA;
    }

    return biggerB;
}

//两个数字数组相加，并且进行按照进制的进位, 结果保存在a中
void Addition(int* a, int* b, int& length, int scale)
{
    for(int i = 0; i < length; i++)
    {
        a[i] += b[i];
        a[i+1] += a[i]/scale;
        a[i] = a[i] % scale;
    }

    if(a[length])
        length++;
}

//a - b, 只支持a > b的
int Subtraction(int* a, int* b, int length, int scale)
{
    // // char a[500] = {}; //字符串存储
    // // char b[500] = {};
    
    // int lenA=strlen(a);
    // int lenB=strlen(b);
    // int l = lenA > lenB ? lenA : lenB; //决定要操作的位数    
    // int* j = new int[l];
    // int* k = new int[l];
    
    // bool biggerB = isBiggerB(a, b , lenA, lenB);
    // if(!biggerB)
    // {
    //     constructBigNum(lenA, a, j); //把a放到j里面。
    //     constructBigNum(lenB, b, k); //把b放到k里面。
    // }
    // else
    // {
    //     constructBigNum(lenB, b, j); //把b放到j里面，b大作为被减数
    //     constructBigNum(lenA, a, k); //把a放到k里面。
    // }
    
    //by default a > b
    //prepare 被减数，提前借位好
    for(int p = 0; p<length-1; p++)
    {
        a[p] += scale;
        a[p+1] -= 1;
    }

    //相减
    for(int p=0;p<length;p++)
    {
        a[p]-=b[p];
    }
    
    //将多余的借位还回去
    for(int p=0;p<length;p++)
    {
        if(a[p]>=scale)
        {
            a[p+1]++;
            a[p]=a[p] % scale;
        }
    }

    // //输出
    // if(a[length-1]!=0)
    //     outputL(length, a);
    // else
    //     outputL(length-1, a);
    // cout<<endl;

    return 0;
}


int multiply_large(int* s, int valx, int& length)
{
    //为s中每个位置乘以valx
    for(int i = 0; i < length; i++)
    {
        s[i] = s[i] * valx;
    }

    for(int i = 0; i < length; i++)
    {
        if(s[i]>=10)
        {
            s[i+1]+=s[i]/10;
            s[i]=s[i]%10;
        }

    }
    while(s[length]>0)
    {
        if(s[length]>=10)
        {
            s[length+1]+=s[length]/10;
            s[length]=s[length]%10;
        }
        length++;
    }
    return length;
}

int Multiply_Large_Large(int* a, int* b, int* c, int lengthA, int lengthB)
{
    for(int i = 0; i < lengthB; i++)
    {
        for(int j = 0; j < lengthA; j++)
        {
            c[i+j] += a[j] * b[i];
        }
    }       

    lengthA = lengthA + lengthB - 1;

    for(int i = 0; i < lengthA; i++)
    {
        c[i+1] += c[i] / 10;
        c[i] = c[i] % 10;
    }

    while(c[lengthA]>0)
    {
        if(c[lengthA]>=10)
        {
            c[lengthA+1]+=c[lengthA]/10;
            c[lengthA]=c[lengthA]%10;
        }
        lengthA++;
    }

    return lengthA;
}

//高精度除以低精度
long long Divide_Large(int* val, int& length, int b, int* result)
{   
    //默认result 和 val的空间已经分配，长度超过length
    memset(result, 0, sizeof(int)*length);
    long long m = 0;

    for(int i = length-1; i >= 0; i--)
    {
        long long temp = m * 10 + val[i];
        result[i] = temp / b;
        m = temp % b;
    }

    for(int i = length-1; i >0; i--)
    {
        if(result[i] != 0)
        {
            length = i + 1; //确定真实的商的长度
            break;
        }
    }
    return m;
}

//compute x^y
int PowerL(int x, int y, int* val, int& length)
{
    memset(val, 0, sizeof(int) * length); //initial
    length = 1;
    val[0] = 1;
    
    //compute x^y
    for(int i = 0; i < y; i++)
    {
        multiply_large(val, x, length);
    }

    return length;
}

//m by default -1 means compute the full factorial of n
//otherwise any number >0 & <n means compute partial factorial n*(n-1)....(n-m+1)
int FactorialL(int n, int* val, int& length, int m)
{
    memset(val, 0, sizeof(int) * length); //initial
    length = 1;
    val[0] = 1;
    
    if(m == -1)
        m = n;
    else if(m <-1 || m > n)
    {
        printf("illegal parameter, m > n or m < 0\n");
        return -1;
    }   
    
    for(int i = n; i > n-m; i--)
    {
        multiply_large(val, i, length);
    }

    return 0;
}

//c(n,m) = n! / (m! (n-m)!)
int Combo(int n, int m, int* val, int length)
{
    //n > m
    //先用组合性质c(m,n) = c(m, m-n), 找一个更容易算的
    if(m > n/2)
        m = n - m;

    int resultlen = length;
    
    //c(n,m) = n! / (m! (n-m)!)
    //可简化为 n*(n-1)*...(n-m+1)/m!
    //分子n*(n-1)*...(n-m+1)/m!典型的高精度*单精度， 用函数factorialL计算
    FactorialL(n, val, resultlen, m);

    //新建一个buf用来存除法结果
    int* result = new int[length];

    //除以m!,可以循环进行高精度除以低精度
    for(int i = m; i > 1; i--)
    {
        memset(result, 0, length* sizeof(int)); //每次提前将将结果初始为0；
        int remain = Divide_Large(val, resultlen, i, result);
        if(remain != 0)
        {
            printf("failed exact divide!\n");
            return -1;
        }   

        //注意此处进行内存替换，保证循环一直是 valueA / i 进行计算。
        int* temp = val;
        val = result;
        result = temp;
    }

    //outputL(resultlen, valueA);
    return 0;
}