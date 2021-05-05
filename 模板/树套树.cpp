#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define mid ((L+R)>>1)
#define lc x<<1,L,mid
#define rc (x<<1)|1,mid+1,R
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=3000100,inf=100000000;
int n,m,x,y,k,tmp,sz,ans,rt[N],s[N],ls[N],rs[N],v[N],w[N],h[N],a[N];

void upd(int x){ s[x]=s[ls[x]]+s[rs[x]]+w[x]; }
void rrot(int &x){ int y=ls[x]; ls[x]=rs[y]; rs[y]=x; s[y]=s[x]; upd(x); x=y; }
void lrot(int &x){ int y=rs[x]; rs[x]=ls[y]; ls[y]=x; s[y]=s[x]; upd(x); x=y; }

void ins(int &x,int k){
	if (!x) { x=++sz; s[x]=w[x]=1; v[x]=k; h[x]=rand(); return; }
	s[x]++;
	if (k==v[x]) w[x]++;
	else if (k<v[x]) { ins(ls[x],k); if (h[ls[x]]<h[x]) rrot(x); }
		else { ins(rs[x],k); if (h[rs[x]]<h[x]) lrot(x); }
}

void del(int &x,int k){
	if (v[x]==k){
		if (w[x]>1) { w[x]--; s[x]--; return; }
		if ((!ls[x]) || (!rs[x])) { x=ls[x]+rs[x]; return; }
		if (h[ls[x]]<h[rs[x]]) { rrot(x); del(x,k); } else { lrot(x); del(x,k); }
		return;
	}
	if (k<v[x]) { del(ls[x],k); s[x]--; } else { del(rs[x],k); s[x]--; }
}

void askrank(int x,int k){
	if (!x) return;
	if (k==v[x]) { tmp+=s[ls[x]]; return; }
	else if (k<v[x]) askrank(ls[x],k); else tmp+=s[ls[x]]+w[x],askrank(rs[x],k);
}

void pre(int x,int k){
	if (!x) return;
	if (v[x]<k) tmp=max(v[x],tmp),pre(rs[x],k); else pre(ls[x],k);
}

void nxt(int x,int k){
	if (!x) return;
	if (v[x]>k) tmp=min(v[x],tmp),nxt(ls[x],k); else nxt(rs[x],k);
}

void build(int x,int L,int R,int pos,int k){
	ins(rt[x],k);
	if (L==R) return;
	if (pos<=mid) build(lc,pos,k); else build(rc,pos,k);
}

void getrank(int x,int L,int R,int l,int r,int k){
	if (L==l && R==r) { askrank(rt[x],k); return; }
	if (r<=mid) getrank(lc,l,r,k);
	else if (l>mid) getrank(rc,l,r,k);
		else getrank(lc,l,mid,k),getrank(rc,mid+1,r,k);
}

void getidx(int x,int y,int z){
	int l=0,r=inf,ans;
	while (l<=r){
		int m=(l+r)>>1;
		tmp=1; getrank(1,1,n,x,y,m);
		if (tmp<=z) l=m+1,ans=m; else r=m-1;
	}
	printf("%d\n",ans);
}

void change(int x,int L,int R,int pos,int k,int y){
	del(rt[x],y); ins(rt[x],k);
	if (L==R) return;
	if (pos<=mid) change(lc,pos,k,y); else change(rc,pos,k,y);
}

void askpre(int x,int L,int R,int l,int r,int k){
	if (L==l && R==r) { pre(rt[x],k); return; }
	if (r<=mid) askpre(lc,l,r,k);
	else if (l>mid) askpre(rc,l,r,k);
		else askpre(lc,l,mid,k),askpre(rc,mid+1,r,k);
}

void asknxt(int x,int L,int R,int l,int r,int k){
	if (L==l && R==r) { nxt(rt[x],k); return; }
	if (r<=mid) asknxt(lc,l,r,k);
	else if (l>mid) asknxt(rc,l,r,k);
		else asknxt(lc,l,mid,k),asknxt(rc,mid+1,r,k);
}

int main(){
	freopen("bzoj3196.in","r",stdin);
	freopen("bzoj3196.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",a+i);
	rep(i,1,n) build(1,1,n,i,a[i]);
	rep(i,1,m){
		int f; scanf("%d",&f);
		if (f==1) scanf("%d%d%d",&x,&y,&k),tmp=1,getrank(1,1,n,x,y,k),printf("%d\n",tmp);
		if (f==2) scanf("%d%d%d",&x,&y,&k),getidx(x,y,k);
		if (f==3) scanf("%d%d",&x,&y),change(1,1,n,x,y,a[x]),a[x]=y;
		if (f==4) scanf("%d%d%d",&x,&y,&k),tmp=0,askpre(1,1,n,x,y,k),printf("%d\n",tmp);
		if (f==5) scanf("%d%d%d",&x,&y,&k),tmp=inf,asknxt(1,1,n,x,y,k),printf("%d\n",tmp);
	}
	return 0;
}
