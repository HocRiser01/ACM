#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (i=l; i<=r; i++)
#define For(i,x) for (i=h[x]; i; i=e[i].nxt) if (!vis[k=e[i].to] && k!=fa)
using namespace std;

const int N=20010,inf=0x3f3f3f3f;
int i,n,x,y,v,cnt,k,tot,rt,sum,ans,fa=0,h[N],f[N],vis[N],sz[N],d[N],a[N];
struct E{ int to,val,nxt; } e[N];
void add(int u,int v,int w){ e[++cnt]=(E){v,w,h[u]}; h[u]=cnt; }

void get(int x,int fa){
	int i,k; sz[x]=1; f[x]=0;
	For(i,x) get(k,x),sz[x]+=sz[k],f[x]=max(f[x],sz[k]);
	f[x]=max(f[x],sum-sz[x]);
	if (f[x]<f[rt]) rt=x;
}

void deep(int x,int fa){
	int i,k; a[++tot]=d[x];
	For(i,x) d[k]=d[x]+e[i].val,deep(k,x);
}

int cal(int x,int v){
	d[x]=v; tot=0; deep(x,0);
	sort(a+1,a+tot+1);
	int l=1,r=tot,sum=0;
	while (l<r)
		if (a[l]+a[r]<=k) sum+=r-l,l++; else r--;
	return sum;
}

void solve(int x){
	int i,k; ans+=cal(x,0); vis[x]=1;
	For(i,x){
		ans-=cal(k,e[i].val); sum=sz[k];
		rt=0; get(k,0); solve(rt);
	}
}

int main(){
	for (scanf("%d%d",&n,&k); n+k; scanf("%d%d",&n,&k)){
		ans=rt=cnt=0; f[0]=inf; sum=n;
		memset(vis,0,sizeof(vis)); memset(h,0,sizeof(h));
		rep(i,1,n-1) scanf("%d%d%d",&x,&y,&v),add(x,y,v),add(y,x,v);
		get(1,0); solve(rt); printf("%d\n",ans);
	}
	return 0;
}
