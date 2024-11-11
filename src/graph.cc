//---------------------------------------------------------------------------------------------------
// arquivo :    graph.cc
// descricao :  implementacao de funcoes e metodos do grafo direcionado para o tp1 de Algoritmos I
// autor :  augusto guerra de lima augustoguerra@dcc.ufmg.br
// historico :  20241102 arquivo criado
//---------------------------------------------------------------------------------------------------

#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

// metodo : add_edge
// descricao :  adiciona uma aresta direcionada de u para v no grafo direcionado
void graph_c::add_edge(string& u, string& v)
{
    if(this->adj.find(v)==this->adj.end())
        this->adj[v]=list<string>();

    this->adj[u].push_back(v);
    this->E++;
}

// metodo : print
// descricao : imprime as listas de adjacencia para cada vertice do grafo direcionado
void graph_c::print()
{
    for(unordered_map<string,list<string>>::iterator i=this->adj.begin();i!=this->adj.end();i++)
    {
        cout<<i->first<<": ";
        for(list<string>::iterator j=i->second.begin();j != i->second.end();j++)
            cout<<*j<<"\t";
            
        cout<<"\n";
    }
}