#include<iostream>
#include <cstdio>
#include <vector>
using namespace std;


int splitK(int K, int* result)
{
    //e.g. result refer to the number of these three parties. 
    //4 can be split into 2, 2
    //5 can be split into 2, [3] or [3], 2
    //10 can be split into 2, [3, 3], 2
    int subUnits = K / 3; 
    int remain = K % 3;

    result[0] = 0;
    result[2] = 0;
            
    if(remain == 0)
    {
        result[1] = subUnits;
    }
    else if(remain == 1)
    {
        //split schema could be [3.....3], 2 or  2, [3,....,3]
        //output solution
        result[0] = 1;
        result[1] = subUnits-1;
        result[2] = 1;
    }
    else if(remain == 2)
    {
        result[0] = 1;
        result[1] = subUnits;
    }

    return result[0]+result[1]+result[2];
}

int* GetPosition(int* a)
{
    //vector<int> aVec;
    int *aArray = new int[a[0]+a[1]+a[2]];
    if(a[0]) //第一个2存在
    {
        aArray[0] = 1;
        for(int i = 0; i < a[1]; i++)
            aArray[i+a[0]] = a[0] + (i+1) * 3;
    }
    else
    {
        for(int i = 0; i < a[1]; i++)
            aArray[i] = 2 + i * 3;
    }   

    if(a[2]) //最后还有一个2存在
        aArray[a[0]+a[1]] = aArray[a[0]+a[1]-1] + 3; 
    
    return aArray;
}


int TestFlipSolver()
{
    int a, b;
    cin >> a >> b;

    //cout << a << " " << b;   
    
    //separate a into the format like  2* 3* 2*
    //which means the frist and the last block can be 2 or 3, the internal should be 3
    int result_a[3];
    int result_b[3]; 
    //result_a[0] refer to the frist 2
    //result_a[1] refer to the second part 3....3
    //result_a[2] refere to the third part 2;
    
    int numAPoints = splitK(a, result_a);
    int numBPoints = splitK(b, result_b);

    int *aPositions = GetPosition(result_a);
    int *bPositions = GetPosition(result_b);

    for(int i = 0; i < numAPoints; i++)
    {
        for(int j = 0; j < numBPoints; j++)
        {
            cout << aPositions[i] << " " << bPositions[j] << endl;
        }
    }

    cout << "0 0" << endl;
    return 0;
}