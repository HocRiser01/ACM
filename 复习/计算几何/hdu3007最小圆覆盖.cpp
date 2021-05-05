//O(n^4)
#include<cstdio>
#include<cmath>
#include<algorithm>
#define rep(i,l,r) for (i=l; i<=r; i++)
using namespace std;
 
const double eps=1e-8;  
int i,j,k,l,f,n;
double r,ans=1e10;

struct P{ double x,y; }p[510],s,t;

double dist(P A,P B){ return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }

P circenter(P A,P B,P C)
{
    double a1=B.x-A.x,b1=B.y-A.y,c1=(a1*a1+b1*b1)/2;  
    double a2=C.x-A.x,b2=C.y-A.y,c2=(a2*a2+b2*b2)/2;  
    double d=a1*b2-a2*b1;
    return (P){A.x+(c1*b2-c2*b1)/d,A.y+(a1*c2-a2*c1)/d};  
}

int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	scanf("%d",&n);
	rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
	if (n==1) { printf("%.2lf %.2lf\n%.2lf",p[1].x,p[1].y,0.0); return 0; }
	rep(i,1,n-1)
		rep(j,i+1,n){
			s=(P){(p[i].x+p[j].x)/2,(p[i].y+p[j].y)/2};
			r=dist(s,p[i]); f=1;
			rep(k,1,n) if (dist(p[k],s)-eps>r) { f=0; break; }
			if (f && r<ans) ans=r,t=s;
		}
	rep(i,1,n-2)
		rep(j,i+1,n-1)
			rep(k,j+1,n)
				if (fabs((p[j].x-p[i].x)*(p[k].y-p[i].y)-(p[k].x-p[i].x)*(p[j].y-p[i].y))>eps){
					s=circenter(p[i],p[j],p[k]);
					r=dist(s,p[i]); f=1;
					rep(l,1,n) if (dist(s,p[l])-eps>r) { f=0; break; }
					if (f && r<ans) ans=r,t=s;
				}
	printf("%.2lf %.2lf %.2lf",t.x,t.y,ans);
	return 0;
}

//POJ3007 O(n)
#include<cstdio>
#include<cmath>
#include<algorithm>
#define rep(i,l,r) for (i=l; i<=r; i++)
using namespace std;

const double eps=1e-8;
struct P{ double x,y; }p[1010],c,d;
int i,j,k,n;
double r;

double dist(P A,P B){ return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }

P circenter(P A,P B,P C)
{
    double a1=B.x-A.x,b1=B.y-A.y,c1=(a1*a1+b1*b1)/2;  
    double a2=C.x-A.x,b2=C.y-A.y,c2=(a2*a2+b2*b2)/2;  
    double d=a1*b2-a2*b1;
    return (P){A.x+(c1*b2-c2*b1)/d,A.y+(a1*c2-a2*c1)/d};  
}

void work(P *p,int n,P &c,double &r){
	random_shuffle(p+1,p+n+1); c=p[1]; r=0;
	rep(i,2,n)
		if (dist(p[i],c)>r+eps){
			c=p[i]; r=0;
			rep(j,1,i-1)
				if (dist(p[j],c)>r+eps){
					c=(P){(p[i].x+p[j].x)/2,(p[i].y+p[j].y)/2};
					r=dist(p[j],c);
					rep(k,1,j-1)
						if (dist(p[k],c)>r+eps) c=circenter(p[i],p[j],p[k]),r=dist(p[i],c);
				}
		}
}

int main(){
	for ( scanf("%d",&n); n; scanf("%d",&n)){
		rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
		work(p,n,c,r); printf("%.2f %.2f %.2f\n",c.x,c.y,r);
	}
	return 0;
}
