#include <bits/stdc++.h>

using namespace std;

int n = 0;
vector<vector<int>> G;
vector<bool>visD;
vector<bool>mark;
vector<int> pathD;

int DFS(int i)
{   
    if(visD[i])return 1;
    if(mark[i])return 0;
    int k = 1;
    mark[i] = true;

    for(int j = 0; j < G[i].size();j++)
    {
        k = min(k, DFS(G[i][j]));
    }

    mark[i] = false;
    visD[i] = true;
    pathD.push_back(i);
    return k;
}

int DFScontrol()
{
    bool missing = true;
    while(missing)
    {   
        missing = false;
        for(int i = 0; i < n; i++)
        {
            if(!visD[i])
            {
                missing = true;
                if(DFS(i) == 0)
                {
                    return 0;
                }
            }
        }
    }
    
    return 1;
}

int main()
{  
    int m;
    cin>>n>>m;
    pathD = vector<int>(0);
    G = vector<vector<int>>(n, vector<int>(0));
    visD = vector<bool>(n, false);
    mark = vector<bool>(n, false);

    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        G[a].push_back(b);
        
    }
    if(DFScontrol() == 0)
    {
        cout<<"Graf posiada cykl\n";
    }
    else
    {
        for(int i = 0; i < pathD.size();i++)
        {
            cout<<pathD[i];
            if(i + 1 < pathD.size())cout<<", ";
            else cout<<"\n";
        }
    }
    
    return 0;
}