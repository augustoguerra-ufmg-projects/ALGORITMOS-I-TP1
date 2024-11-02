#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

void graph_c::add_edge(string& u, string& v)
{
    this->adj[u].push_back(v);
    this->E++;
}

void graph_c::print()
{
    for(unordered_map<string,list<string>>::iterator i=adj.begin();i!=adj.end();i++)
    {
        cout<<i->first<<": ";
        for(list<string>::iterator j=i->second.begin();j != i->second.end();j++)
            cout<<*j<<"\t";
            
        cout<<"\n";
    }
}