
#include<iostream> 
// #include <cstdio>
// #include <algorithm>
#include "ctimer.h"

using namespace std;
const int MAXN = 1e5+10;
int roof[MAXN];

// //冒泡排序
// int sort_in_pos(int* x, int length)
// {
//     for(int i = 0; i < length; i++)
//     {
//         for(int j = i + 1; j < length; j++)
//         {
//             if(x[i] > x[j])
//             {
//                 int tmp = x[i];
//                 x[i] = x[j];
//                 x[j] = tmp;
//             }
//         }
//     }    
//     return 0;
// }

// //获取数组中最小数字的index
// int getMinId(int* v, int n, bool* bValid)
// {
//     int minId = 0;
//     for(int i = 0; i < n; i++)
//     {
//         if(bValid[i])
//         {
//             minId = i;
//             break;
//         }    

//     }

//     for(int i = minId + 1; i < n; i++)
//     {
//         if(v[minId] > v[i] && bValid[i])
//             minId = i;
//     }

//     return minId;
// }

// void showInALine(int* v, int n, bool* bValid)
// {
//     for(int i = 0; i < n; i++)
//     {
//         if(bValid[i])
//             printf("%d ", v[i]);
//     }
//     printf("\n");
// }

// //将n个格子合并掉c个最小的格子
// int merge(int*& v, int n, int c)
// {
//     //用来交换的vtmp
//     //int *tmpV = new int[n]; //剩下的都放在newV中保留，循环结束时候给到v变量
//     bool *bValid = new bool[n];
//     for(int i = 0; i < n; i++)
//         bValid[i] = true;

//     for(int i = 0; i < c; i++)
//     {
//         //showInALine(v, n, bValid);
//         //p中是每个间隔的大小，现在需要知道p中各自的大小顺序，以便从最小间隔开始合并
//         int minPos = getMinId(v, n, bValid); 
//         //int deletedSpanId = -1;

//         //每次merge一个最小的和他旁边的比较小的一个
//         // if(minPos == 0)
//         // {
//         //     v[minPos] += v[minPos+1];
//         //     bValid[minPos+1] = false; 
//         // }
//         // else if(minPos == n-1 )
//         // {
//         //     v[minPos] += v[minPos-1];
//         //     bValid[minPos-1] = false;
//         // }
//         // else
//         // {
//         //     if(v[minPos+1] > v[minPos-1])
//         //     {
//         //         v[minPos] += v[minPos-1];
//         //         bValid[minPos-1] = false;
//         //     }
//         //     else
//         //     {
//         //         v[minPos] += v[minPos+1];
//         //         bValid[minPos+1] = false; 
//         //     }
//         // }

        
//         int leftIndex = minPos - 1;
//         int rightIndex = minPos + 1;
//         while(true)
//         {
//             if(leftIndex < 0)
//                 break;
//             else if(bValid[leftIndex])
//                 break;
            
//             leftIndex--;
//         }

//         while(true)
//         {
//             if(rightIndex >= n)
//                 break;
//             else if(bValid[rightIndex])
//                 break;
            
//             rightIndex++;
//         }

//         //int
//         int mergeTarget;
//         if(leftIndex >=0 && rightIndex < n)
//             mergeTarget = v[leftIndex] <= v[rightIndex] ? leftIndex : rightIndex;
//         else if(leftIndex < 0 && rightIndex < n)
//             mergeTarget = rightIndex;
//         else if(leftIndex > 0 && rightIndex >= n)
//             mergeTarget = leftIndex;
        
//         v[minPos] += v[mergeTarget];
//         bValid[mergeTarget] = false;
        
//         //将剩下valid的部分copy到tmpV中
//         // int validId = 0;
//         // for(int j = 0; j < n; j++)
//         // {
//         //     if(j != deletedSpanId)
//         //     {
//         //         tmpV[validId] = v[j];
//         //         validId++;
//         //     }
//         // }
        
//         //n--;
//     }

//     //showInALine(v, n, bValid);
//     return getMinId(v, n, bValid);
// }

// int main()
// {
//     int n,m; //n个间隔，m头牛 
//     cin >> n >> m;
    
//     if(n < 2 || m > n)
//     {
//         cout << "illegal input n < 2 or m > n" << endl;
//         return -1;    
//     }

//     int *p = new int[n]; //间隔的position
//     for(int i = 0; i < n; i++)
//     {
//         cin >> p[i];
//     }

//     sort_in_pos(p, n);
//     //showInALine(p, n);

//     int *span = new int[n-1];
//     for(int i = 0; i < n - 1; i++)
//     {
//         span[i] = p[i+1]-p[i];
//     }

//     int minId;
//     minId = merge(span, n - 1, n - m);
//     std::cout << span[minId] << endl;
//     return 0;
// }


bool Judge(int n, int m, int scale)
{
    //判断n个item序列放在m个包里面，是否能够满足最少的包里面有distance
    int location = roof[0];
    int number = 1;

    if((m-1)*scale > roof[n-1]-roof[0])
        return false;

    for(int i =1; i < n; i++)
    {
        if(roof[i]-location >= scale)
        {
            location = roof[i];
            number++;
            if(number == m)
                return true;
        }
    }
    
    return false;
}

int GetBaseline(int n, int m)
{
    //获取理论的max（min gap），就是间隔均值
    int optimGap = (roof[n-1] - roof[0]) / (m-1);
    int minGap = optimGap;
    int *keyPosition = new int[m];
    int thisGap;
    int start = 0;
    
    keyPosition[0] = roof[0];
    keyPosition[m-1] = roof[n-1];

    //扫描整个序列
    for(int i = 1; i < m - 1; i++)
    {
        int target = roof[0] + i * optimGap;
        for(int j = start+1; j < n; j++)
        {
            if(roof[j] > target)
            {
                if(j == start +1)
                {
                    keyPosition[i] = roof[j];
                    start = j;
                }
                else
                {
                    keyPosition[i] = roof[j-1];
                    start = j-1;
                }
                break;
            }
        }
    }
    
    for(int i = 0; i < m-1; i++)
    {
        int gap = keyPosition[i+1] - keyPosition[i];
        //printf("%d(%d) ", keyPosition[i], gap);
        if(minGap > gap)
            minGap = gap;
    }
    //printf("\n");

    return minGap;
}

int bullmain()
{
    int n, m;
    cin >> n >> m;
    for(int i =0 ; i < n; i++)
    {
        cin >> roof[i];
    }

    CTimer tm;
    tm.start();

    sort(roof, roof+n);
    tm.getTimeSpan("sort function");

    //对distance进行二分
    int left = 1;
    int right = roof[n-1]-roof[0];

    //left = GetBaseline(n,m);
    tm.getTimeSpan("get baseline result");
    
    //right = (roof[n-1]-roof[0])/(m-1); 
    printf("stall number %d(position %d - %d), bull number %d\n", n, roof[0], roof[n-1], m);
    printf("minimum gap search range %d - %d\n", left, right);

    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(Judge(n,m, mid))
        {
            left = mid + 1;
        }
        else
        {
            right = mid -1;
        }
    }
    cout << right;
    tm.getTimeSpan("search loop"); 

    // for(int i = left; i <= right; i++)
    // {
    //     if(!Judge(n,m,i))
    //     {
    //         cout << i-1;
    //         break;
    //     }   
    // }
    return 0;
}