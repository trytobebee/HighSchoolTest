#include<iostream> 
#include<cstdio>
#include "sorter.h"
using namespace std;

//针对任意一个n, 按规则计算max-min
int process(int n)
{
    int x[4];
    int index = 0;
    
    //获得n的各个数位的数字
    while(n)
    {
        x[index] = n % 10;
        n = n / 10;
        index++;
        if(index > 4)
        {
            printf("illegal input\n");
            return -1;
        }
    }
    
    while(index < 4) //不足4位的话补齐0；
    {
        x[index] = 0;
        index++;
    }

    sorters::bubble_sort(x, 4, false); //排好各个位子的数字的顺序
    int max = x[3] * 1000 + x[2] * 100 + x[1] * 10 + x[0]; //构造最大，最小数字，求差返回
    int min = x[0] * 1000 + x[1] * 100 + x[2] * 10 + x[3];
    return max - min;
}


int minmaxpuzzle()
{
    int n; 
    cin >> n;
    int numRound = 0;

    int ret = n;
    while( ret != 6174) //循环处理数字
    {
        ret = process(ret);
        numRound++;
    }
    
    cout << numRound << endl;
    return 0;
}