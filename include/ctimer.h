#pragma once

#include "time.h"
#include <cstdio>
#include <string>
#include <map>
using namespace std;

class CTimer
{
    public: 
    void start()
    {
        _start = clock(); //开始时间
    }

    void getTimeSpan(string msg)
    {
        clock_t checkPoint = clock();
        printf("time used in %s is %.2lf ms\n", msg.c_str(), (double)(checkPoint - _start)/CLOCKS_PER_SEC*1e3);

        _start = clock(); //move the start point
    }

    void checkTimeSpan(string tag)
    {
        clock_t checkPoint = clock();
        double span = (double)(checkPoint - _start)/CLOCKS_PER_SEC*1e3; //milli second

        std::map<string, double>::iterator it = _timeRecord.find(tag); //查找值
	    if (it == _timeRecord.end()) 
        {
            _timeRecord.insert(std::pair<string, double>(tag, span));
        }
        else
        {
            _timeRecord[tag] += span;
        }

        _start = clock(); //move the start point
	 }

     void OutputStat()
     {
        double totaltm = 0;
        int nCnt = 0;
        for (auto it = _timeRecord.begin(); it != _timeRecord.end(); it++) 
        {
            printf("%s %.2f\n", it->first.c_str(), it->second);
            totaltm += it->second;
            nCnt++;
        }

        printf("total span counted: %d, time: %.2f, average span: %.2f\n", nCnt, totaltm, totaltm / nCnt);

     }

private: 
    clock_t _start;
    map<string, double> _timeRecord;
};
