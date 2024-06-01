#include "mathfunc.h"

//闰年
inline bool isLeapYear(int y)
{
    return y % 400 == 0 || y % 100 != 0 && y % 4 == 0;
}

//转成天数
inline int GetYearDays(int y)
{
    if(isLeapYear(y))
        return 366;
    else
        return 365;
}

inline int GetMonthDays(int m, int y)
{
    if(m == 4 || m == 6 || m == 9 || m == 11)
        return 30;
    else if(m == 2)
    {
        if(isLeapYear(y))
            return 29;
        else
            return 28;
    }
    else
        return 31;
}

//检查一个年月日是否是合理的
inline bool isValidDate(int y, int m, int d)
{
    if(y < 0)
        return false;

    if(m <= 0 || m > 12)
        return false;

    if(d > GetMonthDays(m, y) || d < 1)
        return false;
    
    return true;
}

//日期加一天
inline void IncreaseDate(int& y, int& m, int& d)
{
    //assume这个日期是一个合理的日期
    d++;

    if(GetMonthDays(m, y) < d)
    {
        if(roundAdd(m, 12))
            y++; 
        
        d = 1;
    }
    
    return;
}

//日期减一天
inline void DecreaseDate(int& y, int& m, int& d)
{
    d--;

    if(d==0)
    {
        if(roundMinus(m, 12))
            y--;
        
        d = GetMonthDays(m, y);
    }
    
    return;
}
