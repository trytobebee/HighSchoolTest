#include <iostream>
#include <vector>
using namespace std;

//用矩阵相乘来表示信息沿图传播的问题，在进行全图传播的时候是比较高效的一种做法
//但当信息是从一个点开始出发，并且图是比较稀疏的状态时，
//还是可以用稀疏矩阵来进行信息传递，否则可能出现高很多的计算代价

//只做选择的传播节点为起始的运算
std::vector<std::vector<int>> matrixMultiplyBySelRows(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2, vector<int> selectedRows) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

    if (cols1 != rows2) {
        return result;
    }
    for(int i = 0; i < selectedRows.size(); i++)
    {
        for (int j = 0; j < cols2; ++j) 
        {
            for (int k = 0; k < cols1; ++k) 
            {
                result[selectedRows[i]][j] += matrix1[selectedRows[i]][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

bool vectorEqual(std::vector<int>& v1, std::vector<int>& v2)
{
    if(v1.size() != v2.size())
        return false;

    for(int i = 0; i < v1.size(); i++)
    {
        if(v1[i] != v2[i])
        {
            return false;
        }
    }

    return true;
}

std::vector<int> findReachableNodes_sparse(std::vector<int>& reachableNodes, const std::vector<std::vector<int>>& adjacencyMatrix, int start, int N) 
{
    int size = adjacencyMatrix.size();
    std::vector<std::vector<int>> powerMatrix = adjacencyMatrix;
    std::vector<int> newReachableNodes;
    
    std::vector<int> selectRows;
    selectRows.push_back(start);

    for(int i = 1; i < N; i++)//乘法的次数为 N-1
    {
        powerMatrix = matrixMultiplyBySelRows(powerMatrix, adjacencyMatrix, selectRows);
        newReachableNodes.clear();
        
        for(int j = 0; j < size; j++)
        if (powerMatrix[start][j] > 0)
        {
            newReachableNodes.push_back(j);
        }    
        
        if(vectorEqual(reachableNodes, newReachableNodes))
        {
            //new iteration with same start nodes @ iteration " << i << endl;
            break; //no need to continue compute new possibilities
        } 

        reachableNodes.resize(newReachableNodes.size());
        for(int j = 0; j < newReachableNodes.size(); j++)
        {
            reachableNodes[j] = newReachableNodes[j];
        }
    }
    
    return reachableNodes;
}

int main() 
{
    std::vector<std::vector<int>> adjacencyMatrix;
    std::vector<std::vector<int>> weightMatrix;
    
    int N, t;
    //get inputs
    cin >> N; //number of node
    cin >> t; //number of jumps
    int maxWeightNodeIndexOfZero = 0;
    int maxWeightTmp = 0;
    for(int i = 0; i < N; i++)
    {
        vector<int> weightVec;
        weightMatrix.push_back(weightVec);
        for(int j = 0; j < N; j++)
        {
            int input;
            cin >> input;
            weightMatrix[i].push_back(input);

            if(i == 0 && maxWeightTmp < input)
            {
                maxWeightTmp = input;
                maxWeightNodeIndexOfZero = j;
            }    
        }
    }

    for(int i = 0; i < N; i++)
    {
        vector<int> adjVec;
        for(int i = 0; i < N; i++)
            adjVec.push_back(0);
        adjacencyMatrix.push_back(adjVec);
        
        int length;
        cin >> length;
        for(int j = 0; j < length; j++)
        {
            int input;
            cin >> input;
            adjacencyMatrix[i][input-1] = 1;
        }
    }

    //propagate from the start node for t times;
    int startNode = 0;
    std::vector<int> reachableNodes;
    findReachableNodes_sparse(reachableNodes, adjacencyMatrix, startNode, t);

    cout << "finished the propagation, and reachable nodes include:";
    for(int i = 0; i < reachableNodes.size(); i++)
    {
        cout << reachableNodes[i] << " ";
    }
    cout << endl;

    //if reachable contains the max weighted adjecent item of the first node, just return that value
    bool maxInreach = false;
    for (int i = 0; i < reachableNodes.size(); i++) 
    {
        if(reachableNodes[i] == maxWeightNodeIndexOfZero)
        {
            maxInreach = true;
            cout << maxWeightNodeIndexOfZero + 1 << endl;
            return 0;
        }
    }

    // std::cout << "Reachable Nodes: ";
    int weightsum = 0;
    int maxIndex;
    int maxWeightSum = 0;

    //else check the weight sum to get the max sum one
    for (int i = 0; i < reachableNodes.size(); ++i) 
    {
        //std::cout << reachableNodes[i] << " ";
        //for each reachable node(possible final destination of bomb)
        //check the weight for each [intermediate decision making] node, see which one get the largest
        
        weightsum = 0;
        for(int j = 0; j < N; j++)
        {
            weightsum += weightMatrix[j][reachableNodes[i]];
        }
        
        if(weightsum > maxWeightSum)
        {
            maxWeightSum = weightsum;
            maxIndex = reachableNodes[i];
        }
    }

    cout << maxIndex+1 << endl;
    
    return 0;
}