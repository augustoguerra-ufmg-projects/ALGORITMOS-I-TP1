#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

void graph_c::dfs(int s,vector<bool>&visit, stack<int>&S)
{
    visit[s]=1;
    for(auto edge:adj[s])
        if(!visit[edge.first])
            dfs(edge.first,visit,S);
    
    S.push(s);
}

void graph_c::dfs_SCC(int s,vector<bool>&visit, int color, graph_c* G)
{
    visit[s]=1;
    G->colors[s]=color;
    G->SCC_components[color].push_back(s);

    for(auto edge:adj[s])
        if(!visit[edge.first])
            dfs_SCC(edge.first, visit, color, G);
}

void graph_c::kosaraju_SCC()
{
    stack<int>S;
    vector<bool>visit(V,0);
    graph_c* Gt=transpose();

    dfs(capital,visit,S);

    fill(visit.begin(),visit.end(),0);

    int color=0;
    while(!S.empty())
    {
        int u=S.top();
        S.pop();

        if(!visit[u])
        {
            SCC_components.push_back({});
            Gt->dfs_SCC(u,visit,color,this);
            color++;
        }
    }
    
    delete(Gt);
}

int graph_c::bfs_criteria(int s)
{
    vector<int>distances(V,INF);
    vector<bool>visit(V,0);
    queue<int>q;

    distances[s]=0;
    visit[s]=1;
    q.push(s);

    while(!q.empty())
    {
        int u=q.front();
        q.pop();

        for(auto&edge:adj[u])
        {
            int v=edge.first;
            if(!visit[v] and colors[v]==colors[s])
            {
                visit[v]=1;
                distances[v]=distances[u]+1;
                q.push(v);
            }
        }
    }

    int sum=0;
    for(int u:SCC_components[colors[s]])
        if(distances[u]!=INF)
            sum+=distances[u];

    return(sum);
}

void graph_c::determine_battalions()
{
    kosaraju_SCC();

    for(size_t i=0;i<SCC_components.size();i++)
    {
        vector<int>&vertices=SCC_components[i];

        int battalion;
        int mindist=INF;
        vector<int>candidates;

        for(int u:vertices)
        {
            int dist=capital_distances[u];
            if(dist<mindist)
            {
                mindist=dist;
                candidates.clear();
                candidates.push_back(u);
            }
            else if(dist==mindist)
            {
                candidates.push_back(u);
            }
        }

        if(candidates.size()>1)
        {
            int min=INF;
            int best_candidate;

            for(int candidate : candidates)
            {
                int sum = bfs_criteria(candidate);
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
            battalion=candidates[0];
        }
        battalions.push_back(make_pair(battalion,vertices.size()));
        if(vertices.size()>1)
            patrols++;
    }
}

void graph_c::list_battalions()
{
    cout<<battalions.size()-1<<endl;
    for(const auto& battalion: battalions)
        if(battalion.first != capital)
            cout<<toString[battalion.first]<<endl;
}