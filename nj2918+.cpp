#include<cstdio>
#include<map>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
using namespace std;
const int maxn=4*300010;
struct Edge{
    int u,v,b,e;
};
map<pii,int> mp;
int n,k;
struct Node{
    vector<pii> edges;
    int query;
}ST[maxn];
FILE *fin, *fout;

struct DSU{
    int fa[maxn],sz[maxn],top,cnt;
    pii stk[maxn];
    void init(){
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<=n;i++) sz[i]=1;
        top=0;
        cnt=n;
    }
    int f(int x){
        while(fa[x]!=x) x=fa[x];
        return x;
    }
    bool add(int u,int v){
        int x=f(u),y=f(v);
        //link x to y
        if(x==y) return false;
        if(sz[x]>sz[y]) swap(x,y);
        cnt--;
        fa[x]=y;
        stk[top++]=pii(x,y);
        sz[y]+=sz[x];
        return true;
    }
    void cut(int tot){//tot:現在的結點有多少邊應在stk中
        while(tot<=top-1){
            int x=stk[top-1].first, y=stk[top-1].second;
            top--;
            cnt++;
            fa[x]=x;
            sz[y]-=sz[x];
        }
    }
}dsu;

void adde(int o,int l,int r,Edge edg)
{
    //printf("l=%d r=%d\n",l,r);
    if(l>r) return;
    int ql=edg.b,qr=edg.e;
    if(ql<=l && r<=qr){
        ST[o].edges.push_back(pii(edg.u,edg.v));
    }
    else{
        int m=l+(r-l)/2;
        if(ql<=m) adde(o*2,l,m,edg);
        if(qr>m) adde(o*2+1,m+1,r,edg);
    }
}
void addq(int o,int l,int r,int q)
{
    //printf("l=%d r=%d\n",l,r);
    if(l>r) return;
    if(q<=l && r<=q) {ST[o].query=1; /*printf("o=%d ST[o].query=%d\n",o,ST[o].query);*/}
    else{
        int m=l+(r-l)/2;
        if(q<=m) addq(o*2,l,m,q);
        if(q>m) addq(o*2+1,m+1,r,q);
    }
}
int tot=0;
void dfs(int o,int l,int r)
{
    if(l>r) return;
    /*printf("edges.size()=%d\n",ST[o].edges.size());*/
    int temp=tot;
    for(int i=0;i<ST[o].edges.size();i++){
        pii u=ST[o].edges[i];
        //printf("%d %d %d %d\n",u.first,u.second,dsu.f(u.first),dsu.f(u.second));
        if(dsu.add(u.first,u.second)){
            tot++;
            //printf("i=%d, add(%d,%d), tot=%d\n",i,u.first,u.second,tot);
        }
    }
    //printf("o=%d, ST[o].query=%d\n",o,ST[o].query);
    if(ST[o].query){
        fprintf(fout,"%d\n",dsu.cnt);
    }
    if(l<r){
        int m=l+(r-l)/2;
        //printf("ql=%d,qr=%d,m=%d:\n",ql,qr,m);
        if(1<=m) dfs(o*2,l,m);
        if(k+1>m) dfs(o*2+1,m+1,r);
    }
    tot=temp;
    dsu.cut(tot);
    //printf("return:l=%d, r=%d\n",l,r);
}
int main()
{
    fin=fopen("connect.in","rb");
    fout=fopen("connect.out","wb");
    fscanf(fin,"%d%d",&n,&k);
    for(int i=1;i<2*k+10;i++) ST[i].query=0;
    for(int clock=1;clock<=k;clock++){
        char op[10];
        fscanf(fin,"%s",op);
        if(op[0]=='?'){
            addq(1,1,k+1,clock);
        }
        else{
            int u,v;
            fscanf(fin,"%d%d",&u,&v);
            if(u>v) swap(u,v); //u<=v
            pii p=pii(u,v);
            if(mp.count(p)){
                //printf("ql=%d qr=%d:\n",mp[pii(u,v)],clock);
                adde(1,1,k+1,Edge{u,v,mp[p],clock});
                mp.erase(p);
            }
            else mp[p]=clock;
        }
    }
    map<pii,int>::iterator it;
    for(it=mp.begin();it!=mp.end();it++){
        //printf("ql=%d qr=%d:\n",it->second,k);
        adde(1,1,k+1,Edge{(it->first).first,(it->first).second,it->second,k+1});
    }
    dsu.init();
    dfs(1,1,k+1);
    fclose(fin);
    fclose(fout);
    //printf("YES\n");
}
