//Dinic(O(V2*E),n<=100000,m<=500000),POJ1149:
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rep(i,l,r) for (int i=l; i<=r; i++)
#define For(i,x) for (int i=h[x],k; i; i=e[i].nxt)
using namespace std;

const int N=105,inf=1000000000;
vector<int> a[N];
int v,x,y,m,n,S,T,cnt=1,d[N],q[N],h[N],cur[N],pig[1005],L[1005];
struct E{ int to,nxt,v; }e[100005];

void add(int u,int v,int w){
   e[++cnt]=(E){v,h[u],w}; h[u]=cnt;
   e[++cnt]=(E){u,h[v],0}; h[v]=cnt;
}

bool bfs(){
    memset(d,0,sizeof(d)); q[1]=S; d[S]=1;
    for (int st=0,ed=1; st!=ed; ){
        int x=q[++st];
        For(i,x) if (e[i].v && !d[k=e[i].to])
            d[k]=d[x]+1,q[++ed]=k;
    }
    return d[T];
}

int dfs(int x,int lim){
    if (x==T) return lim;
    int t,c=0;
    for (int i=cur[x],k; i; i=e[i].nxt)
    	if (d[k=e[i].to]==d[x]+1){
		    t=dfs(k,min(lim-c,e[i].v));
		    e[i].v-=t; e[i^1].v+=t; c+=t;
		    if (!e[i].v) cur[x]=i;
		    if (c==lim) return lim;
		}
    if (!c) d[x]=-1; return c;
}

int dinic(){
	int ans=0;
	while (bfs()){
		rep(i,0,T) cur[i]=h[i];
		ans+=dfs(0,inf);
	}
	return ans;
}

int main(){
    scanf("%d%d",&m,&n); S=0; T=n+1;
    rep(i,1,m) scanf("%d",pig+i);
    rep(i,1,n){
        for (scanf("%d",&x); x--; ) scanf("%d",&y),a[i].push_back(y);
        scanf("%d",&y); add(i,T,y);
    }
    rep(i,1,n)
        rep(j,0,(int)a[i].size()-1){
            v=a[i][j];
            if(!L[v]) add(0,i,pig[v]); else add(L[v],i,inf);
            L[v]=i;
    }
    printf("%d\n",dinic());
    return 0;
}

//最小费用最大流(MCMF,O(KV*E2),n<=5000,m<=10000)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=2010,inf=100000000;
int n,m,S,T,ans,u,v,c,st,ed,mn,cnt,h[N],pre[N],inq[N*100],dis[N],q[N];
struct E{ int to,c,nxt,f; }e[50100];

void add(int u,int v,int w,int f){
	e[++cnt]=(E){v,w,h[u],f}; h[u]=cnt;
	e[++cnt]=(E){u,-w,h[v],0}; h[v]=cnt;
}

int spfa(){
	rep(i,0,n+2) pre[i]=-1,inq[i]=0,dis[i]=inf;
	inq[S]=1; dis[S]=0; st=0; ed=1; q[1]=S;
	while (st!=ed){
		int x=q[++st]; inq[x]=0;
		for (int i=h[x],k; i; i=e[i].nxt)
			if (e[i].f && dis[k=e[i].to]>dis[x]+e[i].c){
				dis[k]=dis[x]+e[i].c; pre[k]=i;
				if (!inq[k]) inq[k]=1,q[++ed]=k;
			}
	}
	return dis[T]!=dis[0];
}

void mcmf(){
	for (ans=0; spfa(); ans+=dis[T]*mn){
		mn=inf;
		for (int i=pre[T]; ~i; i=pre[e[i^1].to]) mn=min(mn,e[i].f);
		for (int i=pre[T]; ~i; i=pre[e[i^1].to]) e[i].f-=mn,e[i^1].f+=mn;
	}
}

int main(){
	freopen("poj2135.in","r",stdin);
	freopen("poj2135.out","w",stdout);
	while (scanf("%d%d",&n,&m)==2){
		memset(h,0,sizeof(h)); cnt=1; S=n+1; T=n+2;
		rep(i,1,m) scanf("%d%d%d",&u,&v,&c),add(u,v,c,1),add(v,u,c,1);
		add(S,1,0,2); add(n,T,0,2); mcmf(); printf("%d\n",ans);
	}
	return 0;
}

//zkw费用流(不比朴素快多少,不稳定)
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
#define For(i,x) for (int i=h[x],k; i; i=e[i].nxt)
using namespace std;
const int N=2010,inf=1000000000;

template<typename T>void rd(T &x){
	int t; char ch;
	for (t=0; !isdigit(ch=getchar()); t=(ch=='-'));
	for (x=ch-'0'; isdigit(ch=getchar()); x=x*10+ch-'0');
	if (t) x=-x;
}

