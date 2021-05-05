#include<cstdio>
#include<algorithm>
#include<cmath>
#define abs(x) ((x)>0 ? (x) : -(x))
using namespace std;
const double eps=1e-8,PI=acos(-1.0);//3.14159265358979323846

struct point{ double x,y; };
struct line{ point a,b; };

point operator - (point a,point b){ return (point){a.x-b.x,a.y-b.y}; }
double dist2(point a,point b){ point t=a-b; return t.x*t.x+t.y*t.y; }

int zero(double x) { return (x>0 ? x : -x)<eps; }
int sign(double x) { return (x>eps) ? 1 : ((x<-eps) ? -1 : 0); }

double xmult(point p0,point p1,point p2)
{ return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y); }

double dmult(point p0,point p1,point p2)
{ return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y); }

double dist(point p1,point p2)
{ return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)); }

int dotinline (point p1,point p2,point p3){ return zero(xmult(p1,p2,p3)); }//判三点共线

int dot_online_in(point p,line l)//判点是否在线段上,包括端点
{ return dotinline(p,l.a,l.b) && (l.a.x-p.x)*(l.b.x-p.x)<eps && (l.a.y-p.y)*(l.b.y-p.y)<eps; }

int dot_online_ex(point p,line l)//判点是否在线段上,不包括端点
{ return dot_online_in(p,l) && !zero(p.x-l.a.x) && !zero(p.x-l.b.x); }

int same(point p1,point p2,line l){ return xmult(p1,l.a,l.b)*xmult(p2,l.a,l.b)>eps; }//同侧(线段外)
int diff(point p1,point p2,line l){ return xmult(p1,l.a,l.b)*xmult(p2,l.a,l.b)<-eps; }//异侧(线段外)

int pingxing(line u,line v){ return zero(xmult((point){0,0},u.b-u.a,v.b-v.a)); }
int chuizhi(line u,line v){  return zero(dmult((point){0,0},u.b-u.a,v.b-v.a)); }

int jiao1(line u,line v){//判两线段相交,包括端点和部分重合
	if (!dotinline(u.a,u.b,v.a)||!dotinline(u.a,u.b,v.b))
		return !same(u.a,u.b,v)&&!same(v.a,v.b,u);
	return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}

int jiao2(line u,line v){ return diff(u.a,u.b,v)&&diff(v.a,v.b,u); }//判两线段相交,不包括端点和部分重合

double disdotline(point p,line l){ return abs(xmult(p,l.a,l.b))/dist(l.a,l.b); }//点到直线距离

double dis(point p,line l){//点到线段距离
	point t={p.x+l.a.y-l.b.y,p.y+l.b.x-l.a.x};
	if (xmult(l.a,t,p)*xmult(l.b,t,p)>eps) return min(dist(p,l.a),dist(p,l.b));
	return abs(xmult(p,l.a,l.b))/dist(l.a,l.b);
}

struct Line{ double a,b,c; };

point duicheng(point p1,point p2){ return (point){2*p2.x-p1.x,2*p2.y-p1.y}; } ////求p1关于p2的对称点

point duicheng2(point p,Line l){//p点关于直线L的对称点
	double d=l.a*l.a+l.b*l.b;
	return (point){ l.b*l.b*p.x-l.a*l.a*p.x-2*l.a*l.b*p.y-2*l.a*l.c/d,
				l.a*l.a*p.y-l.b*l.b*p.y-2*l.a*l.b*p.x-2*l.b*l.c/d };
}

Line toline(point p1,point p2){ return (Line){ p2.y-p1.y,p1.x-p2.x,p2.x*p1.y-p1.x*p2.y}; }
//两点式化为一般式

point interline(Line l1,Line l2){//求直线的交点，注意平行的情况无解，避免RE
	double a1=l1.a,b1=l1.b,c1=l1.c,a2=l2.a,b2=l2.b,c2=l2.c,x,y;
	if (sign(b1)==0) x=-c1/a1,y=(-c2-a2*x)/b2;
					else x=(c1*b2-b1*c2)/(b1*a2-b2*a1),y=(-c1-a1*x)/b1;
	return (point){x,y};
}

P work(P p1,P p2,P p3,P p4){//两线段交点
	double t1=cross(p1,p2,p3),t2=cross(p1,p2,p4);
	if (sgn(t1)*sgn(t2)<0){
		double x=(fabs(t2)*p3.x+fabs(t1)*p4.x)/(fabs(t1)+fabs(t2));
		double y=(fabs(t2)*p3.y+fabs(t1)*p4.y)/(fabs(t1)+fabs(t2));
		return (P){x,y};
	}
}
/*[cos -sin]
  [sin  cos]
 */
int main(){ printf("%.15lf\n",PI); return 0; }
