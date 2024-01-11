#pragma once
#include <iostream>
#include <cstdio>
#include <list>
#include "sortedlist_nd.h"
#include "ctimer.h"

using namespace std;

struct chessBoard
{
    int ** _pValues;
    int _n;
    int * _pLastQueenCol; //for each line mark the last queen position
    //CTimer _tm;

    chessBoard(int n)
    {
        _n = n;
        _pValues = new int* [n];
        _pLastQueenCol = new int[n];

        //intialized the board grid
        for(int i = 0; i < n; i++)
        {
            _pValues[i] = new int[n];
            ResetRow(i);
        }
        //_tm.start();
    }

    void ResetRow(int rowIndex)
    {
        for(int i = 0; i < _n; i++)
        {
            _pValues[rowIndex][i] = 0;
        }
        _pLastQueenCol[rowIndex] = -1;
    }

    //放置queen的操作
    bool PlaceQueen(int rowIndex, int colIndex)
    {
        //_tm.start();
        if(_pValues[rowIndex][colIndex] != 0)
            return false;

        //在rowIndex， colIndex处放置queen后，导致棋盘上很多地方变成不可摆放
        //都设置为-1；
        _pValues[rowIndex][colIndex] = 1;
        
        //修改这row之下的被当前queen影响的格子
        for(int i =  1; i < _n - rowIndex; i++)
        {
            _pValues[rowIndex + i][colIndex] --;
            
            if(colIndex + i < _n)
                _pValues[rowIndex + i][colIndex + i] --;
            
            if(colIndex - i >= 0)
                _pValues[rowIndex + i][colIndex - i] --;

        }

        _pLastQueenCol[rowIndex] = colIndex;

        //printf("place queen @ line %d, col %d\n", rowIndex, colIndex);
        //_tm.checkTimeSpan("PlaceQueen");
        return true;
    }

    //撤回queen的操作
    bool WithDrawQueen(int rowIndex, int colIndex)
    {
        //_tm.start();
        _pValues[rowIndex][colIndex] = 0;

        //撤回当前的queen造成的下方行的影响
        for(int i =  1; i < _n - rowIndex; i++)
        {
            _pValues[rowIndex + i][colIndex]++;
            
            if(colIndex + i < _n)
                _pValues[rowIndex + i][colIndex + i] ++;
            
            if(colIndex - i >= 0)
                _pValues[rowIndex + i][colIndex - i] ++;
        }

        //printf("withdraw queen @ line %d, col %d\n", rowIndex, colIndex);
        //_tm.checkTimeSpan("WithDrawQueen");
        return true;
    }

    //在当前行将Queen放置到下一个可行的位置，没有则返回失败
    bool placeQueenToNextPos(int rowIndex)
    {
        //如果当前行已经放了queen，把这个queen移除
        if(_pLastQueenCol[rowIndex] != -1)
        {
            WithDrawQueen(rowIndex, _pLastQueenCol[rowIndex]);
            
            //下层的每行的previous queen place record都重置, 去除所有之前曾经的记录
            for(int i = rowIndex + 1; i < _n; i++)
            {
                _pLastQueenCol[i] = -1;
            }
        }

        //搜寻下一个可以放置queen的点，这里用一个线性的搜索，速度比较慢
        //_tm.start();
        for(int colIndex = _pLastQueenCol[rowIndex]+1; colIndex < _n; colIndex++)
        {
            if(_pValues[rowIndex][colIndex] == 0)
            {
                //_tm.checkTimeSpan("placeQueenToNextPos");
                PlaceQueen(rowIndex, colIndex);
                return true;
            }
        }
        return false;//找不到合适的col
    }

    //从当前行开始寻找全局可以放的下一个状态，不一定在当前行，会修改 currentLine
    //不存在则返回false
    bool SearchToPlaceNext(int& currentLine)
    {
        //从当前行的前一行开始选择下一个合理的摆放点，如果当前行没有，则回退到上一行，如果还没有可行的，那就再次回退直到有可行解
        while(true)
        {
            if(!placeQueenToNextPos(currentLine))
            {
                currentLine --;
                if(currentLine < 0)
                {
                    //there is no proper position to place
                    //printf("no more proper option now!\n");
                    return false;
                }
            }
            else
            {
                //成功放到下一个位置
                break;
            }
        }
        return true;
    }

    //从当前状态下开始放完所有的queen，currentLine是当前的其实行
    bool FitQueensOnce(bool showResult = true, int currentRow = 0)
    {
        //int currentLine = 0;
        while(currentRow < _n)
        {
            if(placeQueenToNextPos(currentRow))
            {
                currentRow++; //goto next line
                continue;
            }
            else
            {
                currentRow--;
                if(!SearchToPlaceNext(currentRow))
                {
                    return false;
                }
                else
                {
                    currentRow++; //goto next line
                }  
            }
        }

        if(showResult)
        {
            //success
            //printf("find one solution for %d queen setting: ", _n);
            for(int i = 0; i < _n; i++)
            {
                printf("%d ", _pLastQueenCol[i]+1);
            }
            printf("\n");
        }
        return true;
    }

