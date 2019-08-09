///maxflow
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=105;
const int INF=2147483647;
struct Edge{
    int from,to,cap,flow;
};
vector<Edge> edges;
vector<int> G[105];
int cur[maxn],dis[maxn];

void addedge(int from,int to,int cap)
{
    edges.push_back((Edge){from,to,cap,0});
    edges.push_back((Edge){to,from,0,0});
    int sz=edges.size();
    G[from].push_back(sz-2);
    G[to].push_back(sz-1);
}
bool bfs(int s,int t)
{
    memset(dis,-1,sizeof(dis));
    queue<int> q;
    q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=0;i<G[u].size();i++){
            Edge& e=edges[G[u][i]]; //為啥要&?
            if(dis[e.to]==-1 && e.cap>e.flow){
                dis[e.to]=dis[u]+1;
                q.push(e.to);
            }
        }
    }
    return (dis[t]>=0);
}
int dfs(int s,int t,int a)
{
    if(s==t || a==0) return a;
    int flow=0,f;
    for(int& i=cur[s];i<G[s].size();i++){//用&可以直接改值!
        Edge& e=edges[G[s][i]];
        if(dis[s]+1==dis[e.to] && (f=dfs(e.to,t,min(a,e.cap-e.flow)))>0){
            e.flow+=f;
            edges[G[s][i]^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int maxflow(int s,int t)
{
    int flow=0;
    while(bfs(s,t)){
        memset(cur,0,sizeof(cur));
        flow+=dfs(s,t,INF);
    }
    return flow;
}
int main()
{
    int n,kase=0;
    while(scanf("%d",&n)==1){
        if(!n) break;
        int s,t,m;
        scanf("%d%d%d",&s,&t,&m);
        edges.clear();
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            addedge(u,v,c);
            addedge(v,u,c);
        }
        printf("Network %d\n",++kase);
        printf("The bandwidth is %d.\n\n",maxflow(s,t));
    }
}
