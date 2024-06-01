#include<iostream>
#include<string.h>
#include "largeNum.h"
#include "inputProc.h"
using namespace std;


//将a反转存入b中
void CopyInverse(int* a, int* b, int length)
{
    for(int i = 0; i < length; i++)
    {
        b[i] = a[length-1 - i];
    }
    b[length] = '\0';
}

//int数组回文判断
bool isPalindrome(int* a, int length)
{
    for(int i = 0; i < length/2; i++)
    {
        if(a[i] != a[length-1-i])
            return false;
    }

    return true;
}

int checkPalindrome()
{
    int scale;
    char m[100];
    cin >> scale >> m;

    int Capcity = 1024;
    int* val = new int[Capcity];
    int* valRev = new int[Capcity];

    memset(val, 0, sizeof(int) * Capcity);
    memset(valRev, 0, sizeof(int) * Capcity);

    int length;
    Map2IntArray(m, val, length);
    Map2IntArray(m, valRev, length, true);
    int step = 0;

    while(step < 30)
    {
        Addition(val, valRev, length, scale);
        step++;
        if(isPalindrome(val, length))
        {
            cout << "STEP=" << step << endl;
            //IntArray2Str(val, m, length);
            //cout << m << endl;
            break;
        }
        memset(valRev, 0, sizeof(int) * Capcity);
        CopyInverse(val, valRev, length);
    }
    
    if(step == 30)
        cout << "Impossible!" << endl;
    
    delete[] val;
    delete[] valRev;
    return 0;
}