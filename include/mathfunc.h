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
                printf("prime list isn't long enough, could miss some factor\n");
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
                ret = isPrime(i, primes, count);
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

    //求最大公约数
    int GetMaxCofactor(int a, int b)
    {
        if(a>=b && a%b==0)
            return b;
        else if(a<=b && b%a==0)
            return a;
        
        int *aFactors;
        int aFactorCount;
        GetAllFactor(a, aFactors, aFactorCount);
        
        int maxCofactor = 1;
        for(int i = 0; i < aFactorCount; i++)
        {
            if(b % aFactors[i] == 0 && aFactors[i] > maxCofactor)
            {
                maxCofactor = aFactors[i];
            }
        }

        return maxCofactor;
    }

    int GetLeastCoMultiple(int a, int b)
    {
        if(a>=b && a%b==0)
            return a;
        else if(a<=b && b%a==0)
            return b;

        return a*b / GetMaxCofactor(a,b);
    }

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

    
}