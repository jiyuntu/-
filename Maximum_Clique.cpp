/* reference:
 * https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm#cite_note-Tomita2003-2
 * http://insilab.org/maxclique/
 */

#include<bits/stdc++.h>
#define maxn 150
using namespace std;
typedef pair<int,int> pii;
char G[maxn][maxn];
int deg[maxn];
vector<int> C[maxn]; //R: sort first
bitset<maxn> Q,QMAX;

bool sort_by_deg(pii x,pii y) {return deg[x.first]==deg[y.first]?x.first<y.first:deg[x.first]>deg[y.first];}
void colorsort(vector<pii> &R)
{
    if(R.empty()) return;
    int C_size=2;
    int min_k = QMAX.count() - Q.count() + 1;
    if(min_k<=0) min_k=1;
    C[1].clear();
    C[1].push_back(R[0].first);
    for(int i=1;i<R.size();i++){
        int j=1;
        for(;j<C_size;j++){
            int flag=0;
            for(int v:C[j]) if(G[R[i].first][R[i].first]=='1' && G[v][v]=='1' && G[v][R[i].first]=='1' && G[R[i].first][v]=='1'){
                flag=1; break;
            }
            if(!flag) break;
        }
        if(j<C_size){
            // add R[i] to C[j]
            C[j].push_back(R[i].first);
        }else{
            // create new C[C_size++]
            C[C_size].clear();
            C[C_size].push_back(R[i].first);
            C_size++;
        }
    }
    R.clear();
    for(int i=1;i<min(min_k,C_size);i++){
        for(int v:C[i]){
            R.push_back(pii(v,0));
        }
    }
    for(int i=min_k;i<C_size;i++){
        for(int v:C[i]){
            R.push_back(pii(v,i));
        }
    }
}
void MaxClique(vector<pii> R)
{
    while(R.size()){
        pii p=R[R.size()-1];
        R.pop_back();
        if(Q.count()+p.second>QMAX.count()){
            Q[p.first]=1;
            vector<pii> RP;
            for(pii v:R) if(G[v.first][p.first]=='1' && G[p.first][v.first]=='1' && G[v.first][v.first]=='1' && G[p.first][p.first]=='1'){
                RP.push_back(pii(v.first,v.second));
            }
            if(RP.size()){
                colorsort(RP);
                MaxClique(RP);
            }else if(Q.count()>QMAX.count()){
                QMAX=Q;
            }
            Q[p.first]=0;
        }else{
            return;
        }
    }
}
int main()
{
    Q.reset(); QMAX.reset();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",G[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) if(G[i][i]=='1' && G[j][j]=='1' && G[i][j]=='1' && G[j][i]=='1'){
            deg[i]++; deg[j]++;
        }
    }
    vector<pii> R;
    for(int i=1;i<=n;i++) R.push_back(pii(i,deg[i]));
    sort(R.begin(),R.end(),sort_by_deg);
    colorsort(R);
    MaxClique(R);
    for(int i=1;i<=n;i++) if(QMAX[i]) printf("%d ",i);
    for(int i=1;i<=n;i++) if(!QMAX[i]) printf("%d ",i);
    printf("\n");
}
