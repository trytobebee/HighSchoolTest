#include <iostream>
using namespace std;

int totalOptions = 0;
int outputs[100];//to save the outputs
int numUsed = 0;

void printOption(int lastCount)
{
    for(int j = 0; j < numUsed; j++)
    {
        cout << outputs[j] << " ";
    }
    cout << lastCount << endl;
}

//递归求解
void Build(int nTotal, int* choices, int choiceNum)
{
    for(int i = 0; i < choiceNum; i++)
    {
        //如果当前ntotal < choice[i] 那么就不需要继续了
        if(nTotal == choices[i])
        {
            totalOptions++; //完成一次完整的摆放
            //printOption(nTotal);
            break;
        }    
        else if(nTotal < choices[i])
        {
            break; //there is no valid choice
        }    
        else
        {
            //cout << choices[i] << " ";
            outputs[numUsed] = choices[i];
            numUsed++;

            Build(nTotal - choices[i], choices, choiceNum);
        }    
    }
    numUsed--;
}

int test()
{
    int n;
    cin >> n;
    int choiceNum = 3;
    int choices[3];
    
    choices[0] = 1;
    choices[1] = 2;
    choices[2] = 3;
    
    Build(n, choices, choiceNum);
    cout << totalOptions << endl;
    return 0;
}