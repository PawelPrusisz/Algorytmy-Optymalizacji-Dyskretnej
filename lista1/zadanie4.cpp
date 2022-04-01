#include <bits/stdc++.h>

using namespace std;
int n;
vector<vector<int>> G;
vector<pair<bool,bool>> visB;
vector<int> pathB;

bool BFS(int k)
{  
    queue<int> Q;
    Q.push(k);

    while(!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        visB[cur].first = 1;
        pathB.push_back(cur);
        for(int i = 0; i < G[cur].size(); i++)
        {
            if(!visB[G[cur][i]].first)
            {
                visB[G[cur][i]].first = 1;
                visB[G[cur][i]].second = !visB[cur].second;
                Q.push(G[cur][i]);
            }
            else if(visB[G[cur][i]].second == visB[cur].second)
            {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    int mode;
    cin>>mode;
    int m;
    cin>>n>>m;
    pathB = vector<int>(0);
    G = vector<vector<int>>(n, vector<int>(0));
    visB = vector<pair<bool,bool>>(n, make_pair(false, false));

    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        G[a].push_back(b);
        if(mode == 0)G[b].push_back(a);
        
    }
    if(BFS(0))
    {
        cout<<"graf jest dwudzielny\nV1:\n";
        for(int i = 0; i < n; i++)
        {
            if(!visB[i].second)
            {
                cout<<i<<" ";
            }
        }
        cout<<"\nV2:\n";
        for(int i = 0; i < n; i++)
        {
            if(visB[i].second)
            {
                cout<<i<<" ";
            }
        }
        cout<<"\n";
    }
    else
    {
        cout<<"graf nie jest dwudzielny";
    }


    return 0;
}