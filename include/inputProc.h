#pragma once
#include <iostream>
using namespace std;

const char c_CharNum[17]="0123456789ABCDEF";
//字符化成整数
inline int char2Int(char c)
{
    if(c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else if(c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else
    {
        printf("invalid input for char2Val %c", c);
        return -1;
    }
}

//save int array into a string(scale under 16)
//{10, 11, 9, 0, 1, 2} ==> 2109BA, up to 16进制
inline void IntArray2Str(int* a, char* strval, int length)
{
    //输入低位在前，高位在后， 故需要反转
    for(int i = 0; i < length; i++)
    {
        if(a[length - 1 - i ] >= 0 && a[length - 1 - i ] <= 15)
            strval[i] = c_CharNum[a[length - 1 - i ]];
        else
            cout << "invalid number: " << a[length - 1 - i ] << endl;
    }
    strval[length] = '\0';
}

//将字符创输入存成int数组，支持16进制下，同时可以反转存储
inline void Map2IntArray(char *str, int* a, int& length, bool reverse = false)
{
    length = strlen(str);
    
    for(int i = 0; i < length; i++)
    {
        if(reverse)
            a[i] = char2Int(str[i]);
        else
            a[length - 1 - i] = char2Int(str[i]);
    }
}
