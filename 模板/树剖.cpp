//bzoj3083
#include<cstdio>
#include<algorithm>
#define lc x<<1
#define rc ((x<<1)|1)
#define rep(i,l,r) for (int i=l; i<=r; i++)
#define For(i,x) for (i=h[x]; i; i=e[i].nxt)
using namespace std;

const int N=100100,inf=2147483647;
int n,m,u,v,k,op,cnt,x,y,z,rt,d[N],son[N],sz[N],f[N],h[N],last[N],top[N],w[N],cov[N<<2],mn[N<<2];
struct E{ int to,nxt; }e[N<<1];
void add(int u,int v){ e[++cnt]=(E){v,h[u]}; h[u]=cnt; }

void dfs(int x){
	int i,k; sz[x]=1;
	For(i,x) if ((k=e[i].to)!=f[x]){
		d[k]=d[x]+1; f[k]=x; dfs(k); sz[x]+=sz[k];
		if (sz[k]>sz[son[x]]) son[x]=k;
	}
}

void dfs2(int x,int t){
	int i,k; top[x]=t; w[x]=++z;
	if (son[x]) dfs2(son[x],t);
	For(i,x) if ((k=e[i].to)!=f[x] && k!=son[x]) dfs2(k,k);
	last[x]=z;
}

int get(int x,int y){
	while (f[top[y]]!=x && top[x]!=top[y]) y=f[top[y]];
	if (f[top[y]]!=x) return son[x]; else return top[y];
}
/*
int lca(int x,int y)
	for (; top[x]!=top[y]; x=f[top[x]]) if (d[top[x]]<d[top[y]]) swap(x,y);
	return d[x]<d[y]?x:y;
}
*/
void push(int x){
	if (cov[x]) cov[lc]=cov[rc]=mn[lc]=mn[rc]=cov[x],cov[x]=0;
}

void mdf(int x,int l,int r,int L,int R,int k){
	if (l==L && r==R) { mn[x]=cov[x]=k; return; }
	int mid=(l+r)>>1; push(x);
	if (R<=mid) mdf(lc,l,mid,L,R,k);
	else if (L>mid) mdf(rc,mid+1,r,L,R,k);
		else mdf(lc,l,mid,L,mid,k),mdf(rc,mid+1,r,mid+1,R,k);
	mn[x]=min(mn[lc],mn[rc]);
}

int ask(int x,int l,int r,int L,int R){
	if (l==L && r==R) return mn[x];
	int mid=(l+r)>>1; push(x);
	if (R<=mid) return ask(lc,l,mid,L,R);
	if (L>mid) return ask(rc,mid+1,r,L,R);
	return min(ask(lc,l,mid,L,mid),ask(rc,mid+1,r,mid+1,R));
}

void work(int x,int y,int z){
	for ( ; top[x]!=top[y]; x=f[top[x]]){
		if (d[top[x]]<d[top[y]]) swap(x,y);
		mdf(1,1,n,w[top[x]],w[x],z);
	}
	if (d[x]<d[y]) swap(x,y);
	mdf(1,1,n,w[y],w[x],z);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n-1) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1); dfs2(1,1);
	rep(i,1,n) scanf("%d",&k),mdf(1,1,n,w[i],w[i],k);
	scanf("%d",&rt);
	while (m--){
		scanf("%d",&op);
		if (op==1) scanf("%d",&rt);
		if (op==2) scanf("%d%d%d",&x,&y,&z),work(x,y,z);
		if (op==3){
			scanf("%d",&x);
			if (x==rt) printf("%d\n",ask(1,1,n,1,n));
			else
				if (f[rt]==x) printf("%d\n",min(ask(1,1,n,1,w[rt]-1),(last[rt]==n) ? inf :ask(1,1,n,last[rt]+1,n)));
				else if (w[rt]>=w[x] && w[rt]<=last[x])
						y=get(x,rt),printf("%d\n",min(ask(1,1,n,1,w[y]-1),(last[y]==n) ? inf :ask(1,1,n,last[y]+1,n)));
					else printf("%d\n",ask(1,1,n,w[x],last[x]));
		}
   }
	return 0;
}

/*
int work1(int x,int k){
	if (v[x]>=k) return ll[x];
	while (x)
		if ((x&1)==0) x=x>>1;
			else{ x=x>>1; if (mx[ls]>=k) break; }
	if (!x) return 0;
	for (x=ls; rr[x]-ll[x]; ) if (mx[rs]>=k) x=rs; else x=ls;
	return ll[x];
}

int work2(int x,int k){
	if (v[x]>=k) return ll[x];
	while (x)
		if (x&1) x=x>>1;
			else{ x=x>>1; if (mx[rs]>=k) break; }
	if (!x) return 0;
	for (x=rs; rr[x]-ll[x]; ) if (mx[ls]>=k) x=ls; else x=rs;
	return ll[x];
}
*/
