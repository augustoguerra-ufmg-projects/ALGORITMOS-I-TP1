#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

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
void graph_c::dfs_SCC(string&s, unordered_map<string,bool>&visit, int color, graph_c* G)
{
    visit[s]=1;
    G->colors[s]=color;
    G->SCC_components[color].push_back(s);

    for(list<string>::iterator u=this->adj[s].begin(); u!=this->adj[s].end(); u++)
        if(!visit[*u])
            dfs_SCC(*u,visit,color,G);
}

// metodo   : kosaraju_SCC
// descricao :  implementa o algoritmo de kosaraju para determiniar
// componentes conexas do grafo
void graph_c::kosaraju_SCC()
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
            Gt->dfs_SCC(u,visit,color,this);
            color++;
        }
    }
    delete(Gt);
}

// funcao   : bfs_criteria()
// descricao    : retorna a soma das distancias de um vertice ate 
// todos os outros da mesma componente conexa
int graph_c::bfs_criteria(string&s)
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
        string u=q.front();
        q.pop();

        for(list<string>::iterator v=adj[u].begin(); v!= adj[u].end();v++)
        {
            if(!visit[*v] and colors[*v]==colors[s])
            {
                visit[*v]=1;
                distances[*v]=distances[u]+1;
                q.push(*v);
            }
        }
    }

    int sum=0;
    for(unordered_map<string,int>::iterator i=distances.begin(); i!=distances.end(); i++)
    {
        if(colors[s]==colors[i->first] and i->second != INF)
        {
            sum+=i->second;
        }
    }
    return(sum);
}

// metodo   : determine_battalions
// descricao    : faz chamada de kosaraju para dividir o grafo em
// componentes fortemente conexas e depois decide batalhoes 
// secundarios para cada uma delas com criterios de desempate
void graph_c::determine_battalions()
{
    kosaraju_SCC();

    for(unordered_map<int,list<string>>::iterator i=this->SCC_components.begin(); i!=this->SCC_components.end(); i++)
    {
        list<string>&vertices=i->second;
        
        string battalion;
        int mindist=INF;
        vector<string>candidates;

        for(list<string>::iterator j=vertices.begin(); j!=vertices.end(); j++)
        {
            string u=*j;
            int dist=capital_distances[u];

            if(dist<mindist)
            {
                mindist=dist;
                candidates.clear();
                candidates.push_back(u);
            }
            else if(dist == mindist)
            {
                candidates.push_back(u);
            }
        }

        if(candidates.size()>1)// houve empate
        {
            int min=INF;
            string best_candidate;

            for(vector<string>::iterator c=candidates.begin(); c!=candidates.end(); c++)
            {
                string candidate=*c;
                int sum=bfs_criteria(candidate);

                if(sum<min)
                {
                    min=sum;
                    best_candidate=candidate;
                }
            }
            battalion=best_candidate;
        }
        else
        {
            battalion=candidates.front();
        }
        this->battalions.push_back(make_pair(battalion,vertices.size()));

        if(vertices.size()>1)
            this->patrols++;
    }
}

// metodo   : list_battalions
// descricao    : conta quantos batolhoes existem e os lista com excecao da capital
void graph_c::list_battalions()
{
    cout<<this->battalions.size()-1<<endl;
    for(size_t i=0; i<battalions.size(); i++)
        if(this->battalions[i].first!=this->capital)
            cout<<this->battalions[i].first<<endl;
}