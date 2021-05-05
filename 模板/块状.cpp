//editor文本编辑器:
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long LL;
using namespace std;

const int N=1<<25,S=20000,M=N/S*3;

int n,m,cur,cnt=1,stk[M+110];
char str[N+110],s[100];

struct node{ char data[S+110]; int len,nxt; }a[M+110];

int get(){ return stk[cnt++]; }
void dis(int x){ stk[--cnt]=x; }
void init(){ a[0].len=0; a[0].nxt=-1; }

void find(int &pos,int &now)
{ for (now=0; a[now].nxt!=-1 && pos>a[now].len; now=a[now].nxt) pos-=a[now].len;}

void fill(int pos,int n,char* data,int nxt)
{ a[pos].nxt=nxt; a[pos].len=n; memcpy(a[pos].data,data,n);}

void split(int pos,int p){
	if (a[pos].len==p) return;
	int t=get();
	fill(t,a[pos].len-p,a[pos].data+p,a[pos].nxt);
	a[pos].nxt=t; a[pos].len=p;
}

void maintain(int pos){
	for (int t; pos!=-1; pos=a[pos].nxt)
		for (t=a[pos].nxt; t!=-1 && a[pos].len+a[t].len<S; t=a[pos].nxt){
			memcpy(a[pos].data+a[pos].len,a[t].data,a[t].len);
			a[pos].len+=a[t].len; a[pos].nxt=a[t].nxt; dis(t);
		}
}

void ins(int pos,int n){
	int now,i,t;
	find(pos,now); split(now,pos);
	for (i=0; i+S<=n; i+=S,now=t)
		{ t=get(); fill(t,S,str+i,a[now].nxt); a[now].nxt=t;}
	if (i<n)
		{ t=get(); fill(t,n-i,str+i,a[now].nxt); a[now].nxt=t;}
	maintain(now);
}

void del(int pos,int n){
	int now,i,t;
	find(pos,now); split(now,pos);
	for (i=a[now].nxt; i!=-1 && a[i].len<n; i=a[i].nxt) n-=a[i].len;
	split(i,n); i=a[i].nxt;
	for (t=a[now].nxt; t!=i; t=a[t].nxt) dis(t);
	a[now].nxt=i; maintain(now);
}

void put(int pos,int n){
	int now,i,t;
	find(pos,now); i=min(n,a[now].len-pos);
	memcpy(str,a[now].data+pos,i);
	for (t=a[now].nxt; t!=-1 && i+a[t].len<=n; i+=a[t].len,t=a[t].nxt)
		memcpy(str+i,a[t].data,a[t].len);
	if (i<n && t!=-1) memcpy(str+i,a[t].data,n-i);
	str[n]=0;
}

void rd(int m){
	for (int i=-1; i<m-1;){
		char c=getchar(); str[++i]=c;
		if (c<32||c>126) i--;
	}
}

int main(){
	freopen("editor.in","r",stdin);
	freopen("editor.out","w",stdout);
	init(); scanf("%d",&n);
	rep(i,1,M+100) stk[i]=i;
	rep(i,1,n){
		scanf("%s",s);
		if (s[0]=='M') scanf("%d",&cur);
		if (s[0]=='I') scanf("%d",&m),rd(m),ins(cur,m);
		if (s[0]=='N') cur++;
		if (s[0]=='P') cur--;
		if (s[0]=='D') scanf("%d",&m),del(cur,m);
		if (s[0]=='G') scanf("%d",&m),put(cur,m),puts(str);
	}
	return 0;
}

//块状树:
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long LL;
using namespace std;

const int inf=1000000000,N=30100,M=60100;

int n,q,u,v,lim,own[N],dep[N],fa[N],mx[N],sz[N],sum[N],w[N];

struct E{ int v,nxt; };

struct Edge{
	int cnt,h[N]; E e[M];
	void add(int x,int y) { e[++cnt]=(E){y,h[x]}; h[x]=cnt;}
}G,G1;

template<typename T>void rd(T &x){
	char ch; int t;
	for (t=0; !isdigit(ch=getchar()); t=(ch=='-'));
	for (x=ch-'0'; isdigit(ch=getchar()); x=x*10+ch-'0');
	if (t) x=-x;
}

void build(int u,int f,int d){
	dep[u]=d; fa[u]=f; int v;
	if (!own[u]) sz[own[u]=u]++;
	for (int i=G.h[u]; i; i=G.e[i].nxt)
		if ((v=G.e[i].v)!=f){
			if (sz[own[u]]<lim) G1.add(u,v),sz[own[v]=own[u]]++;
			build(v,u,d+1);
		}
}

void dfs(int u,int s,int m){
	sum[u]=s+=w[u]; mx[u]=m=max(m,w[u]);
	for (int i=G1.h[u]; i; i=G1.e[i].nxt) dfs(G1.e[i].v,s,m);
}

void change(int u,int k){
	w[u]=k;
	if (own[u]==u) dfs(u,0,-inf); else dfs(u,sum[fa[u]],mx[fa[u]]);
}

pair<int,int> que(int u,int v){
	int sm=0,m=-inf;
	while (u!=v){
		if (dep[u]<dep[v]) swap(u,v);
		if (own[u]==own[v]) sm+=w[u],m=max(m,w[u]),u=fa[u];
		else{
			if (dep[own[u]]<dep[own[v]]) swap(u,v);
			sm+=sum[u],m=max(m,mx[u]),u=fa[own[u]];
		}
	}
	return make_pair(sm+w[u],max(m,w[u]));
}

int main(){
	freopen("bzoj1036.in","r",stdin);
	freopen("bzoj1036.out","w",stdout);
	rd(n); lim=sqrt(n)+1;
	rep(i,1,n-1) rd(u),rd(v),G.add(u,v),G.add(v,u);
	rep(i,1,n) rd(w[i]); build(1,0,1);
	rep(i,1,n) if (own[i]==i) dfs(i,0,-inf);
	rd(q); char opt[10];
	while (q--){
		scanf("%s\n",opt); rd(u); rd(v);
		if (opt[0]=='C') change(u,v);
		else if (opt[1]=='M') printf("%d\n",que(u,v).second);
		else printf("%d\n",que(u,v).first);
	}
	return 0;
}