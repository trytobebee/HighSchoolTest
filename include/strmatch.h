#pragma once

#include <string>
using namespace std;

void inline computeLPSArray(string pat, int M, int lps[])
{
 
    // Length of the previous longest
    // prefix suffix
    int len = 0;
    int i = 1;
    lps[0] = 0; // lps[0] is always 0
 
    // The loop calculates lps[i] for
    // i = 1 to M-1
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
 
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not
                // increment i here
            }
            else // if (len == 0)
            {
                lps[i] = len;
                i++;
            }
        }
    }
}


int inline KMPSearch(string pat, string txt, int& firstPos)
{
    if(txt.length() < pat.length() || pat.length() == 0)
        return 0;
    int M = pat.length();
    int N = txt.length();
 
    // Create lps[] that will hold the longest
    // prefix suffix values for pattern
    int *lps = new int[M];
    int j = 0; // index for pat[]
 
    // Preprocess the pattern (calculate lps[]
    // array)
    computeLPSArray(pat, M, lps);
 
    int i = 0; // index for txt[]
    int res = 0;
 
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
 
            // When we find pattern first time,
            // we iterate again to check if there
            // exists more pattern
            j = lps[j - 1];
            if(res == 0)
               firstPos = i - pat.length();
            
            res++;
        }
 
        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
 
            // Do not match lps[0..lps[j-1]]
            // characters, they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    if(lps)
        delete[] lps;
    return res;
}

int inline KMPSearch(string pat, string txt, int* pPos)
{
    if(txt.length() < pat.length() || pat.length() == 0)
        return 0;
    int M = pat.length();
    int N = txt.length();
 
    // Create lps[] that will hold the longest
    // prefix suffix values for pattern
    int *lps = new int[M];
    int j = 0; // index for pat[]
 
    // Preprocess the pattern (calculate lps[]
    // array)
    computeLPSArray(pat, M, lps);
 
    int i = 0; // index for txt[]
    int res = 0;
 
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
 
            // When we find pattern first time,
            // we iterate again to check if there
            // exists more pattern
            j = lps[j - 1];
            //if(res == 0)
            //    firstPos = i - pat.length();
            pPos[res] = i - pat.length(); //here might be memory access issue, make sure memory are pre-allocated
            res++;
        }
 
        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
 
            // Do not match lps[0..lps[j-1]]
            // characters, they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    if(lps)
        delete[] lps;
    return res;
}