///ternary_search
///problem source: nj3244 Country Meow
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-8;
struct Point{
    double x,y,z;
    Point(){}
    Point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
}point[105];

double dis(Point a, Point b){
    return (double)sqrt((double)((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z)));
}
double L[3]={200000.0,200000.0,200000.0},R[3]={-200000.0,-200000.0,-200000.0};
double cur[3];
int n;

double search(int d)
{
    if(d==3){
        Point p=Point(cur[0],cur[1],cur[2]);
        double mx=0.0;
        for(int i=0;i<n;i++){
            mx=max(mx,dis(p,point[i]));
        }
        return mx;
    }
    double l=L[d],r=R[d];
    double v[2];
    while(r-l>=eps){
        double m1,m2;
        m1=l+(r-l)/3;
        m2=r-(r-l)/3;
        cur[d]=m1;
        v[0]=search(d+1);
        cur[d]=m2;
        v[1]=search(d+1);
        if(v[0]>v[1]) l=m1;
        else r=m2;
    }
    cur[d]=(l+r)/2;
    v[1]=search(d+1);
    return v[1];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        point[i]=Point((double)x,(double)y,(double)z);
        L[0]=min(L[0],point[i].x);
        R[0]=max(R[0],point[i].x);
        L[1]=min(L[1],point[i].y);
        R[1]=max(R[1],point[i].y);
        L[2]=min(L[2],point[i].z);
        R[2]=max(R[2],point[i].z);
    }
    printf("%.15f\n",search(0));
}
