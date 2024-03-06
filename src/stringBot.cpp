#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<vector>
#include<set>
#include "ctimer.h"
#include "mathfunc.h"
#include "strmatch.h"

using namespace std;

//struct to hold the string to check
struct leafNode
{
    string content;
    int firstPos; // the first occurence position
    int previousNode; //the previous node in the entire vector
    int thisSuffix; //the recent suffix added
    int count; //to save the match count 

    leafNode()
    {
        count = -1;
        firstPos = -1;
        previousNode = -1;
        thisSuffix = -1;
    }

    leafNode(const leafNode& ln)
    {
        content = ln.content;
        
        count = ln.count;
        firstPos = ln.firstPos;
        previousNode = ln.previousNode;
        thisSuffix = ln.thisSuffix;
    }
};

//参数是纯的字符串数组, 批量检查srcText中是否存在subUnits中的串
int* checkCnt(string* subUnits, int nSubUnit, string srcText, int& nonZeroUnitCnt)
{
    int *pCnt = new int[nSubUnit];
    nonZeroUnitCnt = 0;
    int* pos = new int[srcText.length()];
    for(int i = 0; i < nSubUnit; i++)
    {
        pCnt[i] = KMPSearch(subUnits[i], srcText, pos);
        if(pCnt[i]>0)
            nonZeroUnitCnt++;
    }
    return pCnt;
}

//只检查这些新的字符串是否出现在text中
int checkCnt(vector<leafNode>& leaves, string srcText, int& nonZeroUnitCnt, string& maxSub)
{
    nonZeroUnitCnt = 0;
    int roundMax = 0;
    
    for(int i = 0; i < leaves.size(); i++)
    {
        if(leaves[i].count == -1) //只有上一轮新加入的leafnode的count才会是-1
        {
            leaves[i].count = KMPSearch(leaves[i].content, srcText, leaves[i].firstPos);
            if(leaves[i].count != 0)
            {
                nonZeroUnitCnt++;
                int value = leaves[i].count * leaves[i].content.length();
                if(roundMax < value)
                {
                    roundMax = value;
                    maxSub = leaves[i].content;
                }    
            }
        }    
    }
    return roundMax;
}

//check leaves并获取，这些字符串在text中的所有位置
int checkCnt(vector<leafNode>& leaves, string srcText, int& nonZeroUnitCnt, string& maxSub, int** pPos)
{
    nonZeroUnitCnt = 0;
    int roundMax = 0;
    int activeLeafIndex = 0;
    
    for(int i = 0; i < leaves.size(); i++)
    {
        if(leaves[i].count == -1) //只有上一轮新加入的leafnode的count才会是-1
        {
            if(pPos != NULL)
            {
                leaves[i].count = KMPSearch(leaves[i].content, srcText, pPos[activeLeafIndex]);
            
                if(leaves[i].count != 0)
                {
                    leaves[i].firstPos = pPos[activeLeafIndex][0]; //为了兼容就的buildvalidpairs方法
                    nonZeroUnitCnt++;
                    int value = leaves[i].count * leaves[i].content.length();
                    if(roundMax < value)
                    {
                        roundMax = value;
                        maxSub = leaves[i].content;
                    }    
                }
            }
            else
            {
                //warning, memory not allocated
                printf("warning, memory not allocated\n");
            }
            activeLeafIndex++;           
        }    
    }
    return roundMax;
}

//deprecated, slower version
//build the valid pairs of suffix
void BuildValidPairs(string text, const vector<leafNode>& suffixVec, set<int>& validPairs, int** pPos)
{
    //清空以确保没有历史遗留
    validPairs.clear();

    int indexi = 0;
    set<int> matchPoint;
    for(int i = 0; i < suffixVec.size(); i++)
    {
        matchPoint.clear();
        for(int j = 0; j < suffixVec[i].count; j++)
        {
            int MatchPos = pPos[i][j] + suffixVec[i].content.length();
            matchPoint.insert(MatchPos);
        }

        for(int j = 0; j < suffixVec.size(); j++)
        {
            for(int k = 0; k < suffixVec[j].count; k++)
            {
                if(matchPoint.count(pPos[j][k]))
                    validPairs.insert(suffixVec[i].thisSuffix * suffixVec.size() + suffixVec[j].thisSuffix);
            }    
        }
    }
}

