#include<iostream>
#include "sorter.h"
#include "interval.h"
using namespace std;

int MergeIntervals()
{
    int lines;
    cin >> lines;
    Interval * intvs = new Interval[lines];

    for(int i = 0; i < lines; i++)
    {
        int iStart, iEnd;
        cin >> iStart >> iEnd;
        
        if(!intvs[i].init(iStart, iEnd))
        {
            cout << "illegal input start > end or negative number" << iStart << " " << iEnd << endl;
            return -1;
        }
    }

    sorters::Sort_TypedArray<Interval>(intvs, lines, false);
    Interval * finalIntvs = new Interval[lines];

    finalIntvs[0] = intvs[0];
    int finalLength = 1;
    for(int i = 1; i < lines; i++)
    {
        //cout << intvs[i].start << " " << intvs[i].end << endl;   
        if(intvs[i].end <= finalIntvs[finalLength-1].end)
        {
            //ignore, covered by previous intvs
        }
        else
        {
            if(intvs[i].start <= finalIntvs[finalLength-1].end)
            {
                //merge into finalIntvs
                finalIntvs[finalLength-1].end = intvs[i].end;
            }
            else
            {
                //new interval
                finalLength++;
                finalIntvs[finalLength-1] = intvs[i];
            }
        }
    }

    // totalLength ++;
    // for(int i = 0; i < finalLength; i++)
    // {
    //     totalLength -= (finalIntvs[i].end - finalIntvs[i].start)+1;
    // }

    // cout << totalLength << endl;
    return 0;
}