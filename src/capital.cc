//=================================================================
// arquivo  : capital.cc
// descricao    : implementacao do algoritmo para determinar capital
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241113
//=================================================================

#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

// funcao   : bfs
// descricao    : avalia a partir de uma bfs a excentricidade de um vertice
// dominio  : grafo direcionado e um vertice fonte
// imagem   : excentricidade do vertice fonte
int graph_c::bfs(int s, vector<int>&distances)
{
    vector<bool>visit(V,0);
    queue<int>q;

    distances[s]=0;
    visit[s]=1;
    q.push(s);

    while(!q.empty())
    {
        int u=q.front();
        q.pop();

        for(auto edge : adj[u])
        {
            if(!visit[edge.first])
            {
                visit[edge.first]=1;
                distances[edge.first]=distances[u]+1;
                q.push(edge.first);
            }
        }
    }

    int sum=0;
    for(int u=0;u<V;u++)
    {
        if(distances[u]==INF)
            return(INF);

        sum+=distances[u];
    }
    return(sum);
}

// metodo   : determine_capital
// descricao    : determina a capital do grafo direcionado pelo criterio de excentricidade
void graph_c::determine_capital()
{
    int mindist=INF;
    
    for(int u=0;u<V;u++)
    {
        vector<int>distances(V,INF);
        int dist=bfs(u,distances);

        if(dist<mindist)
        {
            mindist=dist;
            capital=u;
            capital_distances=distances;
        }
    }
}