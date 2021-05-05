//splay:
#include<cstdio>
#include<algorithm>
#include<iostream>
#define rep(i,l,r) for (i=l; i<=r; i++)
#define L c[x][0]
#define R c[x][1]
#define key c[c[rt][1]][0]
using namespace std;

const int N=2000100,inf=1000000000;
int cnt,rt,x,n,pos=1,c[N][2],s[N],rev[N],f[N];
char v[N],ch[N],op[20];

void get(int &x,char ch,int fa){ x=++cnt; v[x]=ch; f[x]=fa; L=R=rev[x]=0; s[x]=1; }
void upd(int x){ if (x) s[x]=s[L]+s[R]+1; }
void make(int x){ if (x) rev[x]^=1,swap(L,R); }
void push(int x){ if (x && rev[x]) make(L),make(R),rev[x]=0; }

void rot(int &rt,int x){
	int y=f[x],z=f[y],p=(c[y][1]==x),q=p^1;
	if (y==rt) rt=x; else c[z][c[z][1]==y]=x;
	f[x]=z; f[y]=x; f[c[x][q]]=y; c[y][p]=c[x][q]; c[x][q]=y;
	upd(y);
}

void splay(int &rt,int x){
	while (x!=rt){
		int y=f[x],z=f[y];
		if (y!=rt)
			{ if ((c[z][0]==y) ^ (c[y][0]==x)) rot(rt,x); else rot(rt,y); }
		rot(rt,x);
	}
	upd(x);
}

int find(int x,int k){
	push(x);
	if (s[L]+1==k) return x;
	else return (s[L]>=k) ? find(L,k) : find(R,k-s[L]-1);
}

inline void split(int l,int r){ int x=find(rt,l-1),y=find(rt,r+1); splay(rt,x); splay(c[rt][1],y); }

void insert(int &k,int l,int r,int fa){
	int mid=(l+r)>>1; get(k,ch[mid],fa);
	if (l<mid) insert(c[k][0],l,mid-1,k);
	if (mid<r) insert(c[k][1],mid+1,r,k);
	upd(k);
}

void ins(){
	scanf("%d%*c",&x); gets(ch); split(pos+1,pos);
	insert(key,0,x-1,c[rt][1]); upd(c[rt][1]); upd(rt);
}

void del(){ scanf("%d",&x); split(pos+1,pos+x); f[key]=0; key=0; upd(c[rt][1]); upd(rt); }
void reverse(){ scanf("%d",&x); split(pos+1,pos+x); make(key); }

int main(){
	get(rt,'*',0); get(c[rt][1],'*',rt); upd(rt);
	for (scanf("%d",&n); n--; ){
		scanf("%s",op);
		if (op[0]=='M') scanf("%d",&x),pos=x+1;
		if (op[0]=='I') ins();
		if (op[0]=='D') del();
		if (op[0]=='R') reverse();
		if (op[0]=='G') printf("%c\n",v[find(rt,pos+1)]);
		if (op[0]=='P') pos--;
		if (op[0]=='N') pos++;
	}
	return 0;
}

//LCT:
#include<cstdio>
#include<cctype>
#include<algorithm>
#define inf 1000000000
#define N 50100
#define M 100100
#define ls ch[x][0]
#define rs ch[x][1]
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

inline void rd(int &x){
	char ch; int t;
	for (t=0; !isdigit(ch=getchar()); t=(ch=='-'));
	for (x=ch-'0'; isdigit(ch=getchar()); x=x*10+ch-'0');
	if (t) x=-x;
}

int n,m,x,y,a,b,t,fa[N+M],tmp[N+M],ans=inf;

struct edge{ int x,y,a,b; }e[M];

bool operator <(edge a,edge b){ return a.a<b.a; }

int find(int x)
{ return fa[x]==x ? x : fa[x]=find(fa[x]);}

struct Tree{
	int val[M+N],mx[M+N],f[M+N],ch[M+N][2],rev[M+N];

	int isroot(int x) { return (!f[x])||(ch[f[x]][0]!=x && ch[f[x]][1]!=x);}
	void rev1(int x) { swap(ls,rs); rev[x]^=1;}
	void push(int x) { if (rev[x]) rev1(ls),rev1(rs),rev[x]=0;}

	void upd(int x){
		mx[x]=x;
		if (ls && val[mx[x]]<val[mx[ls]]) mx[x]=mx[ls];
		if (rs && val[mx[x]]<val[mx[rs]]) mx[x]=mx[rs];
	}

	void rot(int x){
		int y=f[x],z=f[y],w=ch[y][1]==x;
		ch[y][w]=ch[x][w^1]; f[ch[x][w^1]]=y;
		if (!isroot(y)) ch[z][ch[z][1]==y]=x;
		f[x]=z; f[y]=x; ch[x][w^1]=y; upd(y);
	}

	void splay(int x){
		int s=1,i=x; tmp[1]=x;
		while (!isroot(i)) tmp[++s]=i=f[i];
		while (s) push(tmp[s--]);
		while (!isroot(x)){
			int y=f[x];
			if (!isroot(y))
				((ch[f[y]][1]==y)^(ch[y][1]==x)) ? rot(x) :rot(y);
			rot(x);
		}
		upd(x);
	}

	void access(int x){
		for (int y=0; x; y=x,x=f[x]) splay(x),ch[x][1]=y,upd(x);
	}

	void mkroot(int x){ access(x); splay(x); rev1(x);}
	void link(int x,int y){ mkroot(x); f[x]=y; }
	void cut(int x,int y){ mkroot(x); access(y); splay(y); ch[y][0]=f[x]=0; upd(y); }
	int que(int x,int y){ mkroot(x); access(y); splay(y); return mx[y]; }

	int find(int x){
		access(x); splay(x);
		while (ls) x=ls;
		return x;
	}
	
}T;

int main(){
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	rd(n); rd(m); rep(i,1,n) fa[i]=i;
	rep(i,1,m) rd(e[i].x),rd(e[i].y),rd(e[i].a),rd(e[i].b);
	sort(e+1,e+m+1);
	rep(i,1,m){
		x=e[i].x; y=e[i].y; a=e[i].a; b=e[i].b;
		if (find(x)==find(y)){
			t=T.que(x,y);
			if (b<T.val[t]) T.cut(t,e[t-n].x),T.cut(t,e[t-n].y);
			else continue;
		}
		else fa[find(x)]=find(y);
		T.val[n+i]=b; T.mx[n+i]=n+i; T.link(x,n+i); T.link(y,n+i);
		if (find(1)==find(n)) ans=min(ans,T.val[T.que(1,n)]+a);
	}
	if (ans==inf) puts("-1"); else printf("%d\n",ans);
	return 0;
}
