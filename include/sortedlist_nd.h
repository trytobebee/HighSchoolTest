#pragma once
#include <cstdio>
#include <string>
#include "sorter.h"
using namespace std;
//construct list which works for sorted items(no duplications in data)
//insert a item(with the particular value) to a particular position fits the sorted status O(logN)
//remove a item(with the particular value) O(logN)
class SortedList_ND
{
public: 
    SortedList_ND()
    {
        m_pMemory = NULL;
        m_capacity = 0;
        m_pCurrentMemoryPos = NULL;
        m_size = 0;
    }

    SortedList_ND(int capacity)
    {
        m_pMemory = new int[capacity];
        //memset(m_pMemory, 0, capacity * sizeof(int));
        
        m_capacity = capacity;
        m_pCurrentMemoryPos = m_pMemory;
        m_size = 0;
    }

    bool Initialize(int capacity)
    {
        m_pMemory = new int[capacity];
        if(m_pMemory == NULL)
        {
            printf("memory allocation failed\n");
            return false;
        }
            
        m_capacity = capacity;
        m_pCurrentMemoryPos = m_pMemory;
        m_size = 0;

        return true;
    }

    // void Reset()
    // {
    //     m_size = 0;
    //     m_pCurrentMemoryPos = 0;
    // }

    bool Prefill(int numElem)
    {
        if(numElem >= m_capacity)
            return false;

        for(int i = 0; i < numElem; i++)
            push_back(i);
        
        return true;
    }

    bool push_back(int value)
    {
        //这个值加到最后
        int *pNode = m_pCurrentMemoryPos;
        *pNode = value;
        m_size++;
        m_pCurrentMemoryPos++; //point to the next int memory block
        return true;
    }

    

    
    int * BinarySearch(int value)
    {
        int* start = m_pMemory;
        int* end = m_pCurrentMemoryPos - 1;

        return sorters::BinarySearch(start, end, value);
    }

    //序列中一定没有value
    int* BinarySearchLastLess(int* start, int* end, int value)
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
            else
            {
                pLeft = pMid;
            }   
        }

        if(*pLeft < value && *pRight > value)
        {
            //found between left and right
            return pLeft;
        }
        else if(*pRight < value)
        {
            //value is bigger than right
            return pRight;
        }
        else
        {
            //value is samller than left
            return NULL;
        }
    }

    int* BinarySearchLastLess(int value)
    {
        int* start = m_pMemory;
        int* end = m_pCurrentMemoryPos - 1;
        return BinarySearchLastLess(start, end, value);
    }


    bool insert(int value)
    {
        if(m_capacity == m_size) //超容量，失败
        {
            printf("out of capacity, insertion failed\n");
            return false;
        }
            

        int* pLastInt = m_pCurrentMemoryPos - 1;
        int *pFindValue = BinarySearchLastLess(m_pMemory, pLastInt, value);
        int index = (pFindValue - m_pMemory)/sizeof(int);
        
        if(pFindValue)
        {
            //找到这个位置了，可能包含全序列都比value小的case
            //将值赋予这个位置后一个位置，然后挪动剩下的memory
            if(m_size > index + 1)
            {
                memcpy(pFindValue + 2, pFindValue + 1, (m_size-index-1)*sizeof(int));
            }
            
            pFindValue++;
            *pFindValue = value; //插入新值
        }
        else
        {
            //没有找到，全序列都比value大
            memcpy(m_pMemory + 1, m_pMemory, m_size*sizeof(int));
            *m_pMemory = value;
        }

        m_pCurrentMemoryPos++;
        m_size++;
        return true;
    }

    bool remove(int value)
    {
        if(m_size == 0) //empty, no item to delete
            return false;

        int* pLastInt = m_pCurrentMemoryPos - 1;
        int *pFindValue = sorters::BinarySearch(m_pMemory, pLastInt, value);
        if(!pFindValue)
        {
            //didn't find the value
            //printf("no such value %d in the list\n", value);
            return false;
        }

        int index = (pFindValue - m_pMemory)/sizeof(int);
        memcpy(pFindValue, pFindValue+1, (m_size-index-1)*sizeof(int));
        m_size--;
        m_pCurrentMemoryPos--;
        return true;
    }

    int* GetItem(int index)
    {
        if(index >= m_size)
        {
            return NULL;
        }
        else
        {
            return m_pMemory+index;
        }   
    }

    const int* LastItem()
    {
        return m_pCurrentMemoryPos - 1;
    }

    const int* FirstItem()
    {
        return m_pMemory;
    }

    ~SortedList_ND()
    {
        delete[] m_pMemory;
        m_pMemory = NULL;
    }

public:
    int m_size;
private:
    int * m_pMemory;
    int * m_pCurrentMemoryPos;
    
    int m_capacity;
};