void BuildValidPairs_light(string text, const vector<leafNode>& suffixVec, set<int>& validPairs, int** pPos)
{
    //清空以确保没有历史遗留
    validPairs.clear();

    int indexi = 0;
    for(int i = 0; i < suffixVec.size(); i++)
    {
        int *pLeafEnd = new int[suffixVec[i].count];
        memcpy(pLeafEnd, pPos[i], suffixVec[i].count * sizeof(int));
        for(int j = 0; j < suffixVec[i].count; j++)
            pLeafEnd[j] = pPos[i][j] + suffixVec[i].content.length();

        for(int j = 0; j < suffixVec.size(); j++)
        {
            if(mathfunc::findCommonElements(pLeafEnd, pPos[j], suffixVec[i].count, suffixVec[j].count))
                validPairs.insert(suffixVec[i].thisSuffix * suffixVec.size() + suffixVec[j].thisSuffix);  
        }

        delete[] pLeafEnd;
        pLeafEnd = NULL;
    }
}

bool PassBasicCheck(
    int i, //index of item in leafVec
    int j, //index of suffix
    const vector<leafNode> & leafVec, 
    const vector<leafNode> & suffixVec,
    const set<int> & validSuffixPairs,
    const set<string>& dictString, 
    const int maxValue, 
    const string& text)
{
    //这里可以过滤掉一些从count角度不合理的case
    int pairkey = leafVec[i].thisSuffix * suffixVec.size() + j;
    if(!validSuffixPairs.count(pairkey))
        return false;

    string newKey = leafVec[i].content + suffixVec[j].content;
    if(dictString.count(newKey))
        return false;

    //基本过滤： 1. 当leafVec最后的位置不够加上suffix
    if(leafVec[i].firstPos + leafVec[i].content.length() + suffixVec[j].content.length() > text.length())
        return false;

    //leaf count为1，那么suffix在原文中应紧随其后
    if(leafVec[i].count == 1)
    {
        //这种情况下直接判断加上suffix是否可能，如果不可能直接就skip
        if(text.substr(leafVec[i].firstPos + leafVec[i].content.length(), suffixVec[j].content.length()) != suffixVec[j].content)
            return false;
    }

    //suffix如果count为1，那么他前面的是要加的这个string
    if(suffixVec[j].count == 1)
    {
        if(maxValue > text.length())
            return false;
        if(suffixVec[j].firstPos < leafVec[i].content.length() || text.substr(suffixVec[j].firstPos - leafVec[i].content.length(), leafVec[i].content.length()) != leafVec[i].content)
            return false;
    }

    return true;
}

int ProcessNextRound(
    string text, 
    const int& maxValue, 
    set<string>& dictString, 
    const set<int>& validSuffixPairs, 
    vector<leafNode>& leafVec, 
    int** pLeafPos, 
    const vector<leafNode>& suffixVec, 
    int** pSuffixPos)
{
    //leafvec中已经经过最近一次检查
    //pLeafPos中保存了每个本轮有效的leafNode的match position
    int NewlyAdded = 0;
    int numExist = leafVec.size();
    int leafIdx = 0; //实际在这轮中的有效leaf的index，用来访问position数组 pLeafPos
    set<int> matchPoint; //used in option1
    for(int i = 0; i < numExist; i++)
    {
        if(leafVec[i].count > 0)
        {
            if(maxValue > text.length() && leafVec[i].count == 1)
            {
                //skip, in this case this leaf won't bring better string option
            }
            else
            {
                //update the leaf position array to reflect the end of each match position possible match with suffix
                for(int j = 0; j < leafVec[i].count; j++)
                    pLeafPos[leafIdx][j] += leafVec[i].content.length();

                for(int j = 0; j < suffixVec.size(); j++)
                {
                    //normal checks
                    if(!PassBasicCheck(i, j, leafVec, suffixVec, validSuffixPairs, dictString, maxValue, text))
                    {
                        continue;
                    }    

                    //stronger requirement: 检查每一个match位置，看看可否让suffix接在后面
                    bool needed = false;
                    int coCnt = mathfunc::findCommonElements(pLeafPos[leafIdx], pSuffixPos[j], leafVec[i].count, suffixVec[j].count);
                    if(coCnt > 0)
                        needed = true;

                    //排除不合理的case
                    if(maxValue > text.length() && (coCnt == 1 || coCnt * (text.length() - pLeafPos[leafIdx][0]) < maxValue))
                        needed = false;

                    if(needed)
                    {
                        //是一个可行的new string
                        leafNode ln;
                        ln.content = leafVec[i].content + suffixVec[j].content;
                        ln.thisSuffix = j;
                        ln.previousNode = i;
                        leafVec.push_back(ln);
                        NewlyAdded++;
                        dictString.insert(ln.content);
                    }
                }
            }
            leafIdx++;
            leafVec[i].count = 0; //set 0, 这样之前的leaf在下次计算时候会跳过
        }
    }
    //cout << "skip1: " << skipCount1 << ", skip2: " << skipCount2 << endl;
    return NewlyAdded;
}

