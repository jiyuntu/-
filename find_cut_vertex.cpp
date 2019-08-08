///find all cut vertexes
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=105;
int A[maxn][maxn],pre[maxn],iscut[maxn],dfs_clock,n;
vector<int> G[maxn];

int dfs(int u,int fa)
{
    pre[u]=++dfs_clock;
    int lowu=pre[u];
    int child=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!pre[v]){
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u]) iscut[u]=1;
        }
        else if(pre[v]<pre[u] && v!=fa){
            lowu=min(lowu,pre[v]);
        }
    }
    if(!fa && child==1) iscut[u]=0;
    return lowu;
}
int main()
{
    ios::sync_with_stdio(false);
    while(cin >> n){
        if(!n) break;
        string s;
        getline(cin,s);
        memset(A,0,sizeof(A));
        while(1){
            getline(cin,s);
            stringstream ss(s);
            int x,y;
            ss>>x;
            if(!x) break;
            while(ss>>y){
                A[x][y]=A[y][x]=1;
            }
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
            for(int j=1;j<=n;j++) if(A[i][j] && i!=j)
                G[i].push_back(j);
        }
        memset(pre,0,sizeof(pre));
        memset(iscut,0,sizeof(iscut));
        dfs_clock=0;
        dfs(1,0);
        int ans=0;
        for(int i=1;i<=n;i++) if(iscut[i]) ans++;
        cout << ans << "\n";
    }
}
