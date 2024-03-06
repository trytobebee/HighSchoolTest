#pragma once

template<typename _T>
bool removeArrayElm(_T *pArray, int& length, int index2Remv)
{
    //remove the elem @ index2Remv
    if(index2Remv >= length)
    {
        //illegal
        return false;
    }

    //move the items one position forward to remove the target one
    // 0 1 2 3 4 -> 0 2 3 4 (move 2 3 4 one position forward to eliminate 1)
    memcpy(pArray+index2Remv, pArray+index2Remv+1, (length-1 - index2Remv)*sizeof(_T));
    length = length - 1; 
    return true;
}

int* encode(int n, int* pData2Encode)
{
    int *pCode = new int[n];
    for(int i = 0; i < n; i++)
    {
        pCode[i] = 0;
    }    

    //encoding   
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(pData2Encode[i] > pData2Encode[j])
            {
                pCode[i]++;
            }
        }
    }

    return pCode;
}

int* decode(int n, int* pcodes)
{
    int* pcodebook = new int[n]; //{0, 1, 2, 3, 4, 5, 6, ..., n-1}
    for(int i = 0; i < n; i++)
    {
        pcodebook[i] = i;
    }

    int *pdecodes = new int[n];//decode result will be stored here

    //decoding is conducted from the last code
    //the logic is, given the code is "0 0 0 3 1 2"
    //we know the last code is 2, means among the entire codebook, 
    //there is 2 elems smaller than this one, which means the real value of it will be 2.
    int remainCodes = n;
    for(int i = n-1; i >= 0; i--)
    {
        pdecodes[i] = pcodebook[pcodes[i]];
        if(!removeArrayElm<int>(pcodebook, remainCodes, pcodes[i]))
        {
            //cout << "warning, error happens when remove " << pdecodes[i] << "th item from codebook" << endl;
            return nullptr;
        }
    }

    return pdecodes;
}