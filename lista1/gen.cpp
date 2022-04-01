#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;

    cin>>n>>m;

    srand(time(0));
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i < m; i++)
    {
        int a, b;
        a = rand() % n;
        b = rand() % n;
        while(a == b)b = rand() % n;
        cout<<a<<" "<<b<<"\n";
    }




    return 0;
}