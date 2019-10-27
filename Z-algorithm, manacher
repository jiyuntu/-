///Z-algorithm, manacher
///problem source: https://codeforces.com/gym/101981
#include<cstdio>
#include<stdint.h>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1000100;
char s[maxn],t[maxn];
char M[2*maxn],z[2*maxn];
int len[2*maxn],zv[2*maxn],sv[maxn],prefix[maxn];

void manacher()
{
    M[0]='$';
    M[1]='#';
    int l=strlen(s),ml=2;
    for(int j=0;j<l;ml+=2,j++){//s[i]=M[i*2+2];
        M[ml]=s[j];
        M[ml+1]='#';
    }
    M[ml]='\0';
    len[0]=1;
    int po=0,p=0;
    for(int i=1;i<ml;i++){
        if(i<=p){
            int j=po*2-i;
            if(len[j]<p-i+1) len[i]=len[j];
            else{
                int k=p+1;
                while(k<ml && M[k]==M[2*i-k]) k++;
                len[i]=k-i;
            }
        }else{
            int j=i+1;
            while(j<ml && M[j]==M[2*i-j]) j++;
            len[i]=j-i;
        }
        if(i+len[i]-1>=p){
            p=i+len[i]-1;
            po=i;
        }
    }
}
void Z()
{
    int l=strlen(t),l2=strlen(s);
    for(int i=0;i<l;i++) z[i]=t[i];
    z[l]='#';
    for(int i=l+1,j=l2-1;i<=l+l2;i++,j--) z[i]=s[j];
    z[l+l2+1]='\0';
    int zl=l+l2+1;
    zv[0] = 0;
    int bst = 0;
    for(int i = 1; i<zl ; i++) {
        if(zv[bst] + bst < i) zv[i] = 0;
        else zv[i] = min(zv[bst]+bst-i, zv[i-bst]);
        while(z[zv[i]] == z[i+zv[i]]) zv[i]++;
        if(zv[i] + i > zv[bst] + bst) bst = i;
    }
    for(int i=zl-1,start=0;i>l;i--,start++){
        sv[start]=zv[i];
    }
    prefix[0]=sv[0];
    for(int i=1;i<l2;i++){
        prefix[i]=sv[i]+prefix[i-1];
    }
}
int pre(int idx) {return idx<0?0:prefix[idx];}
int32_t main()
{
    scanf("%s%s",s,t);
    manacher();
    int ml=strlen(M);
    Z();
    int ans=0;
    for(int i=2;i<ml-1;i++){
        if(len[i]-1>0){
            int k,start,l;
            if(M[i]=='#') {k=i-1; start=(k-2)/2; l=(len[i]-1)/2;}
            else {k=i; start=(k-2)/2; l=len[i]/2;}
            ans+=pre(start-1)-pre(start-l-1);
        }
    }
    printf("%I64d\n",ans);
}
/*
ab
a
*/

