#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

void graph_c::bfs_parentage(int s, vector<pair<int,int>>&P)
{
    vector<bool>visit(V,0);
    queue<int>q;

    q.push(s);
    visit[s]=1;
    P[s]={-1,-1};

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(const auto&edge:adj[u])
        {
            int v=edge.first;
            int edge_id=edge.second;
            if(colors[v]==colors[s] and !visit[v])
            {
                visit[v]=1;
                P[v]=make_pair(u,edge_id);
                // cout<<toString[u]<<"->"<<toString[v]<<" "<<edge_id<<endl;
                q.push(v);
            }
        }
    }
}

void graph_c::path_patrol(int s)
{
    vector<pair<int,int>>parents(V); // pai e aresta
    vector<pair<int,int>>childs(V); // filho e aresta
    vector<int>edges; // arestas a serem visitadas
    vector<bool>visit(E,0); // marca se uma aresta ja foi ou nao visitada
    
    graph_c* Gt=transpose(); // grafo transposto

    for(int u : SCC_components[colors[s]]) // para a componente conexa lista todas suas arestas e adiciona em um vetor para visita-las
        for(const auto&edge:adj[u])
            if(colors[edge.first]==colors[s])
                edges.push_back(edge.second);

    // cout<<" Pais "<<endl;
    bfs_parentage(s,parents); // determina pais e indices de arestas para os vertices
    
    // cout<<" Filhos "<<endl;
    Gt->bfs_parentage(s,childs);

    // agora a logica de fazer o patrulhamento
    int current_vertex=s; // comeca no batalhao
    while(!edges.empty())
    {
        edge=edges.back();
        edges.pop_back();
    }
}

void graph_c::determine_patrols()
{
    cout<<patrols<<endl;
    for(size_t i=0; i<battalions.size(); i++)
        if(battalions[i].second>1)
            path_patrol(battalions[i].first);
}