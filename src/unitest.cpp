//#include "sortedlist_nd.h"
#include "ctimer.h"
#include <iostream>
#include "chessBoard.h"
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