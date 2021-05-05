//bzoj3611
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long ll;
using namespace std;

const int N=1000010,inf=1e9;
int n,q,dis[N],dfn[N],tot,dep[N],fa[N][23],num,p[N];
int stk[N],top,siz[N],maxs[N],mins[N],ans1,ans2;
ll f[N]; bool bo[N];
bool cmp(int a,int b){return dfn[a]<dfn[b];}

struct Tgraph{

    int nxt[N<<1],h[N],to[N<<1],cnt;
    void add(int a,int b) {nxt[++cnt]=h[a]; h[a]=cnt; to[cnt]=b; }

    void dfs1(int x){
        dfn[x]=++tot;
        for (int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
        for (int i=h[x],k; i; i=nxt[i]) if ((k=to[i])!=fa[x][0]){
            dis[k]=dis[x]+1; dep[k]=dep[x]+1; fa[k][0]=x; dfs1(k);
        }
    }

    void dfs2(int x){
        siz[x]=bo[x]; maxs[x]=0; mins[x]=inf; f[x]=0;
        for (int i=h[x],k; i; i=nxt[i]){
            int d=dis[k=to[i]]-dis[x];
            dfs2(k),siz[x]+=siz[k];
            ans1=min(ans1,mins[x]+mins[k]+d),mins[x]=min(mins[x],mins[k]+d);
            ans2=max(ans2,maxs[x]+maxs[k]+d),maxs[x]=max(maxs[x],maxs[k]+d);
            f[x]+=f[k]+1ll*siz[k]*(num-siz[k])*d;
        }
        if (bo[x]) ans1=min(ans1,mins[x]),ans2=max(ans2,maxs[x]),mins[x]=0;
        h[x]=0;
    }
}g1,g2;

int lca(int a,int b){
    if (dep[a]<dep[b]) swap(a,b);
    for (int h=dep[a]-dep[b],i=20;i>=0;i--)
        if (h>=(1<<i)) h-=(1<<i),a=fa[a][i];
    for (int i=20;i>=0;i--) if (fa[a][i]!=fa[b][i]) a=fa[a][i],b=fa[b][i];
    if (a==b) return a; else return fa[a][0];
}

void work(){
    top=0;
    rep(i,1,num){
        if (!top) { stk[++top]=p[i]; continue; }
        int u=lca(stk[top],p[i]);
        while (dfn[u]<dfn[stk[top]]){
            if (dfn[u]>=dfn[stk[top-1]]){
                g2.add(u,stk[top]);
                if (stk[--top]!=u) stk[++top]=u;
                break;
            }
            g2.add(stk[top-1],stk[top]); top--;
        }
        stk[++top]=p[i];
    }
    while (top>1) g2.add(stk[top-1],stk[top]),top--;
    ans1=inf; ans2=0; g2.dfs2(stk[1]);
    printf("%lld %d %d\n",f[stk[1]],ans1,ans2);
    rep(i,1,num) bo[p[i]]=0;g2.cnt=0;
}

int main(){
    scanf("%d",&n);
    for (int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b),g1.add(a,b),g1.add(b,a);
    g1.dfs1(1); scanf("%d",&q);
    for (int i=1;i<=q;i++){
        scanf("%d",&num);
        for (int j=1;j<=num;j++) scanf("%d",&p[j]),bo[p[j]]=1;
        sort(p+1,p+1+num,cmp); work();
    }
    return 0;
}

#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=100100;
struct T{ int l,r,v,dis,f; }h[N];
int a,b,A,B,n,m;

int merge(int a,int b){
    if (!a||!b) return a+b;
    if (h[a].v<h[b].v) swap(a,b);
    h[a].r=merge(h[a].r,b); h[h[a].r].f=a;
    if (h[h[a].l].dis<h[h[a].r].dis) swap(h[a].l,h[a].r);
    h[a].dis=(h[a].r==0) ? 0 : h[h[a].r].dis+1;
    return a;
}

int pop(int a){
    int l=h[a].l,r=h[a].r;
    h[l].f=l; h[r].f=r; h[a].l=h[a].r=h[a].dis=0;
    return merge(l,r);
}

int find(int a){ return h[a].f==a ? a : find(h[a].f); }

int main(){
    freopen("hdu1512.in","r",stdin);
    freopen("hdu1512.out","w",stdout);
    while (scanf("%d",&n)==1){
        rep(i,1,n) scanf("%d",&h[i].v),h[i].l=h[i].r=h[i].dis=0,h[i].f=i;
        for (scanf("%d",&m); m--; ){
            scanf("%d%d",&a,&b); A=find(a); B=find(b);
            if (A==B) puts("-1");
            else{
                h[A].v/=2; int u=pop(A); u=merge(u,A);
                h[B].v/=2; int v=pop(B); v=merge(v,B);
                printf("%d\n",h[merge(u,v)].v);
            }
        }
    }
    return 0;
}
