///suffix array
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxl=1000000+5;
char s[maxl];
int sa[maxl],c[maxl],x[maxl],y[maxl];

void build_suffix_array(int m){
    int l=strlen(s);
    for(int i=0;i<m;i++) c[i]=0;
    for(int i=0;i<l;i++) c[x[i]=s[i]-'0']++;
    for(int i=1;i<m;i++) c[i]+=c[i-1];
    for(int i=l-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1;k<=l;k<<=1){
        int p=0;
        for(int i=l-k;i<l;i++) y[p++]=i;
        for(int i=0;i<l;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(int i=0;i<m;i++) c[i]=0;
        for(int i=0;i<l;i++) c[x[y[i]]]++;
        for(int i=1;i<m;i++) c[i]+=c[i-1];
        for(int i=l-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);//y of no use
        p=1; x[sa[0]]=0;
        for(int i=1;i<l;i++){
            if(y[sa[i-1]]==y[sa[i]]){
                if(sa[i]+k<l && sa[i-1]+k<l){
                    if(y[sa[i-1]+k]==y[sa[i]+k]) x[sa[i]]=p-1;
                    else x[sa[i]]=p++;
                }
                else if(sa[i]+k>=l && sa[i-1]+k>=l) x[sa[i]]=p-1;
                else x[sa[i]]=p++;
            }
            else x[sa[i]]=p++;
            //x[sa[i]]= (y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k])?p-1:p++;
        }
        if(p>=l) break;
        m=p;
    }
}
int main()
{
    scanf("%s",s);//c from 0 to 9
    build_suffix_array(10);
    for(int i=0;i<l;i++) printf("%d ",sa[i]);
    printf("\n");
}
