#include<iostream>
#include<iomanip>
#include<cstdio>
using namespace std;


struct Direction
{
    int _rowDir; //the change of row
    int _colDir; //the chagne of col

    void init(int rowDir, int colDir)
    {
        _rowDir = rowDir;
        _colDir = colDir;
    }

    Direction(int rowDir, int colDir)
    {
        init(rowDir, colDir);
    }

    void TurnRight90()
    {
         //-1, 0  ->  0, 1 -> 1, 0 ->  0, -1
         if(_rowDir == -1)
         {
            _rowDir = 0;
            _colDir = 1;
         }
         else if(_colDir == 1)
         {
            _rowDir = 1;
            _colDir = 0;
         }
         else if(_rowDir == 1)
         {
            _rowDir = 0;
            _colDir = -1;
         }
         else if(_colDir == -1)
         {
            _rowDir = -1;
            _colDir = 0;
         }
    }
};

struct point
{
    int _row;
    int _col;

    void init(int row, int col)
    {
        _row = row;
        _col = col;
    }

    point()
    {
        _row = -1;
        _col = -1;
    }

    point(int row, int col)
    {
        init(row, col);
    }

    bool operator==(point other)
    {
        if(_row == other._row && _col == other._col)
            return true;
        else
            return false;
    }

    void move(Direction& change)
    {
        _row += change._rowDir;
        _col += change._colDir;
    }

    void moveback(Direction& change)
    {
        _row -= change._rowDir;
        _col -= change._colDir;
    }
};



bool OutScope(point x, int rowMax, int colMax)
{
    return x._row < 0 || x._row > rowMax || x._col < 0 || x._col > colMax;
}

void OutputSpace(int xspace[10][10], point mouse, point cat)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(xspace[i][j] == -1)
                cout << "* ";
            else if(xspace[i][j] == 0 && mouse == point(i,j))
                cout << "M ";
            else if(xspace[i][j] == 0 && cat == point(i,j))
                cout << "C ";
            else if(xspace[i][j] == 0)
                cout << ". ";
        }
        cout << endl;
    }

    cout << endl;
}


int main()
{
    int space[10][10];
    point mouse;
    point cat;

    //read inputs
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            char x;
            cin >> x;

            if(x == '*')
            {
                space[i][j] = -1;
            }    
            else if(x == '.')
            {
                space[i][j] = 0;
            }    
            else if(x == 'M')
            {
                mouse.init(i, j);
                space[i][j] = 0;
            }
            else if(x == 'C')
            {
                cat.init(i, j);
                space[i][j] = 0;
            }
        }
    }

    //start working while timer ticks
    int T = 0; //timer
    Direction mouseDir(-1, 0); //initial direction to the north, row will decrease, col stay still
    Direction catDir(-1, 0);
    while(T <= 60)
    {
        // print the process like a movie
        cout << T << endl;
        OutputSpace(space, mouse, cat);
        getchar();

        if(mouse == cat)
            break;
        
        mouse.move(mouseDir);
        if(space[mouse._row][mouse._col] == -1 || OutScope(mouse, 9, 9))
        {
            mouse.moveback(mouseDir); //recovery previous position
            mouseDir.TurnRight90();
        }
  
        cat.move(catDir);
        if(space[cat._row][cat._col] == -1 || OutScope(cat, 9, 9))
        {
            cat.moveback(catDir); //recovery previous position
            catDir.TurnRight90();
        }
        T++;    
    }

    if(T > 60)
        T = -1;

    cout << T << endl;

    return 0;
}