//降序的一个sorted_list
class SortedList_Dsc
{
public: 
    SortedList_Dsc()
    {
        m_pMemory = NULL;
        m_capacity = 0;
        m_pCurrentMemoryPos = NULL;
        m_size = 0;
    }

    SortedList_Dsc(int capacity)
    {
        m_pMemory = new int[capacity];
        //memset(m_pMemory, 0, capacity * sizeof(int));
        
        m_capacity = capacity;
        m_pCurrentMemoryPos = m_pMemory;
        m_size = 0;
    }

    bool Initialize(int capacity)
    {
        m_pMemory = new int[capacity];
        if(m_pMemory == NULL)
        {
            printf("memory allocation failed\n");
            return false;
        }
            
        m_capacity = capacity;
        m_pCurrentMemoryPos = m_pMemory;
        m_size = 0;

        return true;
    }

    // void Reset()
    // {
    //     m_size = 0;
    //     m_pCurrentMemoryPos = 0;
    // }

    // bool Prefill(int numElem)
    // {
    //     if(numElem >= m_capacity)
    //         return false;

    //     for(int i = 0; i < numElem; i++)
    //         push_back(i);
        
    //     return true;
    // }

    // bool push_back(int value)
    // {
    //     //这个值加到最后
    //     int *pNode = m_pCurrentMemoryPos;
    //     *pNode = value;
    //     m_size++;
    //     m_pCurrentMemoryPos++; //point to the next int memory block
    //     return true;
    // }

    int * BinarySearch(int* start, int* end, int value)
    {
        int* pLeft = start;
        int* pRight = end;

        int* pMid;

        while(pLeft < pRight - 1)
        {
            pMid = pLeft + (pRight-pLeft)/2;

            if(*pMid > value)
            {
                pLeft = pMid;
            }
            else if(*pMid == value)
            {
                //found
                return pMid;
                break;
            }
            else
            {
                pRight = pMid;
            }
        }
        
        if(*pLeft == value)
            return pLeft;
        else if(*pRight == value)
            return pRight;
        else
            return NULL;
    }

    int * BinarySearch(int value)
    {
        int* start = m_pMemory;
        int* end = m_pCurrentMemoryPos - 1;

        return BinarySearch(start, end, value);
    }

    //寻找序列中第一个比value小的位置
    int* BinarySearchFirstLess(int* start, int* end, int value)
    {
        int* pLeft = start;
        int* pRight = end;
        if(*pLeft < value)
            return pLeft; 

        int* pMid;
        while(pLeft < pRight - 1)
        {
            pMid = pLeft + (pRight-pLeft)/2;
        
            if(*pMid >= value)
            {
                pLeft = pMid;
            }
            else
            {
                pRight = pMid;
            }
        }

        if(*pLeft >= value && *pRight < value)
        {
            //found between left and right
            return pRight;
        }
        else if(*pLeft < value)
        {
            //value is bigger than left
            return pLeft;
        }
        else
        {
            //value is samller than left
            return NULL;
        }
    }

    // int* BinarySearchLastLess(int value)
    // {
    //     int* start = m_pMemory;
    //     int* end = m_pCurrentMemoryPos - 1;
    //     return BinarySearchLastLess(start, end, value);
    // }

    bool insert(int value)
    {
        if(m_capacity == m_size) //超容量，失败
        {
            printf("out of capacity, insertion failed\n");
            return false;
        }

        int* pLastInt = m_pCurrentMemoryPos - 1;
        int *pFindValue = BinarySearchFirstLess(m_pMemory, pLastInt, value);
        int index = (pFindValue - m_pMemory)/sizeof(int);
        
        if(pFindValue)
        {
            //找到这个位置了，可能包含全序列都比value小的case
            //将值赋予这个位置后一个位置，然后挪动剩下的memory
            if(m_size > index + 1)
            {
                memcpy(pFindValue + 2, pFindValue + 1, (m_size-index-1)*sizeof(int));
            }
            
            pFindValue++;
            *pFindValue = value; //插入新值
        }
        else
        {
            //没有找到，全序列都比value大
            memcpy(m_pMemory + 1, m_pMemory, m_size*sizeof(int));
            *m_pMemory = value;
        }

        m_pCurrentMemoryPos++;
        m_size++;
        return true;
    }

    int* GetItem(int index)
    {
        if(index >= m_size)
        {
            return NULL;
        }
        else
        {
            return m_pMemory+index;
        }   
    }

    const int* LastItem()
    {
        return m_pCurrentMemoryPos - 1;
    }

    const int* FirstItem()
    {
        return m_pMemory;
    }

    ~SortedList_Dsc()
    {
        delete[] m_pMemory;
        m_pMemory = NULL;
    }

public:
    int m_size;

private:
    int * m_pMemory;
    int * m_pCurrentMemoryPos;
    
    int m_capacity;
};