    //a^n
    int mypower(int a, int n)
    {
        int result = 1;
        for(int i = 0; i < n; i++)
        {
            result *= a;
        }
        return result;
    }

    void mapToN(int a, int* pos)
    {
        for(int i = 0; i < _n; i++)
        {
            pos[_n-1 - i] = a % _n;
            a = a / _n; 
        }
    }

    void FitQueensAllSimpleEum()
    {
        //convert the space to a particular setting
        //total space = n * n * n * n 
        int totalSpace = mypower(_n, _n);
        printf("total enumeration space %d\n", totalSpace);
        int *pos = new int[_n];
        int numSolution = 0;
        for(int i = 0; i < totalSpace; i++)
        {
            mapToN(i, pos);
            
            if(isValidResult(pos))
            {
                for(int j = 0; j < _n; j++)
                    printf("%d ", pos[j]);

                printf("\n");
                numSolution++;
            }

            for(int j = 0; j < _n; j++)
                ResetRow(j);       
        }

        if(!numSolution)
            printf("no solution found!\n");
    }

    bool isValidResult(int *pos)
    {
        for(int i = 0; i < _n; i++)
        {
            if(!PlaceQueen(i, pos[i]))
            {
                return false;
            }
        }
        return true;
    }

    //找到所有的解
    void FitQueensAll(bool showResult = true)
    {
        int solutionNum = 0;
        int currentRow = 0;
        while(true)
        {
            if(!FitQueensOnce(showResult, currentRow))
            {
                //no more solution options
                break;
            }
            else
            {
                solutionNum++;

                //重放后一行然后重新从当前行开始place
                currentRow = _n-1;
                if(SearchToPlaceNext(currentRow)) //这里currentLine会被修改成真正成功摆放新queen的那一行
                {
                    //goto next line and continue;
                    currentRow++;
                }
                else
                {
                    //no more options
                    break;
                }
            }
        }

        printf("total solution number: %d\n", solutionNum);
        //_tm.OutputStat();
        return;
    }
};

// struct chessBoardRow
// {
//     int * _pValues;
//     int _n;
//     SortedList_ND _lstZeros;
// };

struct chessBoard2
{
    int ** _pValues;
    int _n;
    int * _pLastQueenCol; //for each line mark the last queen position
    int * _pWithdrawCnt; //record the withdraw times of each row
    SortedList_ND * _pRowZeros;
    //CTimer _tm;

    chessBoard2(int n)
    {
        _n = n;
        _pValues = new int* [n];
        _pLastQueenCol = new int[n];
        _pRowZeros = new SortedList_ND[n];
        _pWithdrawCnt = new int[n];
        //intialized the board grid
        for(int i = 0; i < n; i++)
        {
            _pValues[i] = new int[n];
            _pRowZeros[i].Initialize(10000);
            ResetRow(i);
        }

        //_tm.start();
    }

    void ResetRow(int rowIndex)
    {
        for(int i = 0; i < _n; i++)
        {
            _pValues[rowIndex][i] = 0;
        }
        _pLastQueenCol[rowIndex] = -1;
        _pWithdrawCnt[rowIndex] = 0;
        _pRowZeros[rowIndex].Prefill(_n);
    }

    //放置queen的操作
    bool PlaceQueen(int rowIndex, int colIndex)
    {
        //_tm.start();

        //在rowIndex， colIndex处放置queen后，导致棋盘上很多地方变成不可摆放
        //都设置为-1；
        _pValues[rowIndex][colIndex] = 1;
        _pRowZeros[rowIndex].remove(colIndex);

        //修改这row之下的被当前queen影响的格子
        for(int i =  1; i < _n - rowIndex; i++)
        {
            _pValues[rowIndex + i][colIndex] --;
            _pRowZeros[rowIndex + i].remove(colIndex);
            
            if(colIndex + i < _n)
            {
                _pValues[rowIndex + i][colIndex + i] --;
                _pRowZeros[rowIndex + i].remove(colIndex + i);
            }    

            
            if(colIndex - i >= 0)
            {
                _pValues[rowIndex + i][colIndex - i] --;
                _pRowZeros[rowIndex + i].remove(colIndex - i);
            }
        }

        _pLastQueenCol[rowIndex] = colIndex;
        //_tm.checkTimeSpan("PlaceQueen");
        //printf("place queen @ line %d, col %d\n", rowIndex, colIndex);
        return true;
    }

