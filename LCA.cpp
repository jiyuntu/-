#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=30005;
int r[maxn];
vector<int> G[maxn];

struct LCA{
    int depth[maxn],anc[maxn][20];
    int root;

    void init() {depth[root]=0; anc[root][0]=root;}
    void dfs(int u,int p){
        for(int v:G[u]){
            if(v!=p){
                depth[v]=depth[u]+1;
                anc[v][0]=u;
                int m=2;
                for(int j=1;m<=depth[v];j++, m<<=1){
                    anc[v][j]=anc[anc[v][j-1]][j-1];
                }
                dfs(v,u);
            }
        }
    }
    int Query(int a,int b){
        if(depth[a]<depth[b]) swap(a,b); //depth[a]>=depth[b]
        int diff=depth[a]-depth[b];
        for(int i=0;diff>>i;i++){
            if((diff>>i)&1){
                a=anc[a][i];
            }
        }
        if(a==b) return a;
        int i=(int)log2(depth[a]);
        for(;i>=0;i--){
            if(anc[a][i]){
                if(anc[a][i]!=anc[b][i]) {a=anc[a][i]; b=anc[b][i];}
            }
        }
        return anc[a][0];
    }
}lca;
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        int x;
        while(scanf("%d",&x)==1){
            if(!x) break;
            r[x]=1;
            G[i].push_back(x);
        }
    }
    for(int i=1;i<=n;i++) if(!r[i]) {lca.root=i; break;}
    lca.dfs(lca.root,lca.root);
    while(q--){
        int a,b;
        scanf("%d%d",&a,&b);
        int lcaq=lca.Query(a,b);
        int grade=lca.depth[a]+lca.depth[b]-2*lca.depth[lcaq];
        printf("%d %d\n",lcaq,grade);
    }
}
