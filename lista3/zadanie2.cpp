#include <bits/stdc++.h>
#include <fstream>

#include <chrono>
#include <unistd.h>

using namespace std;
#define x first
#define y second
#define mp make_pair

const int inf = INT_MAX;

vector<vector<pair<int,int>>> G;
vector<int> Dist;
vector<int> Start;
vector<pair<int,int>> StartP2P;

int W = 0;
int n = 0;
int m = 0;
int iter = 0;
bool p2p = false;

vector<int> B;
vector<bool> Deleted;
pair<int,int> vertexWithMinDistance()
{
    int minDist = inf;
    int index = -1;
    for(int i = 0; i < n; i++)
    {
        if(minDist > Dist[i] && !Deleted[i])
        {
            index = i;
            minDist = Dist[i];
        }
    }
    return mp(index, minDist);
}
void Dial(int s)
{
    
    B = vector<int>(W+1);
    Deleted = vector<bool>(W+1, false);

    for(int i = 0 ; i <= W; i++)
    {
        pair<int,int> cur = vertexWithMinDistance();
        if(cur.x != -1)
        {
            Deleted[cur.x] = true;
            for(int j = 0; j < G[cur.x].size(); j++)
            {
                if(Dist[G[cur.x][j].x] > Dist[cur.x] + G[cur.x][j].y)
                {
                    Dist[G[cur.x][j].x] = Dist[cur.x] + G[cur.x][j].y;
                }
            }
        }
    }
    
}

void runTest()
{
    for(int j = 0; j < Start.size(); j++)
    {   
        auto strt = chrono::steady_clock::now();
        int start = Start[j];
        pair<int,vector<int>::iterator> Par;
        Par.x = inf;
        Dist = vector<int>(n, inf);
        Dist[start] = 0;
        Dial(start);
        cout<<iter<<": ";
        for(int i = 0; i < n; i++)
        {
            if(i != start)
            {
                if(Dist[i] == inf)
                {
                    cout<<"inf ";
                }
                else
                {
                    cout<<Dist[i]<<" ";
                }
            }
            else
            {
                cout<<"s ";
            }
        
        }
        iter++;
        cerr<<iter<<" ";
        auto end = chrono::steady_clock::now();
         std::chrono::duration<double, std::milli> fp_ms = end - strt;
        cerr<<(long long)(fp_ms.count()*1000)<<"\n";
        cout<<"\n######\n";
    }
    
}

void readGraph(string fileName)
{
    cerr<<"reading Graph definition from "<<fileName<<"\n";
    ifstream infile(fileName);
    string line;
    int in = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        char c;
        int a, b, d;
        if (!(iss>>c))
        {
            break;
        }
        else if(c == 'p')
        {   
            iss>>c>>c>>n>>m;
            cerr<<n<<" "<<m<<"\n";
            G = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(0));
        }
        else if(c == 'a')
        {
            iss>>a>>b>>d;
            a-=1;
            b-=1;
            in++;
            W = max(W, d);
            G[a].push_back(mp(b, d));
        }
    }
    cerr<<"read: "<<in<<" edges\n";
}

void readStart(string fileName)
{
    cerr<<"reading start nodes from "<<fileName<<"\n";
    ifstream infile(fileName);
    string line;
    int in = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        char c;
        int a;
        if (!(iss>>c))
        {
            break;
        }
        else if(c == 's')
        {
            iss>>a;
            in++;
            a--;
            Start.push_back(a);
        }
        
    }
    cerr<<"read: "<<in<<" starting nodes\n";
}

void readStartp2p(string fileName)
{
    cerr<<"reading p2p from "<<fileName<<"\n";
    ifstream infile(fileName);
    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        char c;
        int a, b;
        if (!(iss>>c))
        {
            break;
        }
        else if(c == 'a')
        {
            iss>>a>>b;
            a--;
            b--;
            StartP2P.push_back(mp(a,b));
        }
        
    }
}

int main(int argc, char *argv[], char *envp[])
{
    
    string inFile, startFile, startP2PFile, outFile;

    for(int i = 0; i < argc; i++ )
    {
        if((string)argv[i] == "-d")
        {
            i++;
            inFile = argv[i];
        }
        else if((string)argv[i] == "-ss")
        {
            i++;
            startFile = argv[i];
        }
        else if((string)argv[i] == "-oss")
        {
            i++;
            outFile = argv[i];
        }
        else if((string)argv[i] == "-p2p")
        {
            i++;
            startP2PFile = argv[i];
            p2p = true;
        }
        else if((string)argv[i] == "-op2p")
        {
            i++;
            outFile = argv[i];
        }
    }

    readGraph(inFile);
    
    if(!p2p)
    {
        readStart(startFile);
    }
    else
    {
        readStartp2p(startP2PFile);
    }


    runTest();

    return 0;
}