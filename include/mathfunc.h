#pragma once
#include "math.h"
#include "sorter.h"
#include <cstdio>

namespace mathfunc
{
    inline bool isPrime(int a)
    {
        if (a < 1)
        {
            printf("illegal input\n");
            return false;
        }
        else if(a == 1)
            return false;    
        if(a == 2)
            return true;

        for(int i = 2; i <= sqrt(a); i++)
        {
            if(a % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    inline bool isPrime(int a, int* primeList, int primeCount)
    {
        if (a < 1)
        {
            printf("illegal input\n");
            return false;
        }

        else if(a == 1)
            return false;    
        if(a == 2)
            return true;

        //只需要检查之前的质数是否是因子就ok了，不用查看合数了
        int i = 0;
        while(primeList[i] <= sqrt(a))
        {
            if(a % primeList[i] == 0)
            {
                return false;
            }

            i++;
            if(i >= primeCount)
            {
                printf("prime list isn't long enough, could miss some factor, this function returns unknown result\n");
                break;
            }
        }
            
        return true;
    }

    inline bool EnlistAllPrime(bool speedup, int* &primes, int& count)
    {
        int i = 2;
        primes = new int[100*1024*1024];
        count = 0;
        while(true)
        {
            bool ret;
            if(speedup)
            {
                ret = isPrime(i, primes, count); //这里会传入当前已经发现的所有的质数
            }
            else
            {
                ret = isPrime(i);
            }

            if(ret)    
            {
                primes[count] = i;
                count++;
                
                // if(primeCount % 1000 == 0)
                // {
                //     printf("第%d个质数为%d\n", primeCount,i);
                // }
            }   

            i++;
            if(i > 20*1024*1024)
                break;
        }

        
        return true;
    }

    inline bool GetAllFactor(int a, int *&factors, int& numFactors)
    {
        factors = new int[a]; //maximum < a
        int k = 0;
        numFactors = 0;
        factors[0] = 1;
        factors[1] = a;
        k = 1;
        for(int i = 2; i <= sqrt(a); i++)
        {
            if(a % i == 0)
            {
                factors[k * 2] = i;
                numFactors = 2 * k + 1;
                if(i != a/i)
                {
                    factors[k * 2 + 1] = a / i;
                    numFactors = 2*k + 1 + 1;
                }    
                
                k++;
                //return false;
            }
        }
        return true;
    }

    //euclid method来求最大公约数
    inline int GetMaxCofactor(int a, int b)
    {
        //默认 a > b, 不满足就调换一下
        if(a < b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        //a,b的最大公约数是 (a mod b, b)的最大公约数，一次辗转类推
        int r = a % b;
        if(r == 0)
            return b;

        return GetMaxCofactor(b, r);
    }

    int GetMaxCofactor(int * numbers, int cnt)
    {
        if(cnt < 2)
            return -1;

        int mcf = GetMaxCofactor(numbers[0], numbers[1]);
        for(int i = 2; i < cnt; i++)
        {
            mcf = GetMaxCofactor(mcf, numbers[i]);
        }

        return mcf;
    }


    // //求最大公约数, 原始的做法
    // inline int GetMaxCofactor(int a, int b)
    // {
    //     if(a>=b && a%b==0)
    //         return b;
    //     else if(a<=b && b%a==0)
    //         return a;
        
    //     int *aFactors;
    //     int aFactorCount;
    //     GetAllFactor(a, aFactors, aFactorCount);
        
    //     int maxCofactor = 1;
    //     for(int i = 0; i < aFactorCount; i++)
    //     {
    //         if(b % aFactors[i] == 0 && aFactors[i] > maxCofactor)
    //         {
    //             maxCofactor = aFactors[i];
    //         }
    //     }

    //     return maxCofactor;
    // }

    //求最小公倍数
    inline int GetLeastCoMultiple(int a, int b)
    {
        if(a>=b && a%b==0)
            return a;
        else if(a<=b && b%a==0)
            return b;

        return a*b / GetMaxCofactor(a,b);
    }

    //求出所有的质因数
    inline bool GetAllPrimeFactor(int a, int *&factors, int& numFactors)
    {
        factors = new int[a]; //maximum < a
        int *primefactors = new int[a];

        int k = 0;
        numFactors = 0;
        factors[0] = 1;
        factors[1] = a;
        k = 1;
        for(int i = 2; i <= sqrt(a); i++)
        {
            if(a % i == 0)
            {
                factors[k * 2] = i;
                numFactors = 2 * k + 1;
                if(i != a/i)
                {
                    factors[k * 2 + 1] = a / i;
                    numFactors = 2*k + 1 + 1;
                }    
                k++;
            }
        }

        //filter all non-prime factors
        k = 0;
        for(int i = 0; i < numFactors; i++)
        {
            if(isPrime(factors[i]))
            {
                primefactors[k] = factors[i];
                k++;
            }
        }
        numFactors = k;
        delete[] factors;
        
        factors = primefactors;
        return true;
    }

    //a faster version of GetAllPrimeFactor
    inline bool GetAllPrimeFactorLight(int numInput, int *&factors, int& numFactors)
    {
        numFactors = 0;
        int* All = new int[numInput];
        int factor = 2;
        
        //将每次获得的因数从原数中除去，这样只要从最小的因数开始处理
        //可以保证获得因数都是质因数
        while(numInput >= 2 && factor <= sqrt(numInput))
        {
            if(numInput % factor == 0)
            {
                All[numFactors] = factor;
                numFactors++;
                
                while(numInput % factor == 0)
                {
                    //内层循环保证这个factor有多次出现，被去除干净
                    numInput = numInput / factor;
                }
            }
            
            factor++;
        }
        
        //如果剩下的不是1，那将剩下的numInput算作最后一个质因子
        //如果本身是质数，应该剩下的就是自身，并且All数组中没有内容
        if(numInput > 1)
        {
            All[numFactors] = numInput;
            numFactors++;
        }

        factors = All;
        return true;
    }

    inline bool PrimeFactorization(int numInput, int* &factorResult, int& numFactors)
    {
        numFactors = 0;
        int* All = new int[numInput];
        int factor = 2;
        
        //将每次获得的因数从原数中除去，这样只要从最小的因数开始处理
        //可以保证获得因数都是质因数
        while(numInput >= 2 && factor <= sqrt(numInput))
        {
            while(numInput % factor == 0)
            {
                //内层循环保证这个factor如果可以多次被整除，那么可以连续加入质因数范围
                All[numFactors] = factor;
                numInput = numInput / factor;
                numFactors++;
            }
            factor++;
        }
        
        //如果剩下的不是1，那将剩下的numInput算作最后一个质因子
        //如果本身是质数，应该剩下的就是自身，并且All数组中没有内容
        if(numInput > 1)
        {
            All[numFactors] = numInput;
            numFactors++;
        }

        factorResult = All;
        return true;
    }

    //统计两个排过序的数组中有多少一样的元素，m,n分别是第一个数组和第二个数组的长度
    inline int findCommonElements(int arr1[], int arr2[], int m, int n) 
    {
        //vector<int> result;
        int cnt = 0;
        int i = 0, j = 0;

        while(i < m && j < n) 
        {
            if(arr1[i] == arr2[j]) 
            {
                cnt++;
                i++;
                j++;
            }
            else if(arr1[i] < arr2[j]) 
            {
                i++;
            }
            else 
            {
                j++;
            }
        }

        return cnt;
    }

    //n!
    inline long long factorial_sim(int n)
    {
        long long result = 1;
        for(int i = 1; i <= n; i++)
        {
            result = result * n;
        }
        return result;
    }


    //把string转化成int数字
    int StrToInt(char* str, int len, bool reverse = false)
    {
        int val = 0;
        for(int i = 0; i < len; i++)
        {
            if(!reverse)
                val = val * 10 + (str[len-1 - i]-'0');
            else
                val = val * 10 + (str[i] - '0');
        }
        return val;
    }

    //带周期的加和减
    inline bool roundAdd(int& x, int round, int delta = 1)
    {
        bool goRound = false;
        x += delta;
        if(x > round)
        {
            x -= round;
            goRound = true;
        }    
        
        return goRound;
    }

    inline bool roundMinus(int& x, int round, int delta = 1)
    {
        bool goRound = false;
        x -= delta;
        if(x < 0)
        {
            x += round;
            goRound = true;
        }    
        
        return goRound;
    }
}