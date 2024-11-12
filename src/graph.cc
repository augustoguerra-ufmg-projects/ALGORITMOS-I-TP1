#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

graph_c::graph_c(int _V):V(_V),E(0),patrols(0)
{
    adj.resize(V);
    capital_distances.resize(V);
    colors.resize(V);
}

void graph_c::add_edge(string&u,string&v)
{
    if(toInt.find(u)==toInt.end())
    {
        int id=static_cast<int>(toInt.size());
        toInt[u]=id;
        toString[id]=u;
    }
    if(toInt.find(v)==toInt.end())
    {
        int id=static_cast<int>(toInt.size());
        toInt[v]=id;
        toString[id]=v;
    }
    int u_id=toInt[u];
    int v_id=toInt[v];
    adj[u_id].emplace_back(v_id,E);
    edges_list.emplace_back(u_id,v_id);
    E++;
}

graph_c* graph_c::transpose()
{
    graph_c* Gt=new graph_c(V);

    for(int u=0;u<V;u++)
        for(auto& edge:adj[u])
            {
                Gt->adj[edge.first].emplace_back(u,edge.second);
            }
    Gt->toInt=toInt;
    Gt->toString=toString;
    Gt->colors=colors;
    Gt->V=V;
    Gt->E=E;

    for(const auto&edge:edges_list)
        Gt->edges_list.emplace_back(edge.second,edge.first);

    return(Gt);
}

void graph_c::print()
{
    for(int u=0;u<V;u++)
    {
        cout<<u<<" "<<toString[u]<<":";
        for(auto edge : adj[u])
        {
            cout << "(" <<edge.first<<" "<<toString[edge.first] << ", " << edge.second << ") ";
        }
        cout<<endl;
    }
}