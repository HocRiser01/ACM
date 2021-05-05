//==============================rotating coliper==============================
#include<cstdio>
#include<cmath>
#include<algorithm>
#define rep(i,l,r) for (i=l; i<=r; i++)
using namespace std;

const double eps=1e-5;
int i,n,top;
double ans,t;

struct P{ double x,y; }p[500010],q[500010];
double dis2(P a,P b){ return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }
double xmult(P a,P b,P c){ return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}

int cmp(P a,P b)
{ return (t=xmult(p[1],a,b))>eps || (t>-eps && dis2(a,p[1])<dis2(b,p[1])); }

void graham(){
	int i,mx=1;
	rep(i,2,n) if (p[i].y<p[mx].y || (p[i].y==p[mx].y && p[i].x<p[mx].x)) mx=i;
	swap(p[1],p[mx]);
	sort(p+2,p+n+1,cmp);
	q[++top]=p[1]; q[++top]=p[2];
	rep(i,3,n){
		while (top>1 && xmult(q[top-1],q[top],p[i])<eps) top--;
		q[++top]=p[i];
	}
	q[top+1]=q[1];
}

void RC(){
	int i,x=2; ans=0;
	rep(i,1,top){
		while (xmult(q[i],q[i+1],q[x])<xmult(q[i],q[i+1],q[x+1])) x=(x==top) ? 1 : x+1;
		ans=max(ans,dis2(q[x],q[i]));
	}
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
	graham(); RC(); printf("%d",(int)ans);
	return 0;
}
