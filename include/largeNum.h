#pragma once

#include <iostream>
using namespace std;

//输出大数字，去掉前导零不输出，如果整个序列都是0， 那么就输出一个0
inline void outputL(int length, int* v)
{
    bool startZero = true;
    for(int p=length-1;p>=0;p--)
    {
        if(v[p] == 0 && startZero)
        {
            //不输出
        }
        else if(v[p] != 0)
        {
            cout<<v[p];
            startZero = false;
        }
        else
        {
            cout << v[p];
        }     
    }
}

// deprecated, please use inputProc.h -> 
// Map2IntArray(char *str, int* a, int& length, bool reverse = false)

// //从输入的string，存到int*数组中，并倒序
// inline void constructBigNum(int length, char* strv, int* v)
// {
//     //存入int数组，这里可以用int8优化
//     for(int p=0;p<length;p++)
//     {
//         v[p]=strv[p]-'0';
//     }
    
//     //倒序排列，低位在前，方便运算对齐
//     for(int p=0;p<length/2;p++)
//     {
//         int tmp = v[p];
//         v[p]= v[length-1-p];
//         v[length-1-p] = tmp;
//     }
// }


void Addition(int* a, int* b, int& length, int scale);
int Subtraction(char* a, char* b);
int FactorialL(int n, int* val, int& length, int m = -1);
long long Divide_Large(int* val, int& length, int b, int* result);
int Multiply_Large_Large(int* a, int* b, int* c, int lengthA, int lengthB);
int multiply_large(int* s, int valx, int& length);
int Combo(int n, int m, int* val, int length);