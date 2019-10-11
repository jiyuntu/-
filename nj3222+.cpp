//Aliens
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
ll a[200005],dp[200005],shift[200005]/*,cur[200005]*/;
int bit[40],n;
vector<int> trans[200005];

void get(ll p)
{
    dp[0]=a[0]+p;
    shift[0]=1;
    //cur[0]=a[0];
    for(int i=1;i<n;i++){
        dp[i]=dp[i-1]+a[i]+p;
        shift[i]=shift[i-1]+1;
        ll now=0;
        for(int j:trans[i]){
            now=now|a[j];
            if(j>0){
                ll val=dp[j-1]+now+p;
                if(val>dp[i]){
                    dp[i]=val;
                    shift[i]=shift[j-1]+1;
                    //cur[i]=now;
                }else if(val==dp[i]){
                    shift[i]=min(shift[i],shift[j-1]+1);
                    //cur[i]=now;
                }
            }
            /*ll temp=now|cur[j];
            ll val=dp[j]+temp-cur[j];
            if(val>dp[i]){
                dp[i]=val;
                shift[i]=shift[j];
                cur[i]=temp;
            }else if(val==dp[i] && shift[j]<shift[i]){
                shift[i]=shift[j];
                cur[i]=temp;
            }*/
        }
        if(now+p>=dp[i]){
            dp[i]=now+p;
            shift[i]=1;
        }
    }
}
int main()
{
    ll k;
    scanf("%d%lld",&n,&k);
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    memset(bit,-1,sizeof(bit));
    for(int i=0;i<n;i++){
        ll m=1;
        int time=0;
        while(m<=a[i]){
            if(m&a[i]) bit[time]=i;
            time++; m<<=1;
        }
        for(int j=0;j<32;j++) if(bit[j]>=0) trans[i].push_back(bit[j]);
        sort(trans[i].begin(),trans[i].end(),greater<int>());
        auto it=unique(trans[i].begin(),trans[i].end());
        trans[i].resize(distance(trans[i].begin(),it));
    }
    /*for(int i=0;i<n;i++){
        for(int j:trans[i]){
            printf("%d ",j);
        }
        printf("\n");
    }*/
    //engrave this code in your mind!!!you won't want to get 9 WA's for an ALIEN next time!!!
    ll l=-4294967296ll,r=0,p;
    while(l<r){
        ll p=r+(l-r)/2;
        get(p);
        if(shift[n-1]>k) r=p-1;
        else l=p;
    }
    get(l);
    printf("%lld\n",dp[n-1]-l*k);
    /*int c=0;
    while(r-l>=3){
        p=l+(r-l)/2;
        get(p);
        //printf("p=%lld dp=%lld shift=%lld\n",p,dp[n-1],shift[n-1]);
        if(shift[n-1]==k) {c=1; break;}
        if(shift[n-1]<k) l=p+1;
        else r=p;
    }
    if(c) printf("%lld\n",dp[n-1]-p*k);
    else{
        ll ans;
        for(;l<=r;l++){
            get(l);
            if(shift[n-1]==k) {c=1; break;}
            if(shift[n-1]<k) ans=dp[n-1]-l*k;
        }
        //printf("p=%lld dp=%lld shift=%lld\n",p,dp[n-1],shift[n-1]);
        if(c) printf("%lld\n",dp[n-1]-l*k);
        else printf("%lld\n",ans);
    }*/
}
