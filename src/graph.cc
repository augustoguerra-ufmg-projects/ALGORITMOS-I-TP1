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

// funcao   : transpose
// descricao    : computa o grafo transposto do grafo G
// dominio  : grafo G
// imagem : grafo transposto Gt
graph_c* graph_c::transpose()
{
    graph_c* Gt=new graph_c(this->V);
    for(unordered_map<string,list<string>>::iterator i=this->adj.begin(); i!=this->adj.end();i++)
    {
        string u=i->first;
        for(list<string>::iterator v=i->second.begin();v!=i->second.end();v++)
        {
            Gt->add_edge(*v,u);
        }
    }
    return(Gt);
}

// metodo   : dfs
// descricao : metodo utilizado no algoritmo de kosaraju para fazer uma visita na profundidade do grafo empilhando vertices
// que sao encerrados para a chamadas do kosaraju durante a segunda dfs que determina de fato as componentes conexas do grafo direcionado
void graph_c::dfs(string&s, unordered_map<string,bool>&visit, stack<string>&S)
{
    visit[s]=1;

    for(list<string>::iterator u=adj[s].begin(); u!=adj[s].end(); u++)
        if(!visit[*u])
            dfs(*u,visit,S);

    S.push(s);
}

// metodo   : dfs_SCC
// descricao    : metodo utilizado no algoritmo de kosaraju para
// determinar as componentes fortemente conexas a partir do grafo transposto
// atribui coloracao (um numero inteiro) para os vertices de uma componente
void graph_c::dfs_SCC(string&s, unordered_map<string,bool>&visit, int color, graph_c* G, int& cardinality)
{
    cardinality++;
    visit[s]=1;
    G->colors[s]=color;

    for(list<string>::iterator u=this->adj[s].begin(); u!=this->adj[s].end(); u++)
        if(!visit[*u])
            dfs_SCC(*u,visit,color,G,cardinality);
}

// metodo   : determine_battalions
// descricao :  implementa o algoritmo de kosaraju para determiniar
// componentes conexas do grafo
void graph_c::determine_battalions()
{
    stack<string>S;
    unordered_map<string,bool>visit;
    graph_c* Gt=transpose();

    dfs(this->capital, visit, S);

    visit.clear();
    
    int color=0;
    while(!S.empty())
    {
        string u=S.top();
        S.pop();

        if(!visit[u])
        {
            int cardinality=0;
            Gt->dfs_SCC(u,visit,color,this,cardinality);
            this->battalions.push_back(make_pair(u,cardinality));
            
            if(cardinality>1)
                this->patrols++;

            color++;
        }
    }

    delete(Gt);
}

// metodo   : list_battalions
// descricao    : conta quantos batolhoes existem e os lista com excecao da capital
void graph_c::list_battalions()
{
    cout<<this->battalions.size()-1<<endl;
    for(size_t i=1; i<battalions.size(); i++)
        cout<<this->battalions[i].first<<endl;
}

void graph_c::determine_patrols()
{
    cout<<this->patrols<<endl;
}