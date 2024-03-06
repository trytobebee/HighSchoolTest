//#include "sortedlist_nd.h"
#include "ctimer.h"
#include <iostream>
#include "chessBoard.h"
#include "mathfunc.h"
#include "simpleencode.h"
#include "unitest.h"
using namespace std;

void testcase_sortedlist_nd()
{
    CTimer tm;
    cout << "current version 1.0" << endl;

    while(true)
    {
        int n; //n queens
        cin >> n;
        list<int> lstX;
        
        tm.start();
        for(int i = 0; i < n; i ++)
        {
            lstX.push_back(i * 2 + 1);
        }
        tm.getTimeSpan("push items to lstX");
        for(int i = 0; i < n; i += 10)
        {
            //insert i * 2
            list<int>::iterator pos = find(lstX.begin(), lstX.end(), i*2 + 1);
            lstX.insert(pos, i*2);
        }

        for(int i = 0; i < n; i += 10)
        {
            lstX.remove(i*2);
        }
        // list<int>::iterator pos = lstX.end();
        // pos--;
        // for(int i = 0; i < 100; i++)
        // {
        //     printf("%d ", *pos);
        //     pos--;
        // }

        tm.getTimeSpan("insert & remove items to lstX");

        SortedList_ND lstY(100000);
        for(int i = 0; i < n; i ++)
        {
            lstY.push_back(i * 2 + 1);
        }
        tm.getTimeSpan("push items to lstY");

        for(int i = 0; i < n; i += 10)
        {
            lstY.insert(i*2);
        }

        for(int i = 0; i < n; i += 10)
        {
            lstY.remove(i*2);
        }

        // for(int i = 0; i < 100; i++)
        // {
        //     printf("%d ", lstY.GetItem(lstY.m_size - 1 - i));
        // }
        tm.getTimeSpan("insert and remove items to lstY");
    }
}

int testNQueen()
{
    while(true)
    {
        int n;
        cin >> n;

        if(n <= 0)
            break;

        CTimer tm;
        tm.start();

        chessBoard myChess(n);
        //myChess.FitQueensAllSimpleEum();

        myChess.FitQueensAll(true);
        tm.getTimeSpan("chessBoard class run");

        chessBoard2 myChess2(n);
        myChess2.FitQueensAll(true);
        tm.getTimeSpan("chessBoard2 class run");
    }
    
    return 0;
}

bool testEnlistPrimes()
{
    CTimer tmDebug;
    tmDebug.start();

    int* primes;
    int count;
    
    mathfunc::EnlistAllPrime(false, primes, count);
    tmDebug.getTimeSpan("without speed up");

    int* primes2;
    int count2;
    mathfunc::EnlistAllPrime(true, primes2, count2);
    tmDebug.getTimeSpan("with speed up");

    if(count != count2)
    {
        printf("inconsistent count of prime\n");
        return false;
    }    

    int i;
    for(i = 0; i < count; i++)
    {
        if(primes[i] != primes2[i])
        {
            printf("inconsistent prime value @position %d, %d vs %d\n", i, primes[i], primes2[i]);
            return false;
        }   
    }
    if(i == count)
    {
        printf("confirmed, identical prime array\n");
    }
    
    return true;
}

int testMath()
{
    while(true)
    {
        int a, b;
        cin >> a >> b;
        if(a <= 0)
            break;

        cout << "最大公约数" << mathfunc::GetMaxCofactor(a, b) << endl;
        cout << "最小公倍数" << mathfunc::GetLeastCoMultiple(a, b) << endl;
    }
    
    return 0;
}

int testEncodeDecode()
{
    //inverse encoding
    int n; 
    cin >> n;

    int *pInputs = new int[n];
    for(int i = 0; i < n; i++)
    {
        cin >> pInputs[i];
    }
    
    int functionid;
    cin >> functionid;
    
    int *pResult;
    if(functionid == 0)
    {
        pResult = encode(n, pInputs);
    }
    else if(functionid == 1)
    {
        pResult = decode(n, pInputs);
    }

    for(int i = 0; i < n; i++)
    {
        cout << pResult[i] << " ";
    }
    cout << endl;
    
    delete[] pResult;
    pResult = NULL;
    return 0;
}

int testRabbit()
{
    int iterNum = 10000; //找了多少次
    int n;
    cin >> n; //洞

    if(n <= 0)
    {
        cout << "illegal input" << endl;
    }
    
    bool * pMarked = new bool[n]; //每个洞一个标志boolean， false表示没有被狐狸到过
    for(int i = 0; i < n; i++)
        pMarked[i] = false;
    

    int curIndex = 0; 
    int curGap = 0;
    
    //跑坑找兔子的流程，每跑到一个坑，mark为true
    for(int i = 0; i < iterNum; i++)
    {
        pMarked[curIndex] = true;    
        curGap ++;
        
        curIndex += curGap + 1;
        
        //需处理Index循环的问题，当前的index + gap应该还要落回到n的范围内
        curIndex = curIndex % n;
    }

    bool find = true;
    for(int i = 0; i < n; i++)
    {
        if(pMarked[i] == false)
        {
            cout << i+1 << " ";
            find = false;
        }
    }

    if(find)
        cout << "It is nice!" << endl;

    return 0;
}