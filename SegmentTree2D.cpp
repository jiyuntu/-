#include <bits/stdc++.h>
using namespace std;
const int maxn=500+5;

struct SegmentTree2D{
	int mx[4*maxn][4*maxn],mn[4*maxn][4*maxn],a[maxn][maxn];
	int xo,isleaf,x1,y1,x2,y2,x,y,v,vmax,vmin,n,m,cur;

	void init(int a,int b){
		n=a;
		m=b;
	}

	void build1D(int o,int l,int r)
	{
		if(l==r){
			if(isleaf) mx[xo][o]=mn[xo][o]=a[cur][l];
			else{
				mx[xo][o]=max(mx[xo*2][o],mx[xo*2+1][o]);
				mn[xo][o]=min(mn[xo*2][o],mn[xo*2+1][o]);
			}
		}else{
			int mid=l+(r-l)/2;
			build1D(o*2,l,mid);
			build1D(o*2+1,mid+1,r);
			mx[xo][o]=max(mx[xo][o*2],mx[xo][o*2+1]);
			mn[xo][o]=min(mn[xo][o*2],mn[xo][o*2+1]);
		}
	}
	void build2D(int o,int l,int r)
	{
		if(l==r){
			xo=o;
			cur=l;
			isleaf=1;
			build1D(1,1,m);
		}else{
			int mid=l+(r-l)/2;
			build2D(o*2,l,mid);
			build2D(o*2+1,mid+1,r);
			xo=o;
			isleaf=0;
			build1D(1,1,m);
		}
	}
	void build()
	{
		build2D(1,1,n);
	}

	void query1D(int o,int l,int r)
	{
		if(y1<=l && r<=y2){
			vmax=max(mx[xo][o],vmax);
			vmin=min(mn[xo][o],vmin);
		}else{
			int mid=l+(r-l)/2;
			if(y1<=mid) query1D(o*2,l,mid);
			if(y2>mid) query1D(o*2+1,mid+1,r);
		}
	}
	void query2D(int o,int l,int r)
	{
		if(x1<=l && r<=x2){
			xo=o;
			query1D(1,1,m);
		}else{
			int mid=l+(r-l)/2;
			if(x1<=mid) query2D(o*2,l,mid);
			if(x2>mid) query2D(o*2+1,mid+1,r);
		}
	}
	void query(int a,int b,int c,int d){ //query: x1,y1,x2,y2
		x1=a, y1=b, x2=c, y2=d;
		vmax=0, vmin=2147483647;
		query2D(1,1,n);
	}

	void modify1D(int o,int l,int r)
	{
		/*puts("modify1D");
		printf("%d %d %d\n",o,l,r);
		printf("x=%d y=%d\n",x,y);*/
		if(y<=l && r<=y){
			if(isleaf){
				//puts("update!");
				mx[xo][o] = mn[xo][o] = v;
			}else{
				//puts("1");
				mx[xo][o] = max(mx[xo*2][o], mx[xo*2+1][o]);
				mn[xo][o] = min(mn[xo*2][o], mn[xo*2+1][o]);
			}
		}else{
			//puts("2");
			int mid=l+(r-l)/2;
			if(y<=mid) modify1D(o*2,l,mid);
			else modify1D(o*2+1,mid+1,r);
			mx[xo][o] = max(mx[xo][o*2],mx[xo][o*2+1]);
			mn[xo][o] = min(mn[xo][o*2],mn[xo][o*2+1]);
		}
		return;
	}
	void modify2D(int o,int l,int r)
	{
		//printf("%d %d %d\n",o,l,r);
		if(x<=l && r<=x){
			xo=o;
			isleaf=1;
			modify1D(1,1,m);
		}else{
			//puts("modify2D");
			int mid=l+(r-l)/2;
			if(x<=mid) modify2D(o*2,l,mid);
			else modify2D(o*2+1,mid+1,r);
			xo=o;
			isleaf=0;
			modify1D(1,1,m);
		}
	}
	void modify(int a,int b,int c){ //modify: x,y,v
		x=a, y=b, v=c;
		modify2D(1,1,n);
	}
}ST;
