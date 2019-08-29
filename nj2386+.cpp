#include<cstdio>
#include<vector>
#include<cstring>
#define pii pair<int,int>
using namespace std;
typedef long long ll;
char s[100005];
vector<int> G[100005];
int sz[100005],cal[100005];
ll ans,up[100005];
int n;

int getsize(int root,int p)
{
    int temp=1;
    for(int v:G[root]){
        if(v!=p && !cal[v]){
            temp+=getsize(v,root);
        }
    }
    return sz[root]=temp;
}
pii getcentroid(int u,int p,int szr)
{
    int mx=szr-sz[u],id=-1;
    for(int v:G[u]){
        if(v!=p && !cal[v]){
            if(sz[v]>mx) {mx=sz[v]; id=v;}
        }
    }
    if(id==-1) return pii(mx,u);
    pii v=getcentroid(id,u,szr);
    return mx<v.first?pii(mx,u):pii(v.first,v.second);
}
void getup(int u,int p,int left,int right)
{
    /*printf("u=%d, p=%d, top=%d\n",u,p,top);
    for(int i=0;i<top;i++) putchar(stk[i]);
    putchar('\n');*/
    if(cal[u]) return;
    //int op;
    if(s[u]=='('){
        if(right>0) right--;
        else left++;
        if(right==0) up[left]++;
    }
    else right++;
    for(int v:G[u]){
        if(v!=p && !cal[v]){
            getup(v,u,left,right);
        }
    }
}
ll temp[100005];
int getup2(int u,int p,int left,int right)
{
    if(cal[u]) return 0;
    int mx=0;
    if(s[u]=='('){
        if(right>0) right--;
        else left++;
        if(right==0){
            temp[left]++;
            mx=max(mx,left);
        }
    }
    else right++;
    for(int v:G[u]){
        if(v!=p && !cal[v]){
            mx=max(mx,getup2(v,u,left,right));
        }
    }
    return mx;
}
void godown(int u,int p,int left,int right)
{
    if(cal[u]) return;
    if(s[u]==')'){
        if(left>0) left--;
        else right++;
        if(left==0){
            ans+=up[right]-temp[right];
        }
    }
    else left++;
    for(int v:G[u]){
        if(v!=p && !cal[v]){
            godown(v,u,left,right);
        }
    }
}
void solve(int u)
{
    getsize(u,-1);
    int c=getcentroid(u,-1,sz[u]).second;
    //printf("c=%d\n",c);
    cal[c]=1;
    for(int i=0;i<=sz[u];i++) up[i]=0;
    for(int v:G[c]){
        if(!cal[v]){
            if(s[c]=='(') getup(v,c,1,0);
            else getup(v,c,0,0);
        }
    }
    /*printf("up=:\n");
    for(int i=0;i<=n;i++) printf("%d ",up[i]);
    printf("\n");*/
    if(s[c]=='(') up[1]++;
    else ans+=up[1];
    //printf("ans=%I64d\n",ans);
    for(int v:G[c]){
        if(!cal[v]){
            //printf("v=%d\n",v);
            int ed;
            if(s[c]=='(') ed=getup2(v,c,1,0);
            else ed=getup2(v,c,0,0);
            /*for(int i=0;i<=n;i++) printf("%d ",temp[i]);
            printf("\n");*/
            if(s[c]==')') godown(v,c,0,1);
            else godown(v,c,0,0);
            //printf("ans=%lld\n",ans);
            for(int i=0;i<=ed;i++) temp[i]=0;
        }
    }
    for(int v:G[c]){
        if(!cal[v]) solve(v);
    }
}
int main()
{
    //freopen("input3.txt","r",stdin);
    scanf("%d%s",&n,s);
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    ans=0;
    memset(temp,0,sizeof(temp));
    solve(0);
    printf("%lld\n",ans);
}
/*
10
(()))(()()
1 2
1 5
1 3
1 4
4 6
6 7
7 8
8 9
8 10
ans:10

10
))(((()())
1 2
1 4
2 3
4 6
6 7
6 10
7 8
2 5
5 9
ans:13

10
()()(((())
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
ans:4

15
()()))(()()()((
6 1
1 2
1 4
4 9
4 5
5 8
8 7
7 10
10 3
3 11
10 12
12 13
8 14
2 15
*/

