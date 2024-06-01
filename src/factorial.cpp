#include <vector>
#include <iostream>
#include "ctimer.h"

using namespace std;
const int MOD = 998244353; // A common prime modulus

// Function to calculate the modular inverse of a number n modulo MOD
int inv(int n) {
    int result = 1, base = n;
    //long long lresult;
    int power = MOD - 2;
    while (power > 0) {
        if (power % 2 == 1) {
            result = ((long long)result * base) % MOD;
        }
        
        base = ((long long)base * base) % MOD;
        power /= 2;
    }
    return result;
}

// Function to precompute factorials and their inverses modulo MOD
void precomputeFactorials(vector<int>& fact, vector<int>& invFact, int maxN) {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= maxN; ++i) {
        fact[i] = ((long long)fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}

// Function to calculate n choose k modulo MOD
int comb(int n, int k, const vector<int>& fact, const vector<int>& invFact) {
    if (k < 0 || k > n) return 0;
    int numerator = fact[n];
    int denominator = ((long long)invFact[k] * invFact[n - k]) % MOD;
    return ((long long)numerator * denominator) % MOD;
}

int Test() {
    CTimer tmDebug;
    tmDebug.start();
    int maxN = 200000; // Suppose we want to compute combinations up to 100,000
    cin >> maxN;
    
    int votes[2000000];
    for(int i = 0; i < maxN; i++)
    {
        //cin >> votes[i];
        votes[i] = rand() % 2;
    }    
    tmDebug.getTimeSpan("get input ");
    //准备数据
    vector<int> fact(maxN + 1), invFact(maxN + 1);
    precomputeFactorials(fact, invFact, maxN);

    tmDebug.getTimeSpan("prepare the factorial vector ");
    cout << "finish prepare!" << endl;
    // // Example usage
    // int n = 919, k = 460;
    // cout << "C(" << n << ", " << k << ") mod " << MOD << " = " << comb(n, k, fact, invFact) << endl;

    long long sum = 0;
    int start = (maxN + 1) / 2;
    for(int i = 0; i < maxN; i++)
    {
        //在当前这个位置之前的投完后
        if(i > 0)
            start -= votes[i-1];
        for(int j = start; j <= maxN - i; j++)
        {
            int r = comb(maxN - i, j, fact, invFact);
            sum = sum + r;
            sum = sum % MOD;
        }
        //sum = rand() % MOD;
        //cout << sum << endl;
        sum = 0;    
    }
    tmDebug.getTimeSpan("cout ");
    return 0;
}


// int ComputeCombo(int n, int r, int lib[MAXN][MAXR], int m)
// {
//     //c(r,n)
//     //c(r,n) = c(r-1, n-1) + c(r, n-1);
//     int result = 0;
//     if(r == 0)
//         return 1;

//     if(lib[n][r] == 0)
//     {
//         if(n-r < r)
//         {
//             result = ComputeCombo(n, n-r, lib, m) % m;
//             //lib[n][r] = result;
//         }    
//         else
//         {
//             result = ComputeCombo(n-1, r-1, lib, m) % m + ComputeCombo(n-1, r, lib, m) % m;
//             lib[n][r] = result % m;
//         }
        
//     }
//     else
//     {
//         result = lib[n][r];
//     }

//     return result;
// }

// void printComboTriangle(int comblib[MAXN][MAXR])
// {
//     for(int i = 1; i < 50; i ++)
//     {
//         for(int j = 1; j <= i/2; j++)
//         {
//             cout << comblib[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// int main()
// {
//     int comblib[MAXN][MAXR] = {}; //to save the previously computed c(n, r)
//     int m = 998244353;
//     // for(int i = 1; i < MAXN; i ++)
//     // {
//     //     comblib[i][1] = i % m;
//     //     for(int j = 1; j <= i/2; j++)
//     //     {
//     //         ComputeCombo(i, j, comblib, m);
//     //     }

//     //     if(i % 100 == 0)
//     //     {
//     //         cout << "progress: " << i << endl;
//     //     }
//     // }
//     for(int i = 1; i < MAXN; i++)
//         comblib[i][1] = i % m;

//     int sum = 0;
//     for(int i = (919+1)/2; i <= 919; i++)
//     {
//         //current combo
//         int x = ComputeCombo(919, i, comblib, m);
//         cout << "C(919, " << i << "): " << x << endl;
//         sum += x;
//         sum = sum % m;
//     }

//     cout << "final result: " << sum << endl;
    
    
    
//     //printComboTriangle(comblib);

//     return 0;
// }