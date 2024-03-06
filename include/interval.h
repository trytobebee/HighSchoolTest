struct Interval
{
    /* data */
    int start; 
    int end;
    
    Interval()
    {
        init(0, 0);
    }

    Interval(int x, int y)
    {
        init(x, y);
    }

    bool init(int x, int y)
    {
        if(x < 0 || y < 0 || y < x)
            return false;
        
        start = x;
        end = y;
        return true;
    }

    bool operator <(const Interval& other) const
    {
        return start < other.start;
    }

    bool operator >(const Interval& other) const
    {
        return start > other.start;
    }

    Interval operator =(const Interval& other)
    {
        start = other.start;
        end = other.end;
        return *this;
    }
    
};