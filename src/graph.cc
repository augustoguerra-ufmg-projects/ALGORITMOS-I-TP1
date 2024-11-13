//=================================================================
// arquivo  : graph.cc
// descricao    : implementacao dos metodos do grafo
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241113
//=================================================================

#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

// construtor
graph_c::graph_c(int _V):V(_V),E(0),patrols(0)
{
    adj.resize(V);
    capital_distances.resize(V);
    colors.resize(V);
}

// metodo   : add_edge
// descricao    : simplesmente processa as strings e mapeia para inteiros
// adcionando uma aresta no grafo
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

// funcao   : transpose
// descricao    : retorna um grafo transposto preservando todos os indices e mapeamento do grafo original
// dominio  : grafo direcionado
// imagem   : grafo direcionado transposto
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

// metodo   : print
// descricao    : imprime o grafo de forma visual apenas para fins de debbuging
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