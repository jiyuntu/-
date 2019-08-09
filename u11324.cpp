///SCC  strongly connected component 有向圖的強連通分量
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;
const int maxn=1005;
vector<int> G[maxn],scc[maxn];
int pre[maxn],sccno[maxn],dfs_clock,scc_cnt,n;
int dis[maxn];
stack<int> S;

int dfs(int u)
{
    pre[u]=++dfs_clock;
    S.push(u);
    int lowlinku=pre[u];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!pre[v]){
            int lowlinkv=dfs(v);
            lowlinku=min(lowlinkv,lowlinku);
        }
        else if(!sccno[v]) lowlinku=min(lowlinku,pre[v]);
    }
    if(lowlinku==pre[u]){
        scc_cnt++;
        scc[scc_cnt].clear();
        while(1){
            int x=S.top(); S.pop();
            sccno[x]=scc_cnt;
            scc[scc_cnt].push_back(x);
            if(x==u) break;
        }
    }
    return lowlinku;
}
void bfs(int root)
{
    int inq[maxn];
    memset(inq,0,sizeof(inq));
    queue<int> q;
    q.push(root);
    inq[root]=1;
    dis[root]=scc[root].size();
    while(!q.empty()){
        int r=q.front(); q.pop();
        inq[r]=0;
        for(int i=0;i<scc[r].size();i++){
            int u=scc[r][i];
            for(int j=0;j<G[u].size();j++){
                int v=G[u][j];
                if(sccno[u]!=sccno[v] && dis[sccno[v]]<dis[sccno[u]]+scc[sccno[v]].size()){
                    dis[sccno[v]]=dis[sccno[u]]+scc[sccno[v]].size();
                    if(!inq[sccno[v]]) {q.push(sccno[v]); inq[sccno[v]]=1;}
                }
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
        }
        memset(pre,0,sizeof(pre));
        memset(sccno,0,sizeof(sccno));
        dfs_clock=scc_cnt=0;
        for(int i=1;i<=n;i++) if(!pre[i])
            dfs(i);
        /*for(int i=1;i<=n;i++) printf("%d ",sccno[i]);
        printf("\n");*/
        int mx=0;
        for(int i=1;i<=n;i++){
            memset(dis,0,sizeof(dis));
            bfs(i);
            for(int i=1;i<=scc_cnt;i++) mx=max(mx,dis[i]);
        }
        printf("%d\n",mx);
    }
}
/*
1
12 17
1 2
2 3
2 4
2 5
3 6
6 3
5 2
5 6
5 7
6 8
7 8
8 11
11 12
12 10
7 10
10 9
9 7
*/
