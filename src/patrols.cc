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

                P[v] = {u,edge_id};

                q.push(v);
            }
        }
    }
}

void graph_c::path_patrol(int s)
{
    vector<pair<int,int>>from_battalion(V);
    vector<pair<int,int>>to_battalion(V);
    vector<int>patrol;
    vector<int>edges;
    vector<bool>visit(E,0);
    
    graph_c* Gt=transpose();

    
    for(int u : SCC_components[colors[s]])
        for(const auto&edge:adj[u])
            if(colors[edge.first]==colors[s])
                edges.push_back(edge.second);

    bfs_parentage(s,from_battalion);
    Gt->bfs_parentage(s,to_battalion);

    for(int i:edges)
    {
        if(visit[i])continue;

        int u=edges_list[i].first;
        int v=edges_list[i].second;

        int w=u;
        vector<int>path;
        while(w!=s)
        {
            w=from_battalion[w].first;
            int e = from_battalion[w].second;
            if(e!=-1)visit[e]=1;
            path.push_back(w);
        }
        reverse(path.begin(),path.end());
        path.push_back(u);
        path.push_back(v);
        visit[i]=1;

        w=v;
        while(w!=s)
        {
            int e=to_battalion[w].second;
            w=to_battalion[w].first;
            if(e!=-1)visit[e]=1;
            path.push_back(w);
        }
        for(int j:path)
            patrol.push_back(j);
    }

    for(int i=0;i<((int)patrol.size())-1;i++)
    {
        if(i>0 and patrol[i]==patrol[i-1])continue;

        cout<<toString[patrol[i]]<<" ";
    }
    cout<<endl;
}

void graph_c::determine_patrols()
{
    cout<<patrols<<endl;
    for(size_t i=0; i<battalions.size(); i++)
        if(battalions[i].second>1)
            path_patrol(battalions[i].first);
}