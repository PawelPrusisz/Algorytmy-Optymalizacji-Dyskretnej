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
vector<int> Dist, Start;
vector<pair<int,int>> StartP2P;

int n = 0;
int m = 0;
int iter = 0;
bool p2p = false;

class PriorityQueue
{   
    private:
    vector<pair<int, int>> Heap;
    int size;
    
    public:
    PriorityQueue(int n)
    {
        pair<int, int> p;
        p.first = 0.0;
        p.second = 0;
        Heap = vector<pair<int, int>>(n, p);
        size = -1;
    }

    int parent(int i)
    {
        return (i-1)/2;
    }

    int leftChild(int i)
    {
        return (i*2)+1;
    }

    int rightChild(int i)
    {
        return (i+1)*2;
    }

    void shiftUp(int i)
    {
        while(i > 0 && Heap[parent(i)].first > Heap[i].first)
        {
            swap(Heap[parent(i)], Heap[i]);
            i = parent(i);
        }
    }

    void shiftDown(int i)
    {
        int maxIndex = i;

        int l = leftChild(i);

        if(l <= size && Heap[l].first < Heap[maxIndex].first)
        {
            maxIndex = l;
        }

        int r = rightChild(i);

        if(r <= size && Heap[r].first < Heap[maxIndex].first)
        {
            maxIndex = r;
        }

        if(i != maxIndex)
        {
            swap(Heap[i], Heap[maxIndex]);
            shiftDown(maxIndex);
        }
    }

    void insert(int x, int p)
    {
        pair<int,int> t;
        t.first = p;
        t.second = x;
        size++;
        Heap[size] = t;
        shiftUp(size);
    }

    void pop()
    {   
        if(size >= 0)
        {
            int result = Heap[0].second;

            Heap[0] = Heap[size];
            size--;
            shiftDown(0);
        }
    }
    //TODO: implementacja w log n zamiast n
    int findData(int i)
    {
        for(int j = 0; j <= size; j++)
        {
            if(Heap[j].second == i)
            {
                return j;
            }
        }
        return -1;
    }

    void changePriotity(int i, int p)
    {
        for(int j = findData(i);j != -1; j = findData(i))
        {
            if(Heap[j].first > p)
            {
                Heap[j].first = p;
                shiftUp(j);
            }
            else if(Heap[j].first < p)
            {
                Heap[j].first = p;
                shiftDown(j);
            }
        }
    }

    pair<int,int> top()
    {   
        if(size >= 0)
        {
            return Heap[0];
        }
        return mp(-1,-1);

    }

    void print()
    {
        for(int i = 0; i <= size; i++)
        {
            cout<<"("<<Heap[i].second<<", "<<Heap[i].first<<") ";
        }
        cout<<"\n";
    }
};

void Dijsktra(int s)
{
    PriorityQueue Q(m);
    Q.insert(s, 0);
    Dist[s] = 0;
    while(Q.top().x != -1)
    {
       
        pair<int,int> cur = Q.top(), next;
        Q.pop();
        \
        for(int i = 0; i < G[cur.y].size(); i++)
        {
            next =  G[cur.y][i];
            if(Dist[next.x] > cur.x+ next.y)
            {
                Dist[next.x] = cur.x+ next.y;
                Q.insert(next.x, Dist[next.x]);
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
        Dist = vector<int>(n, inf);
        Dijsktra(start);
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
            //cerr<<a<<" "<<b<<" "<<d<<"\n";
            a-=1;
            b-=1;
            in++;
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
    cerr<<"read: "<<in<<" edges\n";
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