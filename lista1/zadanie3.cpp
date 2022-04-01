#include <bits/stdc++.h>

using namespace std;

int n = 0;
vector<vector<int>> G, R;
vector<bool>visD;
vector<int> pathD;
deque<int> Q;

void DFS(int i)
{   
    visD[i] = 1;
    for(int j = 0; j < G[i].size(); j++)
    {
        if(!visD[G[i][j]])
        {
            DFS(G[i][j]);
        }
    }
    pathD.push_back(i);
}

void DFSR(int i)
{   
    visD[i] = 1;
    for(int j = 0; j < R[i].size(); j++)
    {
        if(!visD[R[i][j]])
        {
            DFSR(R[i][j]);
        }
    }
    pathD.push_back(i);
}

vector<vector<int>> SCC()
{
    vector<vector<int>> comp;
    comp = vector<vector<int>>(0);
    vector<int> stack = pathD;
    visD = vector<bool>(n, false);
    for(int i = stack.size(); i >=0 ;i--)
    {
        pathD = vector<int>(0);
        if(!visD[stack[i]])
        {
            DFSR(stack[i]);
            comp.push_back(pathD);
        }
    }
    return comp;
}
int main()
{  
    int m;
    cin>>n>>m;
    pathD = vector<int>(0);
    G = vector<vector<int>>(n, vector<int>(0));
    R = vector<vector<int>>(n, vector<int>(0));
    visD = vector<bool>(n, false);

    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        G[a].push_back(b);
        R[b].push_back(a);
    }
    DFS(0);
    
    vector<vector<int>> components = SCC();

    for(int i = 0; i < components.size(); i++)
    {
        cout<<"SCC #"<<i<<":\n";
        for(int j = 0; j < components[i].size(); j++)
        {
            cout<<components[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}