bool vis[N],inq[N];
int S,T,n,m,cnt=1,ans,u,v,c,t,h[N],dis[N],q[N];
struct E{ int to,nxt,v,c; }e[2000005];
void inc(int &x){ x++; if (x==2001) x=1; }

void add(int u,int v,int w,int c){
	e[++cnt]=(E){v,h[u],w,c}; h[u]=cnt;
	e[++cnt]=(E){u,h[v],0,-c}; h[v]=cnt;
}

bool bfs(){
	rep(i,0,T) dis[i]=inf;
	memset(inq,0,sizeof(inq)); dis[T]=0; q[1]=T; inq[T]=1;
	for (int st=0,ed=1; st!=ed; ){
		inc(st); int x=q[st]; inq[x]=0;
		For(i,x) if (e[i^1].v && dis[x]+e[i^1].c<dis[k=e[i].to]){
			dis[k]=dis[x]+e[i^1].c;
			if (!inq[k]) inq[k]=1,inc(ed),q[ed]=k;
		}
	}
	return dis[S]!=inf;
}

int dfs(int x,int lim){
	vis[x]=1; if (x==T) return lim;
	int w,c=0;
	For(i,x) if (e[i].v && !vis[k=e[i].to] && dis[x]==dis[k]+e[i].c){
		w=dfs(k,min(e[i].v,lim-c));
		e[i].v-=w; e[i^1].v+=w; ans+=e[i].c*w; c+=w;
		if (c==lim) return lim;
	}
	return c;
}

int zkw(){
	int ans=0;
	while (bfs()){
		vis[T]=1;
		while (vis[T]) memset(vis,0,sizeof(vis)),ans+=dfs(S,inf);
	}
	return ans;
}

int main(){
	rd(n); rd(m); S=0; T=2*n+1;
	rep(i,1,n) rd(t),add(0,i,1,0),add(i+n,T,1,0),add(0,i+n,1,t);
	rep(i,1,m){
		rd(u),rd(v),rd(c);
		if (u>v) swap(u,v); add(u,v+n,1,c);
	}
	zkw(); printf("%d\n",ans);
	return 0;
}

//上下界最大流建图:
begin
	assign(input,'maxflow.in'); reset(input);
	assign(output,'maxflow.out'); rewrite(output);
	readln(n,m); s:=n+m+1; t:=n+m+2;
	fillchar(ind,sizeof(ind),0); fillchar(sum,sizeof(sum),0);
	for i:=1 to m do
		begin
			read(k); inc(ind[t],k); dec(ind[i+n],k);
			add(i+n,t,inf-k,0);
		end;
	for i:=1 to n do
		begin
			readln(c,d); add(s,i,d,0);
			for j:=1 to c do
				begin
					readln(k,l,r); inc(k);
					dec(ind[i],l); inc(ind[k+n],l); map[i,k]:=l;
					add(i,k+n,r-l,0); id[i,k]:=cnt;
				end;
		end;
	add(t,s,inf,0); inc(s,2); inc(t,2);
	for i:=1 to n+m+2 do
		if ind[i]>0 then
			begin inc(sum,ind[i]); add(s,i,ind[i],0); end
		else add(i,t,-ind[i],0);
	if dinic<>sum then writeln(-1)
	else
		begin
			h[s]:=0; h[t]:=0; dec(s,2); dec(t,2);
			writeln(dinic);
			for i:=1 to n do
				for j:=1 to m do
					if id[i,j]>0 then writeln(flow[id[i,j]]+map[i,j]);
		end;
	close(input); close(output);
end.

//上下界最小流建图:
begin
	assign(input,'minflow.in'); reset(input);
	assign(output,'minflow.out'); rewrite(output);
	readln(n,m); sum:=0; maxflow:=0;
	fillchar(ind,sizeof(ind),0);
	for i:=1 to m do
		begin
			readln(u,v,c,k);
			if k>0 then
				begin dec(ind[u],c); inc(ind[v],c); ans[i]:=c; end
			else add(u,v,c,0,i);
		end;
	s:=n+1; t:=n+2;
	for i:=1 to n do
		begin
			if ind[i]>0 then
				begin inc(sum,ind[i]); add(s,i,ind[i],0,0); end;
			if ind[i]<0 then add(i,t,-ind[i],0,0);
		end;
	dinic; add(n,1,inf,0,0); dinic;
	if maxflow<sum then writeln('Impossible')
	else
		begin
			i:=h[n];
			while (i<>0)and(g[i]<>1) do i:=nxt[i];
			writeln(flow[((i-1)xor 1)+1]);
			for i:=1 to cnt do ans[id[i]]:=flow[((i-1)xor 1)+1];
			for i:=1 to m do write(ans[i],' ');
		end;
	close(input); close(output);
end.