int main()
{
    //input process
    CTimer tmDebug;
    tmDebug.start();

    string text;
    //cin >> text;
    text = "tuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqlejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbiptuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbipltuumrhzpfymclgyizkdzyuflixktyhyjcuogmglcuennjuikrtdllvgnyumsbtuvgqejsavrjmofmzgomhgbipoztjsznklsqzqvletssw";
    //text = "zmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswktjydbmzmuucrfnyjrfswkto";
    int nSubUnit;
    cin >> nSubUnit;
    
    string *psubUnits = new string[nSubUnit];
    
    //从console读进来
    // for(int i = 0; i < nSubUnit; i++)
    // {
    //     cin >> psubUnits[i];
    // }
    
    //直接生成
    int cap = text.length();
    int error = cap * 0.1;
    for(int i = 0; i < nSubUnit; i++)
    {

        int length = (rand() % cap);
        if(rand() % cap < error && length < cap - 20 )
        {
            int x = rand() % (cap - length);
            psubUnits[i] = text.substr(x, length) + "xaeads"; //加些noise string
        }    
        else
        {
            int x = rand() % (cap - length);
            psubUnits[i] = text.substr(x, length);
        }
    }

    //计算流程从此开始
    int maxValue = 0; 
    string maxSubstring;
    int suffixCnt = 0;

    //第一次先确定合法的suffix
    int nonZeroUnitCnt = 0;
    int* pCnts = checkCnt(psubUnits, nSubUnit, text, nonZeroUnitCnt);
    
    suffixCnt = nonZeroUnitCnt;
    vector<leafNode> suffixVec;
    int suffixIdx = 0;
    for(int i = 0; i < nSubUnit; i++)
    {
        if(pCnts[i]>0)
        {
            leafNode suffixx;
            suffixx.content = psubUnits[i];
            suffixx.thisSuffix = suffixIdx;
            suffixIdx++;
            suffixVec.push_back(suffixx);
        }    
    }

    int** pSuffixPos = new int*[suffixVec.size()];
    for(int i = 0;i < suffixVec.size(); i++)
        pSuffixPos[i] = new int[text.length()];

    checkCnt(suffixVec, text, nonZeroUnitCnt, maxSubstring, pSuffixPos);
    //cout << "input text length: " << text.length() << ", legal suffix #: " << nonZeroUnitCnt << "suffixvec size: " << suffixVec.size() << endl;
    
    set<int> validSuffixPairs; //确定suffix之间能够搭配
    BuildValidPairs_light(text, suffixVec, validSuffixPairs, pSuffixPos);

    //开始正式的循环来寻找合适的新字符串 
    int round = 0;
    int NewlyAdded = 0;

    set<string> dictString; //save所有之前见过的合理的leaf content，用以去重计算过程
    vector<leafNode> leafVec; //save all the leaves.
    
    for(int i = 0; i < suffixCnt; i++)
    {
        leafNode ln;
        ln.content = suffixVec[i].content;
        //ln.quota = new suffixQuota(initialQuota);
        //ln.quota->DecreaseQuota(i, 1);
        ln.thisSuffix = i;
        leafVec.push_back(ln);
        NewlyAdded++; 
    }

    tmDebug.getTimeSpan("prepare before iteration");
    while( NewlyAdded > 0)
    {
        cout << "round " << round << " , # of strings to check: " <<  NewlyAdded << " leafvec.size: " << leafVec.size() << " dict size: " << dictString.size() << endl;
        
        //检查此次的所有待检查项，发现成功的就留下
        int roundMax;
        string roundMaxStr;
        
        
        //prepair memory for position values
        int ** pLeafPos = new int*[NewlyAdded];
        for(int i = 0; i < NewlyAdded; i++)
        {
            pLeafPos[i] = new int[text.length()];
        }
        roundMax = checkCnt(leafVec, text, nonZeroUnitCnt, roundMaxStr, pLeafPos);
        
        if(nonZeroUnitCnt == 0) //没有新的合适的，退出
            break;
        
        //更新最大值
        if(roundMax > maxValue)
        {
            maxValue = roundMax;
            maxSubstring = roundMaxStr;
        }

         cout << "nonzero: " << nonZeroUnitCnt << " maxvalue: this/Max" << roundMax << "/" << maxValue << ", constructing the new round data" << endl;
        int newRoundCnt = ProcessNextRound(
            text, 
            maxValue, 
            dictString, 
            validSuffixPairs, 
            leafVec, 
            pLeafPos, 
            suffixVec, 
            pSuffixPos);
        
        //clean memory
        for(int i = 0; i < NewlyAdded; i++)
        {
            delete[] pLeafPos[i];
        }
        delete[] pLeafPos;
        NewlyAdded = newRoundCnt;
        
        char msg[1024];
        sprintf(msg, "process round %02d", round);
        tmDebug.checkTimeSpan(string(msg));
        round++;
    }
    tmDebug.OutputStat();
    cout << maxValue; //<< " " << maxSubstring.length() << " " << maxSubstring.substr(194,200);
    return 0;
}