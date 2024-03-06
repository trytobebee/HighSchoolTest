#pragma once

namespace sorters
{
    inline int * BinarySearch(int* start, int* end, int value)
    {
        int* pLeft = start;
        int* pRight = end;

        int* pMid;

        while(pLeft < pRight - 1)
        {
            pMid = pLeft + (pRight-pLeft)/2;

            if(*pMid > value)
            {
                pRight = pMid;
            }
            else if(*pMid == value)
            {
                //found
                return pMid;
                break;
            }
            else
            {
                pLeft = pMid;
            }
        }
        
        if(*pLeft == value)
            return pLeft;
        else if(*pRight == value)
            return pRight;
        else
            return NULL;
    }


    //选择排序，每次挑选一轮中最大的填到x[i]中， 剩下的元素进入下一轮
    inline int select_sort(int* x, int length, bool isDesc = true)
    {
        int indicator = 1;
        if(!isDesc)
        {
            indicator = -1;
        }

        for(int i = 0; i < length; i++)
        {
            int maxIndex = i;
            int max = x[i];
            for(int j = i + 1; j < length; j++)
            {
                if(x[maxIndex] * indicator < x[j] * indicator) //把大的换上来
                {
                    maxIndex = j;
                }
            }
            
            if(maxIndex != i)
            {
                int tmp = x[i];
                x[i] = x[maxIndex];
                x[maxIndex] = tmp;
            }
        }    
        return 0;
    }

    //bubble sort在sort的过程中比较相邻，比较小的会被从i->i+1，经过一轮会将最小的送到当前轮的最后一个位置去（length - i）
    inline int bubble_sort(int *x, int length, bool isDesc = true)
    {
        int numExchg = -1;
        int indicator = 1;
        if(!isDesc)
        {
            indicator = -1;
        }

        for(int i = 0; i < length; i++)
        {
            if(numExchg == 0)
            {
                //printf("no exchange happend in the %d-th round, break\n", i);
                break; //剩余都是好的顺序，不用再替换了
            }

            for(int j = 0; j < length - i - 1; j++)
            {
                numExchg = 0;
                if(x[j] * indicator >= x[j+1] * indicator)
                {
                    //不小的就不动
                }
                else
                {
                    int tmp;
                    tmp = x[j];
                    x[j] = x[j+1];
                    x[j+1] = tmp;

                    numExchg++;
                }
            }    
        }
        return 0;
    }

    //变形版冒泡排序，不是相邻的进行对比交换，而是锚定x[i]作为操作对象
    //best case会不如相邻比较冒泡排序加上tag
    inline int bubble_sort_II(int* x, int length, bool isDesc = true)
    {
        int indicator = 1;
        if(!isDesc)
        {
            indicator = -1;
        }

        for(int i = 0; i < length; i++)
        {
            for(int j = i + 1; j < length; j++)
            {
                if(x[i] * indicator < x[j] * indicator) //把大的换上来
                {
                    int tmp = x[i];
                    x[i] = x[j];
                    x[j] = tmp;
                }
            }
        }    
        return 0;
    }

    //a bubble sort version for any type sorting, _T should have the < & > operator
    template<typename _T>
    bool Sort_TypedArray(_T* pItems, int length, bool isDesc = true)
    {
        for(int i = 0; i < length; i++)
        {
            int maxIndex = i;
            for(int j = i + 1; j < length; j++)
            {
                if(pItems[maxIndex] < pItems[j] && isDesc || pItems[maxIndex] > pItems[j] && !isDesc) //把大的换上来
                {
                    maxIndex = j;
                }
            }
            
            if(maxIndex != i)
            {
                _T tmp = pItems[i];
                pItems[i] = pItems[maxIndex];
                pItems[maxIndex] = tmp;
            }
        }    
        return 0;
    } 
}
