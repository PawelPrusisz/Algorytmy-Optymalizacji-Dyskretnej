#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> G;
vector<bool> visB, visD;
vector<int> pathD, pathB;
vector<pair<int,int>> treeD, treeB;

void DFS(int i)
{   
    visD[i] = 1;
    pathD.push_back(i);
    for(int j = 0; j < G[i].size(); j++)
    {
        if(!visD[G[i][j]])
        {
            DFS(G[i][j]);
            treeD.push_back(make_pair(i, G[i][j]));
        }
    }
}

void BFS(int k)
{  
    queue<int> Q;
    Q.push(k);

    while(!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        visB[cur] = 1;
        pathB.push_back(cur);
        for(int i = 0; i < G[cur].size(); i++)
        {
            if(!visB[G[cur][i]])
            {
                visB[G[cur][i]] = 1;
                Q.push(G[cur][i]);
                treeB.push_back(make_pair(cur, G[cur][i]));
            }
        }
    }
    
}

int main()
{
    cout<<"Podaj tryb: \n";
    int mode;
    cin>>mode;
    if(mode <= 0)mode = 0;
    else mode = 1;
    int n, m;
    cin>>n>>m;
    pathD = vector<int>(0);
    pathB = vector<int>(0);
    treeB = vector<pair<int,int>>(0);
    treeD = vector<pair<int,int>>(0);
    G = vector<vector<int>>(n, vector<int>(0));
    visB = vector<bool>(n, false);
    visD = vector<bool>(n, false);

    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        G[a].push_back(b);
        if(mode == 0)G[b].push_back(a);
    }
    BFS(0);
    DFS(0);
    cout<<"Path DFS:\n";
    for(int i = 0; i<pathD.size();i++)
    {
        cout<<pathD[i];
        if(i + 1<pathD.size()) cout<<"->";
    }

    cout<<"\nPath BFS:\n";
    for(int i = 0; i < pathB.size();i++)
    {
        cout<<pathB[i];
        if(i + 1<pathB.size()) cout<<"->";
    }
    cout<<"\nWypisa drzewo przeszukiwan? (Y/N)\n";
    string input = "";
    cin>>input;
    if(input == "Y")
    {
        cout<<"Drzewo DFS:\n";
        for(int i = 0; i < treeD.size();i++)
        {
            cout<<treeD[i].first<<"->"<<treeD[i].second<<"\n";
        }

        cout<<"\nDrzewo BFS:\n";
        for(int i = 0; i < treeB.size();i++)
        {
            cout<<treeB[i].first<<"->"<<treeB[i].second<<"\n";
        }
    }


    return 0;
}