    //撤回queen的操作
    bool WithDrawQueen(int rowIndex, int colIndex)
    {
        //_tm.start();
        _pValues[rowIndex][colIndex] = 0;
        _pWithdrawCnt[rowIndex]++;
        _pRowZeros[rowIndex].insert(colIndex);
        
        //撤回当前的queen造成的下方行的影响
        for(int i =  1; i < _n - rowIndex; i++)
        {
            _pValues[rowIndex + i][colIndex]++;
            if(_pValues[rowIndex + i][colIndex] == 0)
                _pRowZeros[rowIndex + i].insert(colIndex);

            if(colIndex + i < _n)
            {
                _pValues[rowIndex + i][colIndex + i] ++;
                if(_pValues[rowIndex + i][colIndex + i] == 0)
                    _pRowZeros[rowIndex + i].insert(colIndex + i);
            }    
            
            if(colIndex - i >= 0)
            {
                _pValues[rowIndex + i][colIndex - i] ++;
                if(_pValues[rowIndex + i][colIndex - i] == 0)
                    _pRowZeros[rowIndex + i].insert(colIndex - i);
            }
        }

        //printf("withdraw queen @ line %d, col %d\n", rowIndex, colIndex);
        //_tm.checkTimeSpan("WithDrawQueen");
        return true;
    }

    //在当前行将Queen放置到下一个可行的位置，没有则返回失败
    bool placeQueenToNextPos(int rowIndex)
    {
        //如果当前行已经放了queen，把这个queen移除
        if(_pLastQueenCol[rowIndex] != -1)
        {
            WithDrawQueen(rowIndex, _pLastQueenCol[rowIndex]);
            
            //下层的每行的previous queen place record都重置, 去除所有之前曾经的记录
            for(int i = rowIndex + 1; i < _n; i++)
            {
                _pLastQueenCol[i] = -1;
                _pWithdrawCnt[i] = 0;
            }
        }

        int colIndex;

        //_tm.start();
        int* newItem = _pRowZeros[rowIndex].GetItem(_pWithdrawCnt[rowIndex]);
        if(newItem)
            colIndex = *newItem;    
        else
            return false; //没有合适的
        //_tm.checkTimeSpan("placeQueenToNextPos");

        // if(_pLastQueenCol[rowIndex] == -1)
        // {
        //     int* firstItem = _pRowZeros[rowIndex].GetItem(0);
        //     if(firstItem)
        //     {
        //         colIndex = *firstItem;
        //     }    
        //     else
        //         return false; //没有合适的
        // }
        // else
        // {
        //     //option1, binary search to find the next zero position
        //     int* lastQueen = _pRowZeros[rowIndex].BinarySearch(_pLastQueenCol[rowIndex]);
        //     if(lastQueen == _pRowZeros[rowIndex].LastItem())
        //         return false; //后面没有0的位置了
        //     else
        //         colIndex = *(lastQueen+1);
        // }
        PlaceQueen(rowIndex, colIndex);
        
        return true;
    }

    //从当前行开始寻找全局可以放的下一个状态，不一定在当前行，会修改 currentLine
    //不存在则返回false
    bool SearchToPlaceNext(int& currentLine)
    {
        //从当前行的前一行开始选择下一个合理的摆放点，如果当前行没有，则回退到上一行，如果还没有可行的，那就再次回退直到有可行解
        while(true)
        {
            if(!placeQueenToNextPos(currentLine))
            {
                currentLine --;
                if(currentLine < 0)
                {
                    //there is no proper position to place
                    //printf("no more proper option now!\n");
                    return false;
                }
            }
            else
            {
                //成功放到下一个位置
                break;
            }
        }
        return true;
    }

    //从当前状态下开始放完所有的queen，currentLine是当前的其实行
    bool FitQueensOnce(bool showResult = true, int currentRow = 0)
    {
        //int currentLine = 0;
        while(currentRow < _n)
        {
            if(placeQueenToNextPos(currentRow))
            {
                currentRow++; //goto next line
                continue;
            }
            else
            {
                currentRow--;
                if(!SearchToPlaceNext(currentRow))
                {
                    return false;
                }
                else
                {
                    currentRow++; //goto next line
                }  
            }
        }

        if(showResult)
        {
            //success
            //printf("find one solution for %d queen setting: ", _n);
            for(int i = 0; i < _n; i++)
            {
                printf("%d ", _pLastQueenCol[i]+1);
            }
            printf("\n");
        }
        return true;
    }

    //找到所有的解
    void FitQueensAll(bool showResult = true)
    {
        int solutionNum = 0;
        int currentRow = 0;
        while(true)
        {
            if(!FitQueensOnce(showResult, currentRow))
            {
                //no more solution options
                break;
            }
            else
            {
                solutionNum++;

                //重放后一行然后重新从当前行开始place
                currentRow = _n-1;
                if(SearchToPlaceNext(currentRow)) //这里currentLine会被修改成真正成功摆放新queen的那一行
                {
                    //goto next line and continue;
                    currentRow++;
                }
                else
                {
                    //no more options
                    break;
                }
            }
        }

        printf("total solution number: %d\n", solutionNum);
        //_tm.OutputStat();
        return;
    }
};