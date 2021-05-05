//poj3335 Rotating Scoreboard（求多边形核）
#include<cstdio>
#include<cmath>
#include<algorithm>
#define rep(i,l,r) for (i=l; i<=r; i++)
using namespace std;

const int N=210,inf=0x3f3f3f3f;
const double eps=1e-8;
inline double sgn(double x){ return (fabs(x)<eps) ? 0 : ( x>0 ? 1 : -1); }

int i,T,ntot,n,tot;
struct P{ double x,y; }p[N],a[N],s[N];
struct S{ P s,t; };

double cross(P a,P b,P c) { return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); }
bool outside(S seg,P p){ return cross(seg.s,seg.t,p)>eps; }
bool inside(S seg,P p){ return cross(seg.s,seg.t,p)<-eps; }

void work(P p1,P p2,P p3,P p4){
	double t1=cross(p1,p2,p3),t2=cross(p1,p2,p4);
	if (sgn(t1)*sgn(t2)<0){
		double x=(fabs(t2)*p3.x+fabs(t1)*p4.x)/(fabs(t1)+fabs(t2));
		double y=(fabs(t2)*p3.y+fabs(t1)*p4.y)/(fabs(t1)+fabs(t2));
		a[++tot]=(P){x,y};
	}
}

void cut(S seg){
	int i; tot=0;
	rep(i,1,ntot){
		if (!outside(seg,p[i])) a[++tot]=p[i];
		else work(seg.s,seg.t,p[i-1],p[i]),work(seg.s,seg.t,p[i],p[i+1]);
	}
	ntot=tot; swap(a,p); p[0]=p[tot]; p[tot+1]=p[1];
}

void solve(){
	rep(i,1,n) scanf("%lf%lf",&s[i].x,&s[i].y); s[n+1]=s[1];
	p[1]=(P){-inf,-inf}; p[2]=(P){-inf,inf}; p[3]=(P){inf,inf}; p[4]=(P){inf,-inf};
	ntot=4; p[0]=p[4]; p[5]=p[1];
	rep(i,1,n) cut((S){s[i],s[i+1]});
	if (tot==0) puts("NO"); else puts("YES");
}

int main(){
	for (scanf("%d",&T); T--; ) scanf("%d",&n),solve();
	return 0;
}

//O(nlogn)
#include<cmath>
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=100010;
const double eps=1e-8;
struct P{
    double x,y;
    P(double xx=0,double yy=0):x(xx),y(yy){}
}p[N],a[N];
struct L{P a,b; double slop;}l[N],q[N];

int n,k,cnt,tot;
double ans1,ans2;

P operator -(P a,P b){ return P(a.x-b.x,a.y-b.y); }
double operator *(P a,P b){ return a.x*b.y-a.y*b.x; }
bool operator <(L a,L b){ return (a.slop!=b.slop) ? (a.slop-b.slop)<-eps : (a.b-a.a)*(b.b-a.a)>eps; }

P inter(L a,L b){
    double A1=a.b.y-a.a.y,B1=a.a.x-a.b.x,C1=(a.b.x-a.a.x)*a.a.y-(a.b.y-a.a.y)*a.a.x;
    double A2=b.b.y-b.a.y,B2=b.a.x-b.b.x,C2=(b.b.x-b.a.x)*b.a.y-(b.b.y-b.a.y)*b.a.x;
    return P((C2*B1-C1*B2)/(A1*B2-A2*B1),(C1*A2-C2*A1)/(A1*B2-A2*B1));
}

bool jud(L a,L b,L t){ P p=inter(a,b); return (t.b-t.a)*(p-t.a)<-eps; }

void work(){
    sort(l+1,l+cnt+1);
    int L=1,R=0; tot=0;
    rep(i,1,cnt){
        if (abs(l[i].slop-l[i-1].slop)>eps) tot++;
        l[tot]=l[i];
    }
    cnt=tot; tot=0;
    q[++R]=l[1]; q[++R]=l[2];
    rep(i,3,cnt){
        while (L<R && jud(q[R-1],q[R],l[i])) R--;
        while (L<R && jud(q[L+1],q[L],l[i])) L++;
        q[++R]=l[i];
    }
    while (L<R && jud(q[R-1],q[R],q[L])) R--;
    while (L<R && jud(q[L+1],q[L],q[R])) L++;
    q[R+1]=q[L];
    rep(i,L,R) a[++tot]=inter(q[i],q[i+1]);
}

void get1(){
    ans1=0;
    if (tot<3) return;
    a[++tot]=a[1];
    rep(i,1,tot) ans1+=a[i]*a[i+1];
    ans1=fabs(ans1)/2;
}

void get2(){
    ans2=0; p[n+1]=p[1];
    rep(i,1,n+1) ans2+=p[i]*p[i+1];
    ans2=fabs(ans2)/2;
}

void ins(int i,int j){
    double a=p[1].y-p[i].y-p[2].y+p[j].y;
    double b=p[2].x-p[j].x-p[1].x+p[i].x;
    double c=p[1].x*p[2].y-p[2].x*p[1].y-p[i].x*p[j].y+p[j].x*p[i].y;
    if (abs(a)<eps && abs(b)<eps) return;
    if (abs(a)<eps){
        if (b>0) l[++cnt].a=P(1,-c/b),l[cnt].b=P(0,-c/b);
            else l[++cnt].a=P(0,-c/b),l[cnt].b=P(1,-c/b);
    }
    if (abs(b)<eps){
        if (a>0) l[++cnt].a=P(-c/a,0),l[cnt].b=P(-c/a,1);
            else l[++cnt].a=P(-c/a,1),l[cnt].b=P(-c/a,0);
    }
    if (abs(a)>eps && abs(b)>eps){
        if (b>0) l[++cnt].a=P(1,-a/b-c/b),l[cnt].b=P(0,-c/b);
            else l[++cnt].a=P(0,-c/b),l[cnt].b=P(1,-a/b-c/b);
    }
}

int main(){
    freopen("bzoj4445.in","r",stdin);
    freopen("bzoj4445.out","w",stdout);
    scanf("%d",&n);
    rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
    rep(i,2,n) ins(i,i%n+1); l[++cnt].a=p[1],l[cnt].b=p[2];
    rep(i,1,cnt) l[i].slop=atan2(l[i].b.y-l[i].a.y,l[i].b.x-l[i].a.x);
    work(); get1(); get2(); printf("%.4lf\n",ans1/ans2);
    return 0;
}
