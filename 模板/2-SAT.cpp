#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
#define For(i,x) for (int i=h[x],k; i; i=e[i].nxt)
using namespace std;

const int N=1010;
char ch1,ch2;
int T,x,y,xp,yp,f,n,m,cnt,tim,scc,top,h[N],dfn[N],low[N],q[N],bel[N],inq[N];
struct E{ int to,nxt;} e[20100];

void add(int u,int v){ e[++cnt]=(E){v,h[u]}; h[u]=cnt; }

void tarjan(int x){
	low[x]=dfn[x]=++tim; inq[x]=1; q[++top]=x;
	For(i,x)
		if (!dfn[k=e[i].to]) tarjan(k),low[x]=min(low[x],low[k]);
		else if (inq[k]) low[x]=min(low[x],dfn[e[i].to]);
	if (low[x]==dfn[x]){
		scc++; int t;
		do{ t=q[top--]; bel[t]=scc; inq[t]=0; } while (t!=x);
	}
}

int main(){
	freopen("sat.in","r",stdin);
	freopen("sat.out","w",stdout);
	for (scanf("%d",&T); T--; ){
		top=tim=cnt=scc=f=0; scanf("%d%d",&n,&m);
		rep(i,1,2*n) h[i]=dfn[i]=0;
		rep(i,1,m){
			scanf(" %c%d %c%d",&ch1,&x,&ch2,&y);
			x=x*2-(ch1=='h'); y=y*2-(ch2=='h');
			if (x&1) xp=x++; else xp=x--;
			if (y&1) yp=y++; else yp=y--;
			add(xp,y); add(yp,x);
		}
		rep(i,1,2*n) if (!dfn[i]) tarjan(i);
		rep(i,1,n) if (bel[2*i]==bel[2*i-1]) { f=1; break; }
		if (!f) puts("GOOD"); else puts("BAD");
	}
	return 0;
}
