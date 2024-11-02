#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

int main()
{
    int n,m;cin>>n>>m;

    graph_c G(n);

    string u,v;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;
        G.add_edge(u,v);
    }

    G.print();

    return(0);
}