#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//get line input, there could be ' ' within the string
inline void GetStringInput(string& result)
{
    char inputString[1000] = {}; //set 0
    char ch;
    int length = 0;
    while (true) 
    {
        ch = cin.get();

        if(ch == EOF || ch == '\n')
            break;
        
        inputString[length] = ch;
        length++;
    }

    result = string(inputString);
}

//get input string line and parse the string with ' ' as separator
//save in the result vector.
inline void ParseStringInput(vector<string>& Result)
{
    string input;
    GetStringInput(input);
    const char* inputString = input.c_str();
    
    char tmp[1000] = {}; //set 0
    int tmpIndex = 0;
    for(int i = 0; i < input.length(); i++)
    {
        if(inputString[i] == ' ')
        {
            //copy the content to container if tmp isn't empty
            //if the string is started with ' ', then here tmp[0] will be 0 at the first time.
            if(tmp[0])
            {
                Result.push_back(string(tmp));
                //reset
                tmpIndex = 0;
                memset(tmp, 0, 1000);
            }   
        }
        else
        {
            tmp[tmpIndex++] = inputString[i];
        }
    }
    
    //if there is some chars left behind the last ' ', here the tmp[0] will have the last string with it.
    if(tmp[0])
        Result.push_back(string(tmp));
}

inline int Convert2String(int n, char str[100])
{
    if(n < 0)
    {
        printf("do not support negative number conversion\n");
        return -1;
    }

    int length = 0;
    int value = n;
    while(n > 0)
    {
        n = n / 10;
        length++;
    }

    for(int i = 0; i < length; i++)
    {
        str[length - 1 - i] = '0' + value % 10;
        value = value / 10;
    }

    str[length] = '\0';
    return length;
}

inline bool isPalindrome(char* strval, int length)
{
    int index = 0;
    bool isPalin = true;
    while(index < length / 2)
    {
        if(strval[index] != strval[length-1 - index])
        {
            isPalin = false;
            break;
        }
        index++;
    }
    return isPalin;
}