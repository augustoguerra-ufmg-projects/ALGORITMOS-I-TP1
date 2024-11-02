//---------------------------------------------------------------------------------------------------
// arquivo :    graph.cc
// descricao :  implementacao de funcoes e metodos do grafo direcionado para o tp1 de Algoritmos I
// autor :  augusto guerra de lima augustoguerra@dcc.ufmg.br
// historico :  20241102 arquivo criado
//---------------------------------------------------------------------------------------------------

#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

const int INF = 0x3f3f3f3f;

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

// funcao : bfs
// descricao :  atraves de uma busca em largura no grafo direcionado a partir de um vertice fonte s computa a 
// excentricidade do vertice s i.e. a soma de todas as distancias a todos os vertices
// esse metodo e essencial para determinar qual cidade e a capital
// dominio :    string s rotulo de um vertice encapsulado na classe graph_c
// imagem   : excentricidade do vertice
int graph_c::bfs(string s)
{
    unordered_map<string,int>distances;
    unordered_map<string,bool>visit;
    queue<string>q;

    for(unordered_map<string,list<string>>::iterator i=adj.begin(); i!=adj.end(); i++)
    {
        distances[i->first]=INF;
        visit[i->first]=0;
    }

    distances[s]=0;
    visit[s]=1;
    q.push(s);

    while(!q.empty())
    {
        string st=q.front();
        q.pop();

        for(string& e : this->adj[st])
        {
            if(!visit[e])
            {
                visit[e]=1;
                distances[e]=distances[st]+1;
                q.push(e);
            }
        }
    }

    int sum=0;
    for(unordered_map<string,int>::iterator i=distances.begin();i!=distances.end();i++)
    {
        if(i->second==INF)
            return(INF);

        sum+=i->second;
    }

    return(sum);
}

// metodo   : determine_capital
// descricao    : atraves de multiplas bucas em largura determina qual vertice sera definido como capital
void graph_c::determine_capital()
{
    int mindist=INF;

    for(unordered_map<string,list<string>>::iterator i=this->adj.begin(); i!=this->adj.end(); i++)
    {
        int dist = this->bfs(i->first);
        
        if(dist<mindist)
        {
            mindist=dist;
            this->capital = i->first;
        }
